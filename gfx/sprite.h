#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>

#define WIDTH 624
#define HEIGHT 441

#define BMP 1

typedef struct{
	int width;
	int height;
	int* clut;
}uGDLSprite;

int uGDLGetPixel(uGDLSprite spr, int x, int y);
void uGDLSetPixel(uGDLSprite *spr, int x, int y, int col);
int uGDLAllPixelsSameColor(uGDLSprite spr, int col);
void uGDLDispSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase);
void uGDLDispAnim(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase);
void uGDLAnimSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase);
void uGDLScaleSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float sX, float sY);
void uGDLBlendSprite(uGDLSprite spr1, uGDLSprite spr2, float factor);
void uGDLBlendSpriteAndCol(uGDLSprite spr, int col, float factor);
void uGDLBlendSpriteAndColWithVRAM(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int col, float factor);
/*Semi-Transparency similar to N64 where you blend a sprite's pixels with the color value already placed in the framebuffer*/
void uGDLBlendSpriteTransparent(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float factor);
void uGDLFlipSpriteVert(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type);
void uGDLFlipSpriteHorz(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type, int erase);
void uGDLRotSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float angle);

#endif
