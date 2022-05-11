#pragma once
#include <Godot.hpp>
#include <Node2D.hpp>
#include <Color.hpp>
#include <Label.hpp>
#include <NodePath.hpp>
#include <PackedScene.hpp>
#include <Sprite.hpp>

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
            Color tile_color;
            Turn turn;
            NodePath turn_text_path;
            Label* turn_text;

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

            void change_turn();
            void update_turn_text();

            void process_player(float delta);
            void process_ai(float delta);
            void ready_player();
            void ready_ai();
            Vector2 get_token_start_position(const Vector2 position);
            uint8_t get_token_index(const Vector2 position);

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void _process(float delta);
            void _draw();
    };

}