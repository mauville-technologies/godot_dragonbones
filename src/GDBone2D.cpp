#include "GDBone2D.h"

void GDBone2D::_bind_methods() {
	CLASS_BIND_GODO::bind_method(METH("get_bone_name"), &GDBone2D::get_bone_name);
	CLASS_BIND_GODO::bind_method(METH("get_bone_position"), &GDBone2D::get_bone_position);
	CLASS_BIND_GODO::bind_method(METH("set_bone_position", "new_position"), &GDBone2D::set_bone_position);
	CLASS_BIND_GODO::bind_method(METH("get_bone_scale"), &GDBone2D::get_bone_scale);
	CLASS_BIND_GODO::bind_method(METH("set_bone_scale", "new_scale"), &GDBone2D::set_bone_scale);
	CLASS_BIND_GODO::bind_method(METH("get_bone_rotation"), &GDBone2D::get_bone_rotation);
	CLASS_BIND_GODO::bind_method(METH("set_bone_rotation", "deg_in_rad"), &GDBone2D::set_bone_rotation);
	CLASS_BIND_GODO::bind_method(METH("has_data"), &GDBone2D::has_data);
}

void GDBone2D::set_data(dragonBones::Bone *new_bone) {
	this->boneData = new_bone;
}

String GDBone2D::get_bone_name() {
	if (boneData == nullptr) return "";
	return String(boneData->getName().c_str());
}

Vector2 GDBone2D::get_bone_position() {
	if (boneData == nullptr) return Vector2();

	
	return Vector2(boneData->animationPose.x, boneData->animationPose.y);
}

void GDBone2D::set_bone_position(Vector2 new_pos) {
	if (boneData == nullptr) return;

	boneData->animationPose.x = new_pos.x;
	boneData->animationPose.y = new_pos.y;

	boneData->invalidUpdate();
}

Vector2 GDBone2D::get_bone_scale() {
	if (boneData == nullptr) return Vector2();

	return Vector2(boneData->animationPose.scaleX, boneData->animationPose.scaleY);
}

void GDBone2D::set_bone_scale(Vector2 scale) {
	if (boneData == nullptr) return;

	boneData->animationPose.scaleX = scale.x;
	boneData->animationPose.scaleY = scale.y;

	boneData->invalidUpdate();
}

float GDBone2D::get_bone_rotation() {
	if (boneData == nullptr) return 0.;


	return boneData->animationPose.rotation;
}

void GDBone2D::set_bone_rotation(float rotation) {
	if (boneData == nullptr) return;

	boneData->animationPose.rotation = rotation;
	boneData->update(0);
	boneData->invalidUpdate();
}

bool GDBone2D::has_data() {
	return this->boneData != nullptr;
}
