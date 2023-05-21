#include "animsprite.h"

/*Local variables to hold sprite counter variable*/
int spriteCounter = 0;
int spriteNum = -1;

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
