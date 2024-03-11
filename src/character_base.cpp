#include "player_input_sync.h"
#include <character_base.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/variant/callable.hpp>

using namespace godot;

void CharacterBase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &CharacterBase::set_health);
    ClassDB::bind_method(D_METHOD("get_health"), &CharacterBase::get_health);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &CharacterBase::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &CharacterBase::get_speed);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("set_player", "p_player"), &CharacterBase::set_player);
    ClassDB::bind_method(D_METHOD("get_player"), &CharacterBase::get_player);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "player"), "set_player", "get_player");

    ClassDB::bind_method(D_METHOD("animation_finished"), &CharacterBase::animation_finished);
    ClassDB::bind_method(D_METHOD("attack"), &CharacterBase::attack);

}

void CharacterBase::handle_animations() {
    if (!is_dead) {
        if (action == PlayerInputSync::ACTION_ATTACK) {
            sprite->set_flip_h(attack_direction.x < 0);
            String anim = sprite->get_animation();
            if (anim != "attack" && anim != "attack2") {
                Ref<Tween> tw = create_tween();
                tw->set_trans(Tween::TransitionType::TRANS_SINE);
                tw->tween_property(sprite, "position", attack_direction * 30, 0.5);
                tw->tween_property(sprite, "position", Vector2(0, 0), 0.5);
                RandomNumberGenerator rng;
                rng.randomize();
                if (rng.randi_range(0, 1)) {
                    sprite->play("attack");
                } else {
                    sprite->play("attack2");
                }
            }
        } else if (move_direction.length_squared() > 0) {
            sprite->play("run");
            sprite->set_flip_h(move_direction.x < 0);
        } else {
        sprite->play("stay");
        }
    }
}

void CharacterBase::animation_finished() {
    if (!is_dead) {
        sprite->play("stay");
    }
}

void CharacterBase::attack() {
    String anim = sprite->get_animation();
    if ((anim == "attack" && sprite->get_frame() == 2) || (anim == "attack2" && sprite->get_frame() == 3)) {
        CharacterBase* hit = Object::cast_to<CharacterBase>(target);
        if (hit) {
            hit->damage(5);
        } else {
            UtilityFunctions::print("miss");
        }
    }
}

void CharacterBase::damage(int amount) {
    health -= amount;
    if (health <= 0 && (!is_dead)) {
        is_dead = true;
        sprite->play("die");
    }
}

void CharacterBase::set_player(const int p_player) {
    player = p_player;
    get_node<PlayerInputSync>("InputSynchronizer")->set_multiplayer_authority(player);
}

int CharacterBase::get_player() const{
    return player;
}

void CharacterBase::set_speed(const int p_direction) {
    speed = p_direction;

}

int CharacterBase::get_speed() const{
    return speed;
}

void CharacterBase::set_health(const int p_direction) {
    health = p_direction;
}

int CharacterBase::get_health() const{
    return health;
}

CharacterBase::CharacterBase() {
    move_direction = Vector2(0, 0);
    attack_direction = Vector2(0, 0);
    action = PlayerInputSync::ACTION_NONE;
    health = 20;
    speed = 300;
    player = 1;
    is_dead = false;
    input_sync = nullptr;
    sprite = nullptr;
       
    if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	} else {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
    }
}

CharacterBase::~CharacterBase() {
}

void CharacterBase::_ready() {
    input_sync = get_node<PlayerInputSync>("InputSynchronizer");
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    if (get_multiplayer()->is_server()) {
        sprite->connect("animation_finished", Callable(this, "animation_finished"));
        sprite->connect("frame_changed", Callable(this, "attack"));
    }

    if (player == get_multiplayer()->get_unique_id())
        get_node<Camera2D>("Camera2D")->make_current();
}

void CharacterBase::_physics_process(double p_delta) {
    if (get_multiplayer()->is_server() && !is_dead) {
        action = input_sync->action;

        attack_direction = input_sync->attack_direction.normalized();
        Ref<PhysicsRayQueryParameters2D> query = PhysicsRayQueryParameters2D::create(get_position(), get_position() + attack_direction * 100);
        Dictionary result = get_world_2d()->get_direct_space_state()->intersect_ray(query);
        target = Object::cast_to<Node2D>(result["collider"]);

        move_direction = input_sync->move_direction.normalized();
        set_velocity(move_direction * 300);
        move_and_slide();
    }
}

void CharacterBase::_process(double p_delta) {
    if (get_multiplayer()->is_server()) {
        handle_animations();
    }
    UtilityFunctions::print("bla bla");
}

