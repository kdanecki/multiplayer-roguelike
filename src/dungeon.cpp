#include "dungeon.h"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

const Vector2i Dungeon::directions[] = {
        Vector2i(1, 0), Vector2i(1, -1), Vector2i(0, -1), Vector2i(-1, 0), Vector2i(-1, 1), Vector2i(0, 1)
};

void Dungeon::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_dungeon"), &Dungeon::get_dungeon);
    ClassDB::bind_method(D_METHOD("set_dungeon", "p_dungeon"), &Dungeon::set_dungeon);
    ClassDB::add_property("Dungeon", PropertyInfo(Variant::DICTIONARY, "dungeon"), "set_dungeon", "get_dungeon");

    ClassDB::bind_method(D_METHOD("get_size"), &Dungeon::get_size);
    ClassDB::bind_method(D_METHOD("set_size", "p_size"), &Dungeon::set_size);
    ClassDB::add_property("Dungeon", PropertyInfo(Variant::INT, "size"), "set_size", "get_size");

    ClassDB::bind_method(D_METHOD("get_rooms"), &Dungeon::get_rooms);
    ClassDB::bind_method(D_METHOD("set_rooms", "p_rooms"), &Dungeon::set_rooms);
    ClassDB::add_property("Dungeon", PropertyInfo(Variant::INT, "rooms"), "set_rooms", "get_rooms");

    ClassDB::bind_method(D_METHOD("generate"), &Dungeon::generate);

    BIND_ENUM_CONSTANT(TILE_GRASS);
    BIND_ENUM_CONSTANT(TILE_YELLOW_GRASS);
    BIND_ENUM_CONSTANT(TILE_HOUSE);
    BIND_ENUM_CONSTANT(TILE_MOUNTAIN);
    BIND_ENUM_CONSTANT(TILE_FOREST);
}

Dungeon::Dungeon() {
    //add_layer(5);
    //add_layer(2);
    //dungeon.set_typed(Variant::INT, StringName(), Variant());
    //UtilityFunctions::print(StringName("test"));
//    dungeon.resize(100);
    size = 20;
    rng.randomize();
}

Dungeon::~Dungeon() {
}

void Dungeon::set_ring(Vector2i center, int radius, int type) {
    Vector2i hex = center + (directions[4] * radius);
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j < radius; j++) {
            dungeon[hex] = type;
            hex = hex + directions[i];
        }
    }
}

void Dungeon::set_spiral(Vector2i center, int radius, int type) {
    dungeon[center] = type;
    for (int i = 1; i <= radius; i++) {
        set_ring(center, i, type);
    }
}

int Dungeon::distance(Vector2i a, Vector2i b) {
    Vector2i d = a - b;
    return (abs(d.x) + abs(d.x + d.y) + abs(d.y)) / 2;
}

void Dungeon::path(Vector2i start, Vector2i end, int type) {
    int dis = distance(start, end);
    for (int i = 0; i <= dis; i++) {
        dungeon[local_to_map(map_to_local(start).lerp(map_to_local(end), i / (float)dis))] = type;
    }
}

void Dungeon::generate() {
   // UtilityFunctions::print(rooms);
//    set_ring(Vector2i(0, 0), 20, 1);
    set_spiral(Vector2i(0, 0), size-2, 1);
    TypedArray<Vector2i> cells = dungeon.keys();
    set_ring(Vector2i(0, 0), size-1, 1);
    set_ring(Vector2i(0, 0), size, 1);

    TypedArray<Vector2i> centers; //= new Vector2i[rooms];
    centers.resize(rooms);                                  
    int sizes[rooms]; //= new int[rooms];

    centers[0] = Vector2i(0, 0);
    sizes[0] = rng.randi_range(4, 5);
    set_spiral(centers[0], sizes[0], 0);

    for (int i = 1; i < rooms; i++) {
        //UtilityFunctions::print(cells.size());
        Vector2i center = cells[rng.randi_range(0, cells.size()-1)];
        centers[i] = center;
        sizes[i] = rng.randi_range(1, fmin(4, size -1 - fmax(fmax(abs(center.x), abs(center.y)), abs(-center.x-center.y))));
        UtilityFunctions::print(centers[i], sizes[i]);
        set_spiral(centers[i], sizes[i], 0);
    }
    Dictionary connected;
    for (int i = 0; i < rooms; i++) {
        int min = 2000000;
        int index = -1;
        for (int j = 0; j < rooms; j++) {
            int dis = distance(centers[i], centers[j]);
            if (i != j && dis < min && !connected.has(j)) {
                min = dis;
                index = j;
            }
        }
        if (index == -1) {
            UtilityFunctions::print("coundn't find room to connect");
        } else {
            path(centers[i], centers[index], 0);
            connected[i] = true;
        }


    }

  //  path(Vector2i(0, 0), Vector2i(19, 0), 0);
    
//    dungeon[Vector2i(0, 0)] = 0;
        /*for (int q = -5; q <= 5; q++) {
        int max = (5 < -q+5) ? 5 : -q+5;
        for (int r = (-5 > -q-5) ? -5 : -q-5; r <= max; r++) {
            if (q == 0) {
                dungeon[Vector2i(q, r)] = TILE_MOUNTAIN;
            } else if (r == 0) {
                dungeon[Vector2i(q, r)] = TILE_HOUSE;
            } else if (-q-r == 0) {
                dungeon[Vector2i(q, r)] = TILE_YELLOW_GRASS;
            } else
                dungeon[Vector2i(q, r)] = TILE_GRASS;
        }
    }*/
    //for (int i = 0; i < 10; i++) {
    //    dungeon[Vector2i(rng.randi_range(-10, 9), rng.randi_range(-10, 9))] = TILE_HOUSE;
    //}
}

int Dungeon::get_rooms() {
    return rooms;
}

void Dungeon::set_rooms(int p_rooms) { rooms = p_rooms; }

Dictionary Dungeon::get_dungeon() {
    return dungeon;
}

void Dungeon::set_dungeon(Dictionary p_dungeon) {
    dungeon = p_dungeon;
}

int Dungeon::get_size() {
    return size;
}

void Dungeon::set_size(Dungeon::TileType p_size) {
    size = p_size;
}
