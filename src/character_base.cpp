#include "player_input_sync.h"
#include <character_base.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/property_tweener.hpp>
#include <godot_cpp/variant/callable.hpp>
//#include <godot_cpp/core/>
//#include <godot_cpp/classes/twee

using namespace godot;

void CharacterBase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_move_direction", "p_move_direction"), &CharacterBase::set_move_direction);
    ClassDB::bind_method(D_METHOD("get_move_direction"), &CharacterBase::get_move_direction);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::VECTOR2, "move_direction"), "set_move_direction", "get_move_direction");

    ClassDB::bind_method(D_METHOD("set_attack_direction", "p_attack_direction"), &CharacterBase::set_attack_direction);
    ClassDB::bind_method(D_METHOD("get_attack_direction"), &CharacterBase::get_attack_direction);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::VECTOR2, "attack_direction"), "set_attack_direction", "get_attack_direction");

   // ClassDB::bind_method(D_METHOD("set_action", "p_action"), &CharacterBase::set_action);
   // ClassDB::bind_method(D_METHOD("get_action"), &CharacterBase::get_action);
   // ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "action", PROPERTY_HINT_ENUM, "None,Attack"), "set_action", "get_action");

    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &CharacterBase::set_health);
    ClassDB::bind_method(D_METHOD("get_health"), &CharacterBase::get_health);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &CharacterBase::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &CharacterBase::get_speed);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("set_player", "p_player"), &CharacterBase::set_player);
    ClassDB::bind_method(D_METHOD("get_player"), &CharacterBase::get_player);
    ClassDB::add_property("CharacterBase", PropertyInfo(Variant::INT, "player"), "set_player", "get_player");

  //  ClassDB::bind_method(D_METHOD("set_input_sync", "p_input_sync"), &CharacterBase::set_input_sync);
  //  ClassDB::bind_method(D_METHOD("get_input_sync"), &CharacterBase::get_input_sync);
  //  ClassDB::add_property("CharacterBase", PropertyInfo(Variant::NODE_PATH, "input_sync"), "set_input_sync", "get_input_sync");
    
//    ClassDB::bind_method(D_METHOD("ready"), &CharacterBase::ready);
 //   ClassDB::bind_method(D_METHOD("physics_process", "p_delta"), &CharacterBase::physics_process);
  //  ClassDB::bind_method(D_METHOD("process", "p_delta"), &CharacterBase::_process);
   // ClassDB::bind_method(D_METHOD("moj_input", "p_event"), &CharacterBase::moj_input);
    ClassDB::bind_method(D_METHOD("animation_finished"), &CharacterBase::animation_finished);
    ClassDB::bind_method(D_METHOD("attack"), &CharacterBase::attack);

    //ClassDB::bind_method(D_METHOD("_input", "p_input"), &CharacterBase::_input);
    //BIND_VIRTUAL_METHOD(CharacterBase, _input)

   // BIND_ENUM_CONSTANT(ACTION_NONE)
   // BIND_ENUM_CONSTANT(ACTION_ATTACK)

}

void CharacterBase::handle_animations() {
    if (!is_dead) {
        if (action == PlayerInputSync::ACTION_ATTACK) {
            sprite->set_flip_h(attack_direction.x < 0);
            String anim = sprite->get_animation();
            if (anim != "attack" && anim != "attack2") {
                Ref<Tween> tw = create_tween();
                tw->set_trans(Tween::TransitionType::TRANS_SINE);
//                tw->set_ease(Tween::EaseType::EASE_IN);
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
    UtilityFunctions::print("finished");
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

void CharacterBase::set_move_direction(const Vector2 p_move_direction) {
    move_direction = p_move_direction;
}

Vector2 CharacterBase::get_move_direction() const{
    return move_direction;
}

void CharacterBase::set_attack_direction(const Vector2 p_attack_direction) {
    attack_direction = p_attack_direction;
}

Vector2 CharacterBase::get_attack_direction() const{
    return attack_direction;
}

/*void CharacterBase::set_action(const Action p_action) {
    action = p_action;
}

CharacterBase::Action CharacterBase::get_action() {
    return action;
}*/

/*void CharacterBase::set_input_sync(NodePath p_input_sync) {
    input_sync = p_input_sync;
}

NodePath CharacterBase::get_input_sync() {
    return input_sync;
}*/

CharacterBase::CharacterBase() {
    move_direction = Vector2(0, 0);
    attack_direction = Vector2(0, 0);
    action = PlayerInputSync::ACTION_NONE;
    health = 20;
    speed = 300;
    player = 1;
    is_dead = false;
    input = Input::get_singleton();
    input_sync = nullptr;
    sprite = nullptr;
       
    //bla = nullptr;
    if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	} else {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
    }
}

CharacterBase::~CharacterBase() {
//    if (bla)
  //      bla->queue_free();
}

void CharacterBase::_ready() {
    input_sync = get_node<PlayerInputSync>("InputSynchronizer");
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    sprite->connect("animation_finished", Callable(this, "animation_finished"));
    sprite->connect("frame_changed", Callable(this, "attack"));

    if (player == get_multiplayer()->get_unique_id())
        get_node<Camera2D>("Camera2D")->make_current();
}

void CharacterBase::_physics_process(double p_delta) {
    Ref<PhysicsRayQueryParameters2D> query = PhysicsRayQueryParameters2D::create(get_position(), get_position() + attack_direction * 100);
    Dictionary result = get_world_2d()->get_direct_space_state()->intersect_ray(query);
    target = Object::cast_to<Node2D>(result["collider"]);
    //UtilityFunctions::print(target);
  //  /*if (target)*/ UtilityFunctions::print(get_multiplayer()->is_server(), this, target, attack_direction);
}

void CharacterBase::_process(double p_delta) {
    attack_direction = input_sync->attack_direction.normalized();
    move_direction = input_sync->move_direction;
    //UtilityFunctions::print(get_multiplayer()->is_server(), this, move_direction);
    action = input_sync->action;
//    UtilityFunctions::print(move_direction);
    
    handle_animations();
    //UtilityFunctions::print("process");
    Vector2 target = move_direction.normalized();
    if (target.length_squared() > 0)
        set_velocity(target * speed);
    else
        set_velocity(get_velocity().move_toward(Vector2(0, 0), speed));
    /*if (direction != 100)
        set_velocity(Vector2(300, 0).rotated(direction));
    else
        set_velocity(get_velocity().move_toward(Vector2(0, 0), 300));*/

    move_and_slide();

/*    if (bla) {
        bla->set_position(Vector2(0, bla->get_position().y + delta * 200));
        if (bla->get_position().y > 500)
            bla->set_position(Vector2(0, 100));
    }*/
}

void CharacterBase::moj_input(const Ref<InputEvent> &event){
    CharacterBase::_input(event);
}

/*void CharacterBase::_input(const Ref<InputEvent> &event) {
    UtilityFunctions::print("input");
    //bool wtf = event->is_class("InputEventKey");
    Ref<InputEventKey> ev = event; //static_cast<Ref<InputEventKey>>(event);
    if (ev.is_valid()) {
        if (input->is_action_just_pressed("ui_accept"))
            sprite->play("idle");
        if (ev->is_action_pressed("ui_select")) {
            UtilityFunctions::print("test");
        }
    }*/
    //if (((InputEventKey*)*event)->is_action_pressed("ui_select")) {
        /*UtilityFunctions::print("works");
        ResourceLoader* loader = ResourceLoader::get_singleton();
        Ref<Resource> res = (loader->load("res://player.tscn"));
        if (*res) {
            PackedScene* scene = (PackedScene*)*res;
            if (scene) {
                Node* spawned = scene->instantiate();
                get_parent()->add_child(spawned);
                if (bla)
                    bla->queue_free();
                bla = (CharacterBody2D*)spawned;
                bla->set_position(Vector2(0, 0));
                UtilityFunctions::print("spawned");
            } else { 
                UtilityFunctions::print("boo");
            }
        } else {
            UtilityFunctions::print("boooooooooo>");
        }*/
 //   }
//}
