#ifndef ANIM_SPRITE
#define ANIM_SPRITE 

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : animsprite.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#include "framebuffer.h"
#include "sprite.h"
#include "bmp_img.h"

#define MAX_SHEET_NUM 30

typedef struct{
	int rows;
	int colms;
	int oldrow;
	uGDLSprite sheet[MAX_SHEET_NUM][MAX_SHEET_NUM];
}uGDLAnimSprites;

void uGDLInitSpriteAnim(uGDLAnimSprites *sheet, char * name, int width, int height, int cellw, int cellh, ColorFormat cf);
uGDLSprite uGDLPlaySpriteAnim(uGDLAnimSprites *sheet, int row, int refresh);
void uGDLFreeSpriteSheet(uGDLAnimSprites *sheet);
#endif
