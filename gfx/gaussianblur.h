#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "framebuffer.h"
#include "color.h"
#include "image.h"
#include "texture.h"
#include "sprite.h"
#include "canvas.h"
#include "tile.h"

#define gauss_width 7

void uGDLDispGaussianSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY);
void uGDLMakeTextureGaussian(uGDLTexture tex);
void uGDLBlurCanvas(uGDLCanvas *canvas);
void uGDLBlurImage(uGDLImage img);

#endif
