#pragma once
#include <Godot.hpp>
#include <Node2D.hpp>
#include <Color.hpp>
#include <Label.hpp>
#include <NodePath.hpp>

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

            void change_turn();
            void update_turn_text();

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void _process(float delta);
            void _draw();
    };

}