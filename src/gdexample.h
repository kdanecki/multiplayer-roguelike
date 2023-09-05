#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class GDExample : public Sprite2D {
    GDCLASS(GDExample, Sprite2D)

private:
    double time_passed;
    double time_emit;
    double amplitude;
    double speed;
    int test2;

public:
    void set_amplitude(const double p_amplitude);
    double get_amplitude() const;
    void set_test(const int p_test);
    int get_test() const;
    void set_speed(const double p_speed);
    double get_speed() const;
    void test_func();

protected:
    static void _bind_methods();

public:
    GDExample();
    ~GDExample();

    void _ready() override;
    void _process(double delta) override;
};

}

#endif
