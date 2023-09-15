#ifndef 	GDISPLAY_H
#define     GDISPLAY_H

#include "dragonBones/DragonBonesHeaders.h"
#include "scene/2d/node_2d.h"

DRAGONBONES_USING_NAME_SPACE;

class GDOwnerNode : public Node2D
{
	#define BLENDMODE_CLASS CanvasItemMaterial
	#define VISUAL_SERVER_NAMESPACE RenderingServer

    GDCLASS(GDOwnerNode, Node2D);

protected:
    static void _bind_methods() {}

public:
    Color		    modulate;

public:
    GDOwnerNode()  { modulate = Color(1,1,1,1); }
    virtual ~GDOwnerNode() {}

    virtual void set_modulate(const Color& _col)
    {
        modulate = _col;
    }

    virtual void dispatch_event(const String &_str_type, const EventObject* _p_value) {}
    virtual void dispatch_snd_event(const String &_str_type, const EventObject* _p_value) {}

    CanvasItemMaterial::BlendMode get_blend_mode()
    {
        return BLENDMODE_CLASS::BlendMode::BLEND_MODE_ADD;
    }
};

class GDDisplay : public GDOwnerNode
{
	GDCLASS(GDDisplay, GDOwnerNode);

protected:
    static void _bind_methods() {}

private:
    GDDisplay(const GDDisplay&);

public:
    Ref<Texture2D>    texture;
    CanvasItemMaterial* p_canvas_mat;

    GDOwnerNode*    p_owner;
    bool            b_debug;

public:
    GDDisplay()  {
                   p_owner = nullptr;
                   b_debug = false;
                   p_canvas_mat = memnew(CanvasItemMaterial);
				   set_material(p_canvas_mat);
                 }
    virtual ~GDDisplay() {}

    virtual void set_modulate(const Color& _col)
	{
		modulate = _col;
	}

	void set_blend_mode(BLENDMODE_CLASS ::BlendMode _blend)
    {
        p_canvas_mat->set_blend_mode((CanvasItemMaterial::BlendMode)_blend);
        Ref<CanvasItemMaterial> __mat = Ref<CanvasItemMaterial>(p_canvas_mat);
        set_material(__mat);
    }
};

#endif // GDISPLAY_H