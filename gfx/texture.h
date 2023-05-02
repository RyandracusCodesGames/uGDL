#ifndef TEXTURE_H
#define TEXTURE_H

#include "framebuffer.h"
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
void uGDLBlendTextureAndVRAM(uGDLTexture dest, uint32_t *VRAM, float factor, ColorFormat cf);
void uGDLFlipTextureVert(uGDLTexture tex, int image_type);
void uGDLFlipTextureHorz(uGDLTexture tex, int image_type);
int countbits(int n);

#endif
