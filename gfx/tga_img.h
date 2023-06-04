#ifndef TGA_IMG_H
#define TGA_IMG_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : tga_img.h
	Author  : Ryandracus Chapman
	Date 	: 6/1/2023
	Version : 1.0
	
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "sprite.h"
#include "texture.h"
#include "image.h"

#define NO_PAL 0
#define HAS_PAL 1

typedef enum TGAType{
	TGA_NONE = 0,
	TGA_INDEXED = 1,
	TGA_RGB = 2,
	TGA_GRAYSCALE = 3,
	TGA_RLE = 4,
}TGAType;

typedef struct{
	
	unsigned char identsize;
	unsigned char paltype;
	unsigned char imgtype;
	
	short palstart;
	short pallength;
	unsigned char palbitdepth;
	
	short xstart;
	short ystart;
	short width;
	short height;
	unsigned char bitdepth;
	unsigned char descriptor;
	
}TGAHeader;


void uGDLReadPixelsTGA(FILE *file, int width, int height, int *clut, ColorFormat cf);
int* uGDLLoadCLUTTGA(char* name, ColorFormat cf, int width, int height);
void uGDLLoadSpriteTGA(char* name, ColorFormat cf, uGDLSprite* spr, int width, int height);
void uGDLLoadTextureTGA(char* name, ColorFormat cf, uGDLTexture *tex, int width, int height);
void uGDLWriteImageTGA(uGDLImage img);
void uGDLCaptureScreenshotTGA(FrameBuffer frame_buffer);

#endif
