#include "board_controller.h"
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>
#include <Sprite.hpp>
#include <Color.hpp>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace godot;

void BoardController::_register_methods() {
    register_method("_ready", &BoardController::_ready);
    register_method("_process", &BoardController::_process);
    register_method("_draw", &BoardController::_draw);

    register_property<BoardController, uint8_t>("width", &BoardController::width, 7);
    register_property<BoardController, uint8_t>("height", &BoardController::height, 6);
    register_property<BoardController, Color>("tile_color", &BoardController::tile_color, Color(0.0, 0.0, 1.0));
    register_property<BoardController, NodePath>("turn_text_path", &BoardController::turn_text_path, NodePath());
}

void BoardController::_init() {
    width = 7;
    height = 6;
    tile_color = Color(0.0, 0.0, 1.0);
}

void BoardController::_ready() {

    //initialize other constants
    texture_size = 256;
    scale = 0.25f;
    scaled_texture_size = (texture_size * scale);
    x_offset = ((-256.0*(float)width) / 2.0) * scale;
    y_offset = ((-256.0*(float)height) / 2.0) * scale + 96.0;

    //load the tile object scene
    ResourceLoader* resource_loader = ResourceLoader::get_singleton();
    Ref<PackedScene> board_tile = resource_loader->load("res://Scenes/Objects/Tile.tscn");

    //spawn the tiles
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {

            Sprite* tile = (Sprite*)board_tile->instance();

            //set it's position and scale
            tile->set_position(Vector2(x*scaled_texture_size + x_offset, y*scaled_texture_size + y_offset));
            tile->set_scale(Vector2(scale, scale));
            tile->set_modulate(tile_color);

            //add child to this node
            add_child(tile);
        }
    }

    //gather the turn text reference from the nodepath
    assert(!turn_text_path.is_empty());
    turn_text = (Label*)get_node(turn_text_path);
    assert(turn_text);

    //randomize who starts
    std::srand(std::time(nullptr));
    int random = std::rand() % 2;
    if(random == 0) {
        turn = Turn::Player;
    } else if(random == 1) {
        turn = Turn::AI;
    }

    //set it to the correct text
    update_turn_text();
}

void BoardController::_process(float delta) {
    
}

void BoardController::_draw() {

    //draw black border around the board
    Vector2 top_left = Vector2(x_offset, y_offset - 1);
    Vector2 top_right = Vector2(x_offset + scaled_texture_size * width + 1, y_offset - 1);
    Vector2 bot_left = Vector2(x_offset, y_offset + scaled_texture_size * height + 1);
    Vector2 bot_right = Vector2(x_offset + scaled_texture_size * width + 1, y_offset + scaled_texture_size * height);

    draw_line(top_left, top_right, Color(0.0, 0.0, 0.0));
    draw_line(bot_left, bot_right, Color(0.0, 0.0, 0.0));
    draw_line(top_left, bot_left, Color(0.0, 0.0, 0.0));
    draw_line(top_right, bot_right, Color(0.0, 0.0, 0.0));
}

void BoardController::change_turn() {

    //switches turn and updates the "who's turn" text in the gui
    if(turn == Turn::Player) {
        turn = Turn::AI;
    } else {
        turn = Turn::Player;
    }
    update_turn_text();
}

//updates the turn text depending on the built in "turn" variable
//turn_text cannot be null
void BoardController::update_turn_text() {
    assert(turn_text);

    switch(turn) {
        case Turn::Player:
            turn_text->set_text("Player's turn!");
            turn_text->add_color_override("font_color", Color(1.0, 1.0, 0.0)); //player is yellow
            break;

        case Turn::AI:
            turn_text->set_text("AI's turn!");
            turn_text->add_color_override("font_color", Color(1.0, 0.0, 0.0)); //ai is red
            break;
    }
}