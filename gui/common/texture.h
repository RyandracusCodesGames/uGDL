#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct{
	int width, height, widthMask, heightMask, widthShift;
	int *tlut;
}uGDLTexture;

int uGDLGetTexel(uGDLTexture tex, int x, int y);
void uGDLSetTexel(uGDLTexture *tex, int x, int y, int col);
int countbits(int n);

#endif
