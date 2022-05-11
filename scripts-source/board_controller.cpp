#include "board_controller.h"
#include <ResourceLoader.hpp>
#include <Sprite.hpp>

using namespace godot;

void BoardController::_register_methods() {
    register_method("_ready", &BoardController::_ready);
    register_method("_process", &BoardController::_process);

    register_property<BoardController, uint8_t>("width", &BoardController::width, 7);
    register_property<BoardController, uint8_t>("height", &BoardController::height, 6);
}

void BoardController::_init() {
    width = 7;
    height = 6;
}

void BoardController::_ready() {

    //load the tile object scene
    ResourceLoader* resource_loader = ResourceLoader::get_singleton();
    Ref<PackedScene> board_tile = resource_loader->load("res://Scenes/Objects/Tile.tscn");

    //spawn the tiles
    const float texture_size = 256;
    const float scale = 0.25f;
    const float scaled_texture_size = (texture_size * scale);
    const float x_offset = ((-256.0*(float)width) / 2.0) * scale;
    const float y_offset = ((-256.0*(float)height) / 2.0) * scale + 128.0 - 32.0;
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {

            Sprite* tile = (Sprite*)board_tile->instance();

            //set it's position and scale
            tile->set_position(Vector2(x*scaled_texture_size + x_offset, y*scaled_texture_size + y_offset));
            tile->set_scale(Vector2(scale, scale));

            //add child to this node
            add_child(tile);
        }
    }
}

void BoardController::_process(float delta) {
    
}