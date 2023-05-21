#ifndef ANIM_SPRITE
#define ANIM_SPRITE 

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
#endif
