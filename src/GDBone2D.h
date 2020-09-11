#ifndef GDBONE2D_H
#define GDBONE2D_H

#include "dragonBones/DragonBonesHeaders.h"
#include <memory>
#include "scene/2d/skeleton_2d.h"
#include "core/version_generated.gen.h"

#if (VERSION_MAJOR >= 3)
	#define CLASS_BIND_GODO ClassDB
	#define METH D_METHOD
	#define _SCS(val) val

#else

	#include "core/globals.h"

	#define CLASS_BIND_GODO ObjectTypeDB
	#define METH _MD

#endif

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
	Vector2 get_bone_scale();
	void set_bone_scale(Vector2 scale);
	float get_bone_rotation();
	void set_bone_rotation(float rotation);

	bool has_data();
};

#endif
