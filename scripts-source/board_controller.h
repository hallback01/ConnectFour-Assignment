#pragma once
#include <Godot.hpp>
#include <Node.hpp>
#include <Color.hpp>
#include <Label.hpp>
#include <NodePath.hpp>

namespace godot {

    class BoardController : public Node {
        GODOT_CLASS(BoardController, Node)

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

            void change_turn();
            void update_turn_text();

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void _process(float delta);
    };

}