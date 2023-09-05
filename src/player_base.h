#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class PlayerBase : public CharacterBody2D {
	GDCLASS(PlayerBase, CharacterBody2D)

private:
    //CharacterBody2D* bla;
    Vector2 direction;

public:
    void set_direction(const Vector2 p_direction);
    Vector2 get_direction() const;

public:
    PlayerBase();
    ~PlayerBase();
    
    void process(double p_delta);
    void _input(InputEvent* event);


protected:
    static void _bind_methods();

};
}

#endif
