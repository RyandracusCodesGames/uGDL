#include "texture.h"

int uGDLGetTexel(uGDLTexture tex, int x, int y){
	if(x >= 0 && y >= 0 && x < tex.width && y < tex.height){
		return tex.tlut[x + y * tex.width];
	}
}

void uGDLSetTexel(uGDLTexture* tex, int x, int y, int col){
	if(x >= 0 && y >= 0 && x < tex->width && y < tex->height){
		tex->tlut[x + y * tex->width] = col;
	}
}

int countbits(int n){
	int count = 0;
    while (n > 0) {
        count+=(n & 1);
        n>>=1;
    }
    return count;
}
