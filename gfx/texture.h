#ifndef TEXTURE_H
#define TEXTURE_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : texture.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#include "framebuffer.h"
#include "color.h"
#include <stdint.h>

#define BMP 1

typedef struct{
	int width, height, widthMask, heightMask, widthShift;
	int *tlut;
}uGDLTexture;

int uGDLGetTexel(uGDLTexture tex, int x, int y);
void uGDLSetTexel(uGDLTexture *tex, int x, int y, int col);
void uGDLBlendTexture(uGDLTexture dest, uGDLTexture src, float factor, ColorFormat cf);
void uGDLBlendTextureAndCol(uGDLTexture dest, int col, float factor, ColorFormat cf);
void uGDLBlendTextureMode(uGDLTexture dest, uGDLTexture src, float factor, ColorFormat cf, int mode);
void uGDLBlendTextureAndColMode(uGDLTexture dest, int col, float factor, ColorFormat cf, int mode);
void uGDLBlendTextureAndVRAM(uGDLTexture dest, uint32_t *VRAM, float factor, ColorFormat cf);
void uGDLConvertTextureToGrayscale(uGDLTexture tex, int tX, int tY, ColorFormat cf);
void uGDLFlipTextureVert(uGDLTexture tex, int image_type);
void uGDLFlipTextureHorz(uGDLTexture tex, int image_type);
void uGDLClearTexture(uGDLTexture *tex, int col);
int countbits(int n);

#endif
