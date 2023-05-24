#include "lightmap.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : lightmap.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLLoadLightmap
	Purpose    : Loads a lightmap into memory using an image in a file directory
	Parameters : lm - A reference to a lightmap structure
				 name - The directory, file name, and file extension of our image
				 width - The width of the image
				 height - The height of the image
				 col - The color desired to be binded to a sprite, texture, or image
				 cf - The color format, bit depth, of the image
				 type - The type of lightmap, inverted or standard, see header file for macros
	Returns	   : void
=======================================================================================
*/
void uGDLLoadLightmap(uGDLLightmap *lm, char * name, int width, int height, int col, ColorFormat cf, int type){
	lm->width = width;
	lm->height = height;
	lm->col = col;
	lm->cf = cf;
	lm->type = type;
	lm->clut = uGDLLoadCLUT(name, cf, width, height);
}
/*
=======================================================================================
	Function   : uGDLGetLightPixel
	Purpose    : Returns the color located at the specificed coordinates of the lightmap
	Parameters : x - The x - coordinate
				 y - The y - coordinate
	Returns	   : A color packed into an integer.
=======================================================================================
*/
int uGDLGetLightPixel(uGDLLightmap lm, int x, int y){
	if(x >= 0 && y >= 0 && x < lm.width && y < lm.height){
		return lm.clut[x + y * lm.width];
	}
}
/*
=======================================================================================
	Function   : uGDLBindSpriteAndLightmap
	Purpose    : Binds the lightmap to a sprite
	Parameters : spr - A sprite structure
				 lm - A lightmap structure
	Returns	   : void
=======================================================================================
*/
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
/*
=======================================================================================
	Function   : uGDLBindTextureAndLightmap
	Purpose    : Binds the lightmap to a texture
	Parameters : tex - A texture structure
				 lm - A lightmap structure
	Returns	   : void
=======================================================================================
*/
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
/*
=======================================================================================
	Function   : uGDLBindTileAndLightmap
	Purpose    : Binds the lightmap to a tile
	Parameters : tile - A tile structure
				 lm - A lightmap structure
	Returns	   : void
=======================================================================================
*/
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
/*
=======================================================================================
	Function   : uGDLBindTilemapAndLightmap
	Purpose    : Binds the lightmap to a tilemap
	Parameters : map - A reference to a tilemap structure
				 lm - A lightmap structure
	Returns	   : void
=======================================================================================
*/
void uGDLBindTilemapAndLightmap(uGDLTilemap *map, uGDLLightmap lm){
	int i;
	for(i = 0; i < map->index; i++){
		uGDLBindTileAndLightmap(map->map[i], lm);
	}
}
/*
=======================================================================================
	Function   : uGDLBindVRAMAndLightmap
	Purpose    : Binds the lightmap to a the video memory of our window display
	Parameters : buf - A reference to a frame buffer structure
				 xsrc - The starting x - coordinate to bind
				 ysrc - The starting y - coordinate to bind
				 width - The width of the bind
				 height - The height of the bind
				 lm - A lightmap structure
	Returns	   : void
=======================================================================================
*/
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
