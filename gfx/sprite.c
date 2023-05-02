#include "sprite.h"
#include "color.h"
#include "draw.h"
#include "geometry.h"

int uGDLGetPixel(uGDLSprite spr, int x, int y){
	if(x >= 0 && y >= 0 && x < spr.width && y < spr.height){
		return spr.clut[x + y * spr.width];
	}
}

void uGDLSetPixel(uGDLSprite *spr, int x, int y, int col){
	if(x >= 0 && y >= 0 && x < spr->width && y < spr->height){
		spr->clut[x + y * spr->width] = col;
	}
}

int uGDLAllPixelsSameColor(uGDLSprite spr, int col){
	int flag;
	int i;
	for(i = 0; i < spr.width * spr.height; i++){
		flag = 0;
		if(spr.clut[i] == col){
			flag = 1;
		}
	}
	return flag;
}

void uGDLDispSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			if(uGDLGetPixel(spr, x,y) != erase){
			// && getR(uGDLGetPixel(spr, x, y), RGB_888) - 3 >= 0 && getG(uGDLGetPixel(spr, x, y), RGB_888) - 3 >= 0){
				uGDLPoint2D p = {x + tX, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, x, y));
			}
		}
	}
}

void uGDLDispAnim(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			if(uGDLGetPixel(spr, x,y) != erase){
				uGDLPoint2D p = {x + tY, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, x, y));
			}
		}
	}
}

void uGDLAnimSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			if(uGDLGetPixel(spr, x, spr.height - y) != erase){
				uGDLPoint2D p = {x + tX, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, x, spr.height - y));
			}
		}
	}
}

void uGDLScaleSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float sX, float sY){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			VRAM[(int)(x * sX + tX) + (int)((y + 220) * sY + tY) * WIDTH] = uGDLGetPixel(spr, x, y);
		}
	}
}

void uGDLBlendSprite(uGDLSprite spr1, uGDLSprite spr2, float factor){
	int x, y;
	for(y = 0; y < spr1.height; y++){
		for(x = 0; x < spr1.width; x++){
			int col1 = uGDLGetPixel(spr1, x, y);
			int col2 = uGDLGetPixel(spr2, x, y);
			uGDLSetPixel(&spr1, x, y, uGDLBlendColor(col1, col2, factor, RGB_888));
		}
	}
}

void uGDLBlendSpriteAndCol(uGDLSprite spr, int col, float factor){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			int col2 = uGDLGetPixel(spr, x, y);
			uGDLSetPixel(&spr, x, y, uGDLBlendColor(col2, col, factor, RGB_888));
		}
	}
}

void uGDLBlendSpriteAndColWithVRAM(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int col, float factor){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			if(uGDLGetPixel(spr, x, y) != 0x0){
				if(getR(uGDLGetPixel(spr, x, y), RGB_888) >= 168 && getR(uGDLGetPixel(spr, x, y), RGB_888) <= 180){
					uGDLPoint2D p = {x + tX, y + tY};
					uGDLDrawPoint(VRAM, p,uGDLBlendColor(uGDLGetPixel(spr, x, y),col, factor, RGB_888));
				}
				else{
					uGDLPoint2D p = {x + tX, y + tY};
					uGDLDrawPoint(VRAM, p, uGDLBlendColor(uGDLGetPixel(spr, x, y),col, factor+0.30f, RGB_888));
				}
			}
		}
	}
}

void uGDLBlendSpriteTransparent(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, float factor){
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			int col = uGDLGetScreenPixel(VRAM, x, y, 0, 1);
			uGDLPoint2D p = {x + tX, y + tY};
			uGDLDrawPoint(VRAM, p, uGDLBlendColor(uGDLGetPixel(spr, x, y), col, factor, RGB_888));
		}
	}
}

void uGDLFlipSpriteVert(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type){
	if(img_type == BMP){
		int x, y;
		for(y = 0; y < spr.height; y++)
		{
			for(x = 0; x < spr.width; x++)
			{
				uGDLPoint2D p = {x + tX, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, x, spr.height - y));
			}
		}
	}
	else{
		int x, y;
		for(y = 0; y < spr.height; y++)
		{
			for(x = 0; x < spr.width; x++)
			{
				uGDLPoint2D p = {x + tX, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, x, spr.height));
			}
		}
	}
}

void uGDLFlipSpriteHorz(uint32_t *VRAM, uGDLSprite spr, int tX, int tY, int img_type, int erase){
	if(img_type == BMP){
		int x, y;
		for(y = 0; y < spr.height; y++)
		{
			for(x = 1; x < spr.width; x++)
			{
				if(uGDLGetPixel(spr, spr.width - x, y) != erase){
					uGDLPoint2D p = {x + tX, y + tY};
					uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, spr.width - x, y));
				}
			}
		}
	}
	else{
		int x, y;
		for(y = 0; y < spr.height; y++)
		{
			for(x = 0; x < spr.width; x++)
			{
				uGDLPoint2D p = {x + tX, y + tY};
				uGDLDrawPoint(VRAM, p, uGDLGetPixel(spr, spr.width - x, spr.height - y));
			}
		}
	}
}
