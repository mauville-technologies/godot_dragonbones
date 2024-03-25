#ifndef GDBONE2D_H
#define GDBONE2D_H

#include "dragonBones/DragonBonesHeaders.h"
#include <memory>
#include "scene/2d/skeleton_2d.h"

DRAGONBONES_USING_NAME_SPACE;

class GDBone2D : public Bone2D {
	GDCLASS(GDBone2D, Bone2D);

protected:
	dragonBones::Bone *boneData;

public:
	static GDBone2D *create() {
		return memnew(GDBone2D);
	};

	static void _bind_methods();

	void set_data(dragonBones::Bone *new_bone);

	String get_bone_name();
	Vector2 get_bone_position();
	void set_bone_position(Vector2 new_pos);
	void set_bone_global_position(Vector2 new_pos);
	Vector2 get_bone_scale();
	void set_bone_scale(Vector2 scale);
	void set_bone_global_scale(Vector2 scale);
	float get_bone_rotation();
	void set_bone_rotation(float rotation);
	void set_bone_global_rotation(float rotation);
	Vector2 get_bone_global_position();
	Vector2 get_bone_global_scale();
	float   get_bone_global_rotation();
	Vector2 get_bone_offset_position();
	Vector2 get_bone_animation_position();
	Vector2 get_bone_origin_position();
	bool has_data();

	GDBone2D() {set_autocalculate_length_and_angle(false);}
};

#endif