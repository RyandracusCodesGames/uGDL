#ifndef IMAGE_H
#define IMAGE_H

#define IMG_EXTENSION ".bmp"

typedef struct{
	int width, height;
	char * name;
	int* clut;
}uGDLImage;

uGDLImage uGDLCreateImage(char * name, int width, int height);
int uGDLGetImagePixel(uGDLImage img, int x, int y);
void uGDLSetImagePixel(uGDLImage *img, int x, int y);
void uGDLSyncCLUT(uGDLImage *img, int* clut);
void uGDLFreeImage(uGDLImage *img);

#endif
