#include "texture.h"
#include "color.h"
#include "draw.h"

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

void uGDLBlendTexture(uGDLTexture dest, uGDLTexture src, float factor, ColorFormat cf){
	int x, y;
	for(y = 0; y < dest.height; y++){
		for(x = 0; x < dest.width; x++){
			int col1 = uGDLGetTexel(dest, x, y);
			int col2 = uGDLGetTexel(src, x, y);
			uGDLSetPixel(&dest, x, y, uGDLBlendColor(col1, col2, factor, cf));
		}
	}
}

void uGDLBlendTextureAndCol(uGDLTexture dest, int col, float factor, ColorFormat cf){
	int x, y;
	for(y = 0; y < dest.height; y++){
		for(x = 0; x < dest.width; x++){
			int col1 = uGDLGetTexel(dest, x, y);
			uGDLSetTexel(&dest, x, y, uGDLBlendColor(col1, col, factor, cf));
		}
	}
}

void uGDLBlendTextureAndVRAM(uGDLTexture dest, uint32_t *VRAM, float factor, ColorFormat cf){
	int x, y;
	for(y = 0; y < dest.height; y++){
		for(x = 0; x < dest.width; x++){
			int col1 = uGDLGetScreenPixel(VRAM, x, y, 0, 1);
			uGDLSetTexel(&dest, x, y, uGDLBlendColor(uGDLGetTexel(dest, x, y), col1, factor, cf));
		}
	}
}

void uGDLFlipTextureVert(uGDLTexture tex, int image_type){
	int x, y;
	for(y = 0; y < tex.height; y++){
		for(x = 0; x < tex.width; x++){
			int col = uGDLGetTexel(tex, tex.width - x, y);
			uGDLSetTexel(&tex, x, y, col);
		}
	}
}

void uGDLFlipTextureHorz(uGDLTexture tex, int image_type){
	int x, y;
	for(y = 0; y < tex.height; y++){
		for(x = 0; x < tex.width; x++){
			int col = uGDLGetTexel(tex, x, tex.height - y);
			uGDLSetTexel(&tex, x, y, col);
		}
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
