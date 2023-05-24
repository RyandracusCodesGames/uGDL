#include "animsprite.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : animsprite.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*Local variables to hold sprite counter variable*/
int spriteCounter = 0;
int spriteNum = -1;

/*
=======================================================================================
	Function   : uGDLInitSpriteAnim
	Purpose    : Loades in the animations contained inside of a spritesheet for 2D-Character animation
	Parameters : sheet - A reference to a sprite sheet structure
				 name - The current directory, file name, and file extension of our spritesheet
				 width - The width of the image
				 height - The height of the image
				 cellw - The width of each cell, the individual sub frames of a row
				 cellh - The height of each cell, the individual sub frames of a row
				 cf - The color format, the bit depth, of the image
	Returns	   : void
=======================================================================================
*/
void uGDLInitSpriteAnim(uGDLAnimSprites *sheet, char * name, int width, int height, int cellw, int cellh, ColorFormat cf){
	int *clut = uGDLLoadCLUT(name, cf, width, height);
	
	int x, y, col = 0, row = 0;
	for(y = 0; y <= height - cellh; y+=cellh){
		for(x = 0; x <= width - cellw; x+=cellw){
			int* tempCLUT = (int*)malloc(sizeof(int)*(cellw*cellh));
			int i, j;
			for(j = 0; j < cellh; j++){
				for(i = 0; i < cellw; i++){
					tempCLUT[i + j * cellw] = clut[(x + i) + (y + j) * width];
				}
			}
			uGDLSprite spr;
			spr.width = cellw;
			spr.height = cellh;
			spr.clut = tempCLUT;
			spr.cf = cf;
			sheet->sheet[row][col] = spr;
			col++;
		}
		row++;
	}
	
	sheet->rows = row;
	sheet->colms = col;
	sheet->oldrow = 0;
}
/*
=======================================================================================
	Function   : uGDLPlaySpriteAnim
	Purpose    : Iterates through a particular row of the spritesheet and returns the sprites contained in that row
	Parameters : sheet - A reference to a spritesheet structure
				 row - The desired row to iterate through its key-frame animations.
				 refresh - The cycle speed rate at which the function iterates through each column of the row
	Returns	   : A uGDLSprite structure.
=======================================================================================
*/
uGDLSprite uGDLPlaySpriteAnim(uGDLAnimSprites *sheet, int row, int refresh){
	if(row != sheet->oldrow){
		spriteCounter = 0;
		spriteNum = -1;
		sheet->oldrow = row;
	}
	if(row >= 0 && row <= sheet->rows){
		spriteCounter++;
		if(spriteCounter >= refresh){
			if(spriteNum >= sheet->colms-1){
				spriteNum = -1;
			}
			spriteCounter = 0;
			spriteNum++;
		}
		return sheet->sheet[row][spriteNum];
	}
}
/*
=======================================================================================
	Function   : uGDLFreeSpriteSheet
	Purpose    : Releases the allocated memory of the spritesheet
	Parameters : sheet - A reference to a spritesheet structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeSpriteSheet(uGDLAnimSprites *sheet){
	int i, j;
	for(j = 0; j < sheet->rows; j++){
		for(i = 0; i < sheet->colms; i++){
			free(sheet->sheet[j][i].clut);
		}
	}
}
