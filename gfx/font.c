#include "font.h"
#include "framebuffer.h"
#include <stdlib.h>
#include <string.h>

void uGDLInitFont(uGDLFont *font, int width, int height){
	font->width = width;
	font->height = height;
	font->font[0] = 'A';
	font->font[1] = 'B';
	font->font[2] = 'C';
	font->font[3] = 'D';
	font->font[4] = 'E';
	font->font[5] = 'F';
	font->font[6] = 'G';
	font->font[7] = 'H';
	font->font[8] = 'I';
	font->font[9] = 'J';
	font->font[10] = 'K';
	font->font[11] = 'L';
	font->font[12] = 'M';
	font->font[13] = 'N';
	font->font[14] = 'O';
	font->font[15] = 'P';
	font->font[16] = 'Q';
	font->font[17] = 'R';
	font->font[18] = 'S';
	font->font[19] = 'T';
	font->font[20] = 'U';
	font->font[21] = 'V';
	font->font[22] = 'W';
	font->font[23] = 'X';
	font->font[24] = 'Y';
	font->font[25] = 'Z';
	font->font[26] = '0';
	font->font[27] = '1';
	font->font[28] = '2';
	font->font[29] = '3';
	font->font[30] = '4';
	font->font[31] = '5';
	font->font[32] = '6';
	font->font[33] = '7';
	font->font[34] = '8';
	font->font[35] = '9';
	font->font[36] = '.';
	font->font[37] = ',';
	font->font[38] = '\'';
	font->font[39] = '?';
	font->font[40] = '!';
	font->font[41] = '-';
	font->font[42] = '&';
	
	uGDLLoadSprite("gfx/textures/fonts/A.bmp", RGB_888, &font->spr[0], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/B.bmp", RGB_888, &font->spr[1], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/C.bmp", RGB_888, &font->spr[2], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/D.bmp", RGB_888, &font->spr[3], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/EE.bmp", RGB_888, &font->spr[4], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/F.bmp", RGB_888, &font->spr[5], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/G.bmp", RGB_888, &font->spr[6], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/H.bmp", RGB_888, &font->spr[7], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/I.bmp", RGB_888, &font->spr[8], 3, 9);
	uGDLLoadSprite("gfx/textures/fonts/J.bmp", RGB_888, &font->spr[9], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/K.bmp", RGB_888, &font->spr[10], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/L.bmp", RGB_888, &font->spr[11], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/M.bmp", RGB_888, &font->spr[12], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/N.bmp", RGB_888, &font->spr[13], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/O.bmp", RGB_888, &font->spr[14], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/P.bmp", RGB_888, &font->spr[15], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/Q.bmp", RGB_888, &font->spr[16], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/R.bmp", RGB_888, &font->spr[17], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/S.bmp", RGB_888, &font->spr[18], 9, 9);	
	uGDLLoadSprite("gfx/textures/fonts/T.bmp", RGB_888, &font->spr[19], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/U.bmp", RGB_888, &font->spr[20], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/V.bmp", RGB_888, &font->spr[21], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/W.bmp", RGB_888, &font->spr[22], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/X.bmp", RGB_888, &font->spr[23], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/Y.bmp", RGB_888, &font->spr[24], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/Z.bmp", RGB_888, &font->spr[25], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/0.bmp", RGB_888, &font->spr[26], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/1.bmp", RGB_888, &font->spr[27], 3, 9);
	uGDLLoadSprite("gfx/textures/fonts/2.bmp", RGB_888, &font->spr[28], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/3.bmp", RGB_888, &font->spr[29], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/4.bmp", RGB_888, &font->spr[30], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/5.bmp", RGB_888, &font->spr[31], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/6.bmp", RGB_888, &font->spr[32], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/7.bmp", RGB_888, &font->spr[33], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/8.bmp", RGB_888, &font->spr[34], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/9.bmp", RGB_888, &font->spr[35], 9, 9);
	uGDLLoadSprite("gfx/textures/fonts/period.bmp", RGB_888, &font->spr[36], 4, 9);
	uGDLLoadSprite("gfx/textures/fonts/comma.bmp", RGB_888, &font->spr[37], 4, 9);
	uGDLLoadSprite("gfx/textures/fonts/apostrophe.bmp", RGB_888, &font->spr[38], 4, 10);
	uGDLLoadSprite("gfx/textures/fonts/question.bmp", RGB_888, &font->spr[39], 8, 9);
	uGDLLoadSprite("gfx/textures/fonts/exclamation.bmp", RGB_888, &font->spr[40], 3, 9);
	uGDLLoadSprite("gfx/textures/fonts/hyphen.bmp", RGB_888, &font->spr[41], 6, 9);
	uGDLLoadSprite("gfx/textures/fonts/and.bmp", RGB_888, &font->spr[42], 8, 9);
}

void uGDLAddSprite(uGDLFont *font, uGDLSprite spr, int index){
	font->spr[index] = spr;
}

uGDLSprite uGDLFindFontCharacter(uGDLFont font, char s){
	int i;
	for(i = 0; i < 44; i++){
		if(font.font[i] == s){
			return font.spr[i];
		}
	}
}

void uGDLFreeFont(uGDLFont font){
	int i;
	for(i = 0; i < 43; i++){
		free(font.spr[i].clut);
	}
}

void uGDLSetFontColor(uGDLFont font, int col){
	font.col = col;
	
	int i;
	for(i = 0; i < 43; i++){
		uGDLBlendSpriteAndCol(font.spr[i], col, 0.95f);
	}
}
