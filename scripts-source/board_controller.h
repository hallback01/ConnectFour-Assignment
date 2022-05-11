#pragma once
#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>

namespace godot {

    class BoardController : public Node {
        GODOT_CLASS(BoardController, Node)

        private:
            uint8_t width;
            uint8_t height;

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void _process(float delta);
    };

}