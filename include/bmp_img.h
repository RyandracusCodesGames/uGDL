#ifndef BMP_IMG_H
#define BMP_IMG_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "framebuffer.h"
#include "color.h"
#include "sprite.h"
#include "texture.h"
#include "image.h"
#include "dither.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : bmp_img.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#define SIZE 4096

typedef struct {             // Total: 54 bytes
  uint16_t  type;             // Magic identifier: 0x4d42
  uint32_t  size;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors  
  uint32_t  important_colors; // Important colors 
} BMPHeader;

struct Pixel
{
    unsigned char r, g, b, a;
};

void uGDLLoadSprite(char* name, ColorFormat cf, uGDLSprite* spr,int width, int height);
void uGDLLoadTexture(char* name, ColorFormat cf, uGDLTexture *tex, int width, int height);
void uGDLFreeTexture(uGDLTexture *tex);
void uGDLFreeSprite(uGDLSprite *spr);
int * uGDLLoadCLUT(char * name, ColorFormat cf, int width, int height);
void readPixelsBMP(FILE* file,struct Pixel*pArr[SIZE],int width,int height, int *clut, ColorFormat cf);
void removeAll(struct Pixel*pArr[SIZE],int width,int height);
void uGDLWriteImage(uGDLImage img);
void uGDLCaptureScreenshot(FrameBuffer buf);
void uGDLCaptureDitheredScreenshot(FrameBuffer buf, uGDLDither dither, int factor);
void uGDLLoadColorPalette(char * name, uGDL_PALETTE *pal);
#endif
