#ifndef LIGHTMAP_H
#define LIGHTMAP_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : lightmap.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#include "framebuffer.h"
#include "sprite.h"
#include "tile.h"
#include "texture.h"
#include "bmp_img.h"

#define LIGHTMAP 0x12
#define LIGHTMAP_INVERTED 0x14

typedef struct{
	int width, height;
	const int* clut;
	ColorFormat cf;
	int col;
	int type;
}uGDLLightmap;

void uGDLLoadLightmap(uGDLLightmap *lm, char * name, int width, int height, int col, ColorFormat cf, int type);
int uGDLGetLightPixel(uGDLLightmap lm, int x, int y);
void uGDLBindSpriteAndLightmap(uGDLSprite spr, uGDLLightmap lm);
void uGDLBindTextureAndLightmap(uGDLTexture tex, uGDLLightmap lm);
void uGDLBindTileAndLightmap(uGDLTile tile, uGDLLightmap lm);
void uGDLBindTilemapAndLightmap(uGDLTilemap *map, uGDLLightmap lm);
void uGDLBindVRAMAndLightmap(FrameBuffer *buf, int xsrc, int ysrc, int width, int height, uGDLLightmap lm);
#endif
