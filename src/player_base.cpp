#include <player_base.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void PlayerBase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_move_direction", "p_direction"), &PlayerBase::set_move_direction);
    ClassDB::bind_method(D_METHOD("get_move_direction"), &PlayerBase::get_move_direction);
    ClassDB::add_property("PlayerBase", PropertyInfo(Variant::VECTOR2, "move_direction"), "set_move_direction", "get_move_direction");

    ClassDB::bind_method(D_METHOD("set_attack_direction", "p_direction"), &PlayerBase::set_attack_direction);
    ClassDB::bind_method(D_METHOD("get_attack_direction"), &PlayerBase::get_attack_direction);
    ClassDB::add_property("PlayerBase", PropertyInfo(Variant::VECTOR2, "attack_direction"), "set_attack_direction", "get_attack_direction");

    ClassDB::bind_method(D_METHOD("set_action", "p_action"), &PlayerBase::set_action);
    ClassDB::bind_method(D_METHOD("get_action"), &PlayerBase::get_action);
    ClassDB::add_property("PlayerBase", PropertyInfo(Variant::INT, "action", PROPERTY_HINT_ENUM, "None,Attack"), "set_action", "get_action");

    ClassDB::bind_method(D_METHOD("process", "p_delta"), &PlayerBase::process);

    ClassDB::bind_method(D_METHOD("set_health", "p_health"), &PlayerBase::set_health);
    ClassDB::bind_method(D_METHOD("get_health"), &PlayerBase::get_health);
    ClassDB::add_property("PlayerBase", PropertyInfo(Variant::INT, "health"), "set_health", "get_health");

    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &PlayerBase::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &PlayerBase::get_speed);
    ClassDB::add_property("PlayerBase", PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");
    

    BIND_ENUM_CONSTANT(ACTION_NONE)
    BIND_ENUM_CONSTANT(ACTION_ATTACK)

}

void PlayerBase::set_speed(const int p_direction) {
    speed = p_direction;
}

int PlayerBase::get_speed() const{
    return speed;
}

void PlayerBase::set_health(const int p_direction) {
    health = p_direction;
}

int PlayerBase::get_health() const{
    return health;
}

void PlayerBase::set_move_direction(const Vector2 p_direction) {
    move_direction = p_direction;
}

Vector2 PlayerBase::get_move_direction() const{
    return move_direction;
}

void PlayerBase::set_attack_direction(const Vector2 p_direction) {
    attack_direction = p_direction;
}

Vector2 PlayerBase::get_attack_direction() const{
    return attack_direction;
}

void PlayerBase::set_action(const Action p_action) {
    action = p_action;
}

PlayerBase::Action PlayerBase::get_action() {
    return action;
}

PlayerBase::PlayerBase() {
    move_direction = Vector2(0, 0);
    action = ACTION_NONE;
    health = 20;
    speed = 300;
    //bla = nullptr;
    if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	} else {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_INHERIT);
	}
}

PlayerBase::~PlayerBase() {
//    if (bla)
  //      bla->queue_free();
}

void PlayerBase::process(double p_delta) {
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

void PlayerBase::_input(InputEvent* event) {
//    Ref<InputEventKey> ev = event;
    bool wtf = event->is_class("InputEventKey");
    if (((InputEventKey*)event)->is_action_pressed("ui_select")) {
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
    }
}
