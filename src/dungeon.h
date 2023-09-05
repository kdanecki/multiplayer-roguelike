#ifndef DUNGEON_H
#define DUNGEON_H

#include <godot_cpp/classes/tile_map.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot {



class Dungeon : public TileMap {
    GDCLASS(Dungeon, TileMap)

public:
    enum TileType {
        TILE_GRASS,
        TILE_YELLOW_GRASS,
        TILE_HOUSE,
        TILE_MOUNTAIN,
        TILE_FOREST
    };

    static const Vector2i directions[]; 

private:
    RandomNumberGenerator rng;
    Dictionary dungeon;
    int size;
    int rooms;
    void set_ring(Vector2i center,int radius, int type);
    void set_spiral(Vector2i center, int radius, int type);
    int distance(Vector2i a, Vector2i b);
    void path(Vector2i start, Vector2i end, int type);

public:
    void generate();


    int get_rooms();
    void set_rooms(int p_rooms);
    Dictionary get_dungeon();
    void set_dungeon(Dictionary p_dungeon);
    int get_size();
    void set_size(TileType p_size);

    Dungeon();
    ~Dungeon();

protected:
    static void _bind_methods();

};
}

VARIANT_ENUM_CAST(Dungeon::TileType)

#endif
