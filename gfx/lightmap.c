#include "lightmap.h"

void uGDLLoadLightmap(uGDLLightmap *lm, char * name, int width, int height, int col, ColorFormat cf, int type){
	lm->width = width;
	lm->height = height;
	lm->col = col;
	lm->cf = cf;
	lm->type = type;
	lm->clut = uGDLLoadCLUT(name, cf, width, height);
}

int uGDLGetLightPixel(uGDLLightmap lm, int x, int y){
	if(x >= 0 && y >= 0 && x < lm.width && y < lm.height){
		return lm.clut[x + y * lm.width];
	}
}

void uGDLBindSpriteAndLightmap(uGDLSprite spr, uGDLLightmap lm){
	if(lm.width != spr.width  || lm.height != spr.height){
		printf("Dimensions of lightmap out of sync with sprite!\n");
	}
	
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
						
			int col = uGDLGetPixel(spr, x, y);
			int col2 = uGDLGetLightPixel(lm, x, y);
			
			float blend_factor = getR(col2, lm.cf) / 255.00f;						
			
			if(lm.type == LIGHTMAP_INVERTED){
				int blend = uGDLBlendColor(col, lm.col, blend_factor, lm.cf);
				uGDLSetPixel(&spr, x, y, blend);								
			}
			else{
				int blend = uGDLBlendColor(col, lm.col, 1 - blend_factor, lm.cf);				
				uGDLSetPixel(&spr, x, y, blend);				
			}									
			
		}
	}	
}

void uGDLBindTextureAndLightmap(uGDLTexture tex, uGDLLightmap lm){
	if(lm.width != tex.width  || lm.height != tex.height){
		printf("Dimensions of lightmap out of sync with texture!\n");
	}
	
	int x, y;
	for(y = 0; y < tex.height; y++){
		for(x = 0; x < tex.width; x++){
						
			int col = uGDLGetTexel(tex, x, y);
			int col2 = uGDLGetLightPixel(lm, x, y);
			
			float blend_factor = getR(col2, lm.cf) / 255.00f;						
			
			if(lm.type == LIGHTMAP_INVERTED){
				int blend = uGDLBlendColor(col, lm.col, blend_factor, lm.cf);
				uGDLSetTexel(&tex, x, y, blend);								
			}
			else{
				int blend = uGDLBlendColor(col, lm.col, 1 - blend_factor, lm.cf);				
				uGDLSetTexel(&tex, x, y, blend);				
			}									
			
		}
	}	
}

void uGDLBindTileAndLightmap(uGDLTile tile, uGDLLightmap lm){
	if(lm.width != W || lm.height != H){
		printf("Dimension of lightmap out of sync with tile!\n");
	}
	
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			int col = uGDLGetTileTexel(tile, x, y);
			int col2 = uGDLGetLightPixel(lm, x, y);
			
			float blend_factor = getR(col2, lm.cf) / 255.00f;
			
			if(lm.type == LIGHTMAP_INVERTED){
				int blend = uGDLBlendColor(col, lm.col, blend_factor, lm.cf);
				uGDLSetTileTexel(&tile, x, y, blend);								
			}
			else{
				int blend = uGDLBlendColor(col, lm.col, 1 - blend_factor, lm.cf);				
				uGDLSetTileTexel(&tile, x, y, blend);				
			}
		}
	}
}

void uGDLBindTilemapAndLightmap(uGDLTilemap *map, uGDLLightmap lm){
	int i;
	for(i = 0; i < map->index; i++){
		uGDLBindTileAndLightmap(map->map[i], lm);
	}
}

void uGDLBindVRAMAndLightmap(FrameBuffer *buf, int xsrc, int ysrc, int width, int height, uGDLLightmap lm){
	int x, y;
	for(y = ysrc; y < height; y++){
		for(x = xsrc; x < width; x++){
			int col = uGDLGetScreenPixel(buf->VRAM, x, y, 0, SCREEN_POINT);
			int col2 = uGDLGetLightPixel(lm, x, y);
			
			float blend_factor = getR(col2, lm.cf) / 255.00f;
			
			if(lm.type == LIGHTMAP_INVERTED){
				int blend = uGDLBlendColor(col, lm.col, blend_factor, lm.cf);
				buf->VRAM[x + y * buf->width] = blend;							
			}
			else{
				int blend = uGDLBlendColor(col, lm.col, 1 - blend_factor, lm.cf);				
				buf->VRAM[x + y * buf->width] = blend;				
			}
		}
	}
}
