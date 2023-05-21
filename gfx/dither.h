#ifndef DITHER_H
#define DITHER_H

#include "color.h"
#include "sprite.h"
#include "texture.h"
#include "canvas.h"
#include "image.h"
#include "framebuffer.h"
#include "draw.h"

typedef enum uGDLDither{
	DITHER_FLOYD_STEINBERG = 0,
	DITHER_ORDERED = 1,
}uGDLDither;

int uGDLQuantizeImageColor(int col, int factor, ColorFormat cf);
int uGDLErrorDiffuseColor(int col, float errR, float errG, float errB, float top, float bottom, ColorFormat cf);
void uGDLDitherSprite(uGDLSprite spr, uGDLDither dither, int factor);
void uGDLDitherTexture(uGDLTexture tex, uGDLDither dither, int factor, ColorFormat cf);
void uGDLDitherCanvas(uGDLCanvas *canvas, uGDLDither dither, int factor);
void uGDLDitherImage(uGDLImage img, uGDLDither dither, int factor);
void uGDLDitherFrameBuffer(FrameBuffer *buf, uGDLDither dither, int factor);
#endif
