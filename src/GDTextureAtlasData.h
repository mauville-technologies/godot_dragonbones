#ifndef GDTEXTUREATLAS_H
#define GDTEXTUREATLAS_H

#include "dragonBones/DragonBonesHeaders.h"

DRAGONBONES_USING_NAME_SPACE;
class GDTextureAtlasData : public TextureAtlasData
{
	BIND_CLASS_TYPE_B(GDTextureAtlasData);

public:
	GDTextureAtlasData();
	~GDTextureAtlasData();

    virtual TextureData* createTexture() const override;

    void setRenderTexture();
};

#endif // GDTEXTUREATLAS_H