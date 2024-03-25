#ifndef GDMESH_H
#define GDMESH_H

#include "GDDisplay.h"

#include "core/templates/vector.h"

DRAGONBONES_USING_NAME_SPACE;

class GDMesh : public GDDisplay
{ 
    GDCLASS(GDMesh, GDDisplay);

private:
    GDMesh(const GDMesh&);

public:
    PackedInt32Array					indices;
    PackedColorArray						verticesColor;
    PackedVector2Array						verticesUV;
    PackedVector2Array						verticesPos;

    Color                               col_debug;

public:
    GDMesh(){ col_debug = Color( 0.6f, 0.6f, 0.6f, 1);}
	virtual ~GDMesh() {}

	void dispatch_event(const String &_str_type, const EventObject *_p_value) {
		if (p_owner != nullptr) {
			p_owner->dispatch_event(_str_type, _p_value);
		}
	}

	void dispatch_snd_event(const String &_str_type, const EventObject *_p_value) {
		if (p_owner != nullptr) {
			p_owner->dispatch_snd_event(_str_type, _p_value);
		}
	}

    static  GDMesh* create()
    {
        return memnew(GDMesh);
    }

    void _render()
	{
        if (indices.is_empty())
			return;

        if(texture.is_valid())
        {
			VISUAL_SERVER_NAMESPACE::get_singleton()->canvas_item_add_triangle_array(
                get_canvas_item(),
                indices,
                verticesPos,
                verticesColor,
                verticesUV,

                PackedInt32Array(),
                PackedFloat32Array(),

                texture.is_valid() ? texture->get_rid() : RID(),
                -1
            );
        }

        if(b_debug || !texture.is_valid())
        {
            for (int idx = 0; idx < indices.size(); idx += 3)
            {
				VISUAL_SERVER_NAMESPACE::get_singleton()->canvas_item_add_line(get_canvas_item(), verticesPos[indices[idx]], verticesPos[indices[idx + 1]], col_debug, 1.0);
				VISUAL_SERVER_NAMESPACE::get_singleton()->canvas_item_add_line(get_canvas_item(), verticesPos[indices[idx + 1]], verticesPos[indices[idx + 2]], col_debug, 1.0);
				VISUAL_SERVER_NAMESPACE::get_singleton()->canvas_item_add_line(get_canvas_item(), verticesPos[indices[idx + 2]], verticesPos[indices[idx]], col_debug, 1.0);
            }
        }
	}

    virtual void set_modulate(const Color& _col)
    {
        GDDisplay::set_modulate(_col);
        col_debug.a = modulate.a;
        for(int i = 0; i < verticesColor.size(); ++i)
        {
            verticesColor.write[i] = modulate;
        }
    }

    void _notification(int p_what)
    {

        switch (p_what)
        {
            case NOTIFICATION_DRAW:
                _render();
                break;
        }
    }
};

#endif // #ifndef GDMESH_H