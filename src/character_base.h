#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include "player_input_sync.h"


namespace godot {

class CharacterBase : public CharacterBody2D {
	GDCLASS(CharacterBase, CharacterBody2D)

public:

private:
    PlayerInputSync* input_sync;
    AnimatedSprite2D* sprite;
    Camera2D* camera;
    
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
    void set_player(int p_player);
    int get_player() const;

public:
    CharacterBase();
    ~CharacterBase();
    
    void _ready() override;
    void _process(double p_delta) override;
    void _physics_process(double p_delta) override;

protected:
    static void _bind_methods();

};
}

#endif
