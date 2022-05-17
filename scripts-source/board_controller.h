#pragma once
#include "board.h"
#include <Godot.hpp>
#include <Node2D.hpp>
#include <Color.hpp>
#include <Label.hpp>
#include <NodePath.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <Sprite.hpp>
#include <unordered_map>
#include <chrono>

namespace godot {

    class BoardController : public Node2D {
        GODOT_CLASS(BoardController, Node2D)

        private:

            enum Turn {
                Player,
                AI
            };

            uint8_t width;
            uint8_t height;
            uint32_t minimax_depth;
            Color tile_color;
            Turn turn;
            NodePath turn_text_path;
            Label* turn_text;
            ResourceLoader* resource_loader;
            bool is_playing = true;
            std::unordered_map<uint16_t, Sprite*> token_references;
            VictoryTokenCoordinates vct;
            TokenType victor;
            float win_animation_time = 10.0f;
            float timer = 0.0f;

            float texture_size;
            float scale;
            float scaled_texture_size;
            float x_offset;
            float y_offset;

            //state variables
            NodePath token_parent_path;
            Node2D* token_parent;
            Sprite* token;
            bool is_animating;
            Ref<PackedScene> token_scene;
            float gravitation_force;
            float gravitation;
            float end_y_position;
            Board board;

            void change_turn();
            void update_turn_text();
            uint16_t combine_coordinates(uint8_t x, uint8_t y);

            void ready_player();
            void ready_ai();
            Vector2 get_token_start_position(const Vector2 position);
            uint8_t get_token_index(const Vector2 position);
            void animate_token(float delta);

            //time
            float get_time();
            std::chrono::high_resolution_clock::time_point start;

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void _process(float delta);
            void _draw();
    };

}