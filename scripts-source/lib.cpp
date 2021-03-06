//why this file is here:
//https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html
#include <Godot.hpp>
#include "board_controller.h"
#include "scene_manager.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    
    godot::register_class<godot::BoardController>();
    godot::register_class<godot::SceneManager>();
}