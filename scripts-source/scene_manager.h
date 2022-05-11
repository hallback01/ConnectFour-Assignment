#pragma once
#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

    class SceneManager : public Node {
        GODOT_CLASS(SceneManager, Node)

        public:
            static void _register_methods();

            void _init();
            void _ready();
            void switch_scene(const String scene);
    };
}