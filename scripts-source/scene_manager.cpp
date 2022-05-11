#include "scene_manager.h"
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>

using namespace godot;

void SceneManager::_register_methods() {
    register_method("_ready", &SceneManager::_ready);
}

void SceneManager::_init() {

}

void SceneManager::_ready() {
    //load the game scene first 
    ResourceLoader* resource_loader = ResourceLoader::get_singleton();
    Ref<PackedScene> game_scene = resource_loader->load("res://Scenes/GameScene.tscn");
    add_child(game_scene->instance());
}

void SceneManager::switch_scene(const String scene) {
    get_child(0)->queue_free();
    ResourceLoader* resource_loader = ResourceLoader::get_singleton();
    Ref<PackedScene> game_scene = resource_loader->load(scene);
    add_child(game_scene->instance());
}