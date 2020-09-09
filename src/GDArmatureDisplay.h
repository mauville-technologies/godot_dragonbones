#ifndef GDARMATUREDESPLAY_H
#define GDARMATUREDESPLAY_H

#include "scene/2d/node_2d.h"
#include "dragonBones/DragonBonesHeaders.h"
#include "GDDisplay.h"
#include "GDSlot.h"

#if (VERSION_MAJOR >= 3)
	#define CLASS_BIND_GODO ClassDB
	#define METH D_METHOD
	#define _SCS(val) val

#else

	#include "core/globals.h"

	#define CLASS_BIND_GODO ObjectTypeDB
	#define METH _MD

#endif


class GDArmatureDisplay : public GDDisplay, virtual public IArmatureProxy
{
#if (VERSION_MAJOR >= 3)
    GDCLASS(GDArmatureDisplay, GDDisplay);
#else
    OBJ_TYPE(GDArmatureDisplay, GDDisplay);
#endif
public:
	enum AnimMode {
		ANIMATION_PROCESS_FIXED,
		ANIMATION_PROCESS_IDLE,
	};

	enum AnimFadeOutMode {
		FadeOut_None,
		FadeOut_SameLayer,
		FadeOut_SameGroup,
		FadeOut_SameLayerAndGroup,
		FadeOut_All,
		FadeOut_Single
	};

private:
    GDArmatureDisplay(const GDArmatureDisplay&);

protected:
    Armature*           p_armature;
	Dictionary child_armatures;

public:
	GDArmatureDisplay();
	~GDArmatureDisplay();

    static GDArmatureDisplay* create()
    {
        return memnew(GDArmatureDisplay);
    }

	Dictionary get_child_armatures() { return child_armatures; };

	Slot *getSlot(const std::string &name) const;

    void addEvent(const std::string& _type, const std::function<void(EventObject*)>& _callback);
    void removeEvent(const std::string& _type);

    bool hasDBEventListener(const std::string& _type) const override { return true; }
    void addDBEventListener(const std::string& _type, const std::function<void(EventObject*)>& _listener) {}
    void removeDBEventListener(const std::string& _type, const std::function<void(EventObject*)>& _listener) {}
    void dispatchDBEvent(const std::string& _type, EventObject* _value);

    void dbInit(Armature* _p_armature) override;
	void dbClear() override;
	void dbUpdate() override;

	void dispose(bool disposeProxy) override;
	
	Armature* getArmature() const override { return p_armature; }
	Animation* getAnimation() const override { return p_armature->getAnimation(); }

    void    add_parent_class(bool _b_debug, const Ref<Texture>& _m_texture_atlas);
    void    update_childs(bool _b_color, bool _b_blending = false);
    void    update_texture_atlas(const Ref<Texture> &_m_texture_atlas);
    void    update_material_inheritance(bool _b_inherit_material);

public:
	/* METHOD BINDINGS */
	static void _bind_methods();

	bool is_frozen();
	void freeze();
	void thaw();
	void set_debug(bool _b_debug);

	bool has_animation(const String &_animation_name);
	Array get_animations();

	String get_current_animation() const;
	String get_current_animation_on_layer(int _layer) const;
	String get_current_animation_in_group(const String &_group_name) const;

	float tell_animation(const String &_animation_name);
	void seek_animation(const String &_animation_name, float progress);

	bool is_playing() const;
	void play(const String &_animation_name);
	void play_from_time(const String &_animation_name, float _f_time);
	void play_from_progress(const String &_animation_name, float f_progress);
	void stop(const String &_animation_name, bool b_reset = false);
	void stop_all_animations(bool b_children = false, bool b_reset = false);
	void fade_in(const String &_animation_name, float _time,
			int _loop, int _layer, const String &_group, GDArmatureDisplay::AnimFadeOutMode _fade_out_mode);

	void reset();

	bool has_slot(const String &_slot_name) const;
	Array get_slots();
	GDSlot_script *get_slot(const String &_slot_name);

	void flip_x(bool _b_flip);
	bool is_flipped_x() const;
	void flip_y(bool _b_flip);
	bool is_flipped_y() const;

};


VARIANT_ENUM_CAST(GDArmatureDisplay::AnimMode);
VARIANT_ENUM_CAST(GDArmatureDisplay::AnimFadeOutMode);

#endif // GDARMATUREDESPLAY_H
