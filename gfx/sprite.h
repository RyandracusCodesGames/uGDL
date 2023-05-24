#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include "framebuffer.h"
#include "canvas.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : sprite.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/


#define WIDTH 624
#define HEIGHT 441

#define BMP 1

typedef struct{
	int width;
	int height;
	ColorFormat cf;
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
void uGDLBlendSpriteMode(uGDLSprite spr1, uGDLSprite spr2, float factor, int mode);
void uGDLBlendSpriteAndColMode(uGDLSprite spr, int col, float factor, int mode);
void uGDLBlendSpriteAndColWithVRAM(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int col, float factor);
void uGDLDispBlendSpriteAndCol(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int col, float factor);
/*Semi-Transparency similar to N64 where you blend a sprite's pixels with the color value already placed in the framebuffer*/
void uGDLBlendSpriteTransparent(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float factor);
void uGDLFlipSpriteVert(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type);
void uGDLFlipSpriteHorz(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type, int erase);
void uGDLRotSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float angle);
uGDLSprite uGDLClipSprite(uGDLSprite spr, int x, int y, int width, int height);
/*Grayscale is the process of taking the average of the RGB Components and using that same resulting value
/*as a new RGB triplet for each new component(Shades of gray always have equal RGB Components)*/
void uGDLConvertSpriteToGrayscale(uint32_t *VRAM, uGDLSprite spr, int tX, int tY);
void uGDLGrayscaleSprite(uGDLSprite *spr);
/*Canvas Equivalent Sprite Functions*/
void uGDLDispSpriteOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, int erase);
void uGDLDispAnimOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, int erase);
void uGDLAnimSpriteOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, int erase);
void uGDLScaleSpriteOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, float sX, float sY);
void uGDLBlendSpriteTransparentOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, float factor);
void uGDLFlipSpriteVertOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, int img_type);
void uGDLFlipSpriteHorzOnCanvas(uGDLCanvas *canvas, uGDLSprite spr, int tX, int tY, int img_type, int erase);
#endif
