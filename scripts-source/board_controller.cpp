#include "board_controller.h"
#include <ResourceLoader.hpp>
#include <Color.hpp>
#include <Input.hpp>
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
    register_property<BoardController, NodePath>("token_parent_path", &BoardController::token_parent_path, NodePath());
}

float clamp(float value, float min, float max) {
    if(value < min) {
        return min;
    } else if(value > max) {
        return max;
    } else {
        return value;
    }
}

void BoardController::_init() {
    width = 7;
    height = 6;
    tile_color = Color(0.0, 0.0, 1.0);
    is_animating = false;
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

    //load the token scene
    token_scene = resource_loader->load("res://Scenes/Objects/Token.tscn");

    //gather the token parent reference from the nodepath
    assert(!token_parent_path.is_empty());
    token_parent = (Node2D*)get_node(token_parent_path);
    assert(token_parent);

    //gather the turn text reference from the nodepath
    assert(!turn_text_path.is_empty());
    turn_text = (Label*)get_node(turn_text_path);
    assert(turn_text);

    //randomize who starts
    std::srand(std::time(nullptr));
    int random = std::rand() % 2;
    if(random == 0) {
        turn = Turn::Player;
        ready_player();
    } else if(random == 1) {
        turn = Turn::AI;
        ready_ai();
    }

    //set it to the correct text
    update_turn_text();
}

void BoardController::_process(float delta) {

    switch(turn) {
        case Turn::Player: process_player(delta); break;
        case Turn::AI: process_ai(delta); break;
    }
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

//switches turn and updates the "who's turn" text in the gui
void BoardController::change_turn() {
    
    if(turn == Turn::Player) {
        turn = Turn::AI;
        ready_ai();
    } else {
        turn = Turn::Player;
        ready_player();
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

/// ---- ready functions
void BoardController::ready_player() {
    Godot::print("Player's turn.");

    token = (Sprite*)token_scene->instance();
    token->set_modulate(Color(1.0, 1.0, 0.0));
    token->set_position(Vector2(10000.0, 10000.0)); //place it outside the screen for now
    token_parent->add_child(token);

}

void BoardController::ready_ai() {
    Godot::print("AI's turn.");

    token = (Sprite*)token_scene->instance();
    token->set_modulate(Color(1.0, 0.0, 0.0));
    token->set_position(Vector2(10000.0, 10000.0)); //place it outside the screen for now
    token_parent->add_child(token);
}

// ---- process functions
Vector2 BoardController::get_token_start_position(const Vector2 position) {
    float start_position = x_offset;
    float y_position = y_offset - scaled_texture_size - 16.0;
    float total_length = scaled_texture_size * (width-1);
    float percentage = clamp(position.x - start_position, 0, total_length) / total_length;
    return Vector2(start_position + ((int)(percentage * (width-1)) * scaled_texture_size), y_position);
}

uint8_t BoardController::get_token_index(const Vector2 position) {
    float start_position = x_offset;
    float total_length = scaled_texture_size * (width-1);
    float percentage = clamp(position.x - start_position, 0, total_length) / total_length;
    return percentage * (width-1);
}

void BoardController::process_player(float delta) {

    //droping the token
    if(is_animating) {

    } else {
        //chosing a token
        token->set_position(get_token_start_position(get_global_mouse_position()));

        Input* input = Input::get_singleton();
        if(input->is_action_pressed("drop")) {
            int index = get_token_index(get_global_mouse_position());
            Godot::print("Dropping");
            is_animating = true;
        }
    }
}

void BoardController::process_ai(float delta) {

    //dropping the token

}