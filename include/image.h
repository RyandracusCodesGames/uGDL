#ifndef IMAGE_H
#define IMAGE_H

#include "framebuffer.h"

#define IMG_EXTENSION ".bmp"

typedef struct{
	int width, height;
	char * name;
	ColorFormat cf;
	int* clut;
}uGDLImage;

uGDLImage uGDLCreateImage(char * name, int width, int height, ColorFormat cf);
int uGDLGetImagePixel(uGDLImage img, int x, int y);
void uGDLSetImagePixel(uGDLImage *img, int x, int y, int col);
void uGDLSyncCLUT(uGDLImage *img, int* clut);
void uGDLFreeImage(uGDLImage *img);
void uGDLCopyImageData(uGDLImage *src, uGDLImage *dest);
void uGDLClearImage(uGDLImage *img, int col);
void uGDLConvertImageToGrayscale(uGDLImage *img);
#endif
