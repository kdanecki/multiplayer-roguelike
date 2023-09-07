#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class PlayerBase : public CharacterBody2D {
	GDCLASS(PlayerBase, CharacterBody2D)

public:
    enum Action {
        ACTION_NONE,
        ACTION_ATTACK
    };

private:
    //CharacterBody2D* bla;
    Vector2 move_direction;
    Vector2 attack_direction;
    Action action;
    int health;
    int speed;

public:
    void set_health(const int p_health);
    int get_health() const;
    void set_speed(const int p_speed);
    int get_speed() const;
    void set_move_direction(const Vector2 p_direction);
    Vector2 get_move_direction() const;
    void set_attack_direction(const Vector2 p_direction);
    Vector2 get_attack_direction() const;
    void set_action(const Action p_action);
    Action get_action();
    //void set_direction(const real_t p_direction);
    //real_t get_direction() const;

public:
    PlayerBase();
    ~PlayerBase();
    
    void process(double p_delta);
    void _input(InputEvent* event);


protected:
    static void _bind_methods();

};
}

VARIANT_ENUM_CAST(PlayerBase::Action)

#endif
