#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include "player_input_sync.h"


namespace godot {

class CharacterBase : public CharacterBody2D {
	GDCLASS(CharacterBase, CharacterBody2D)

public:

private:
    //CharacterBody2D* bla;
//    NodePath input_sync;
    PlayerInputSync* input_sync;
    AnimatedSprite2D* sprite;
    Camera2D* camera;
    Input* input;
    
    int player;

    bool is_dead;
    Vector2 move_direction;
    Vector2 attack_direction;
    PlayerInputSync::Action action;
    int health;
    int speed;
    Node2D* target;

    void handle_animations();

public:
    void animation_finished();
    void attack();
    void damage(int amount);
    void set_health(const int p_health);
    int get_health() const;
    void set_speed(const int p_speed);
    int get_speed() const;
    void set_move_direction(const Vector2 p_move_direction);
    Vector2 get_move_direction() const;
    void set_attack_direction(const Vector2 p_attack_direction);
    Vector2 get_attack_direction() const;
    void set_player(int p_player);
    int get_player() const;
    //void set_action(const Action p_action);
    //Action get_action();
    //void set_input_sync(NodePath p_input_sync);
    //NodePath get_input_sync();
    //void set_direction(const real_t p_direction);
    //real_t get_direction() const;

public:
    CharacterBase();
    ~CharacterBase();
    
    void _ready() override;
    void _process(double p_delta) override;
    void _physics_process(double p_delta) override;
    void moj_input(const Ref<InputEvent> &event);
    //void _input(const Ref<InputEvent> &event) override;

protected:
    static void _bind_methods();

};
}

//VARIANT_ENUM_CAST(CharacterBase::Action)

#endif
