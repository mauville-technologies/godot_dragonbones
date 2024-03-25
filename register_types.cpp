#include "register_types.h"
#include "gddragonbones.h"
#include "src/GDMesh.h"
#include "src/GDArmatureDisplay.h"

static Ref<ResourceFormatLoaderGDDragonBones> resource_loader_gddragonbones;

void initialize_godot_dragonbones_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

    ClassDB::register_class<GDOwnerNode>(true);
    ClassDB::register_class<GDDisplay>(true);
    
	ClassDB::register_class<GDArmatureDisplay>(true);
	ClassDB::register_class<GDSlot>(true);
	ClassDB::register_class<GDBone2D>(true);
	ClassDB::register_class<GDMesh>(true);

    ClassDB::register_class<GDDragonBonesResource>();
    ClassDB::register_class<GDDragonBones>();

	resource_loader_gddragonbones.instantiate();
	ResourceLoader::add_resource_format_loader(resource_loader_gddragonbones, true);
}

void uninitialize_godot_dragonbones_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ResourceLoader::remove_resource_format_loader(resource_loader_gddragonbones);
	resource_loader_gddragonbones.unref();
}