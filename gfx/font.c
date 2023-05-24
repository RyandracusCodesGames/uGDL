#include "font.h"
#include "framebuffer.h"
#include <stdlib.h>
#include <string.h>

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : font.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLInitFont
	Purpose    : Initializes the data members of a font structure to indicate the width, height, and bitmap data of a font
	Parameters : font - A reference to a font structure
				 width - The width of the font
				 height - The height of the font
	Returns	   : void
=======================================================================================
*/
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
	
	uGDLLoadSprite("gfx/textures/fonts/A.bmp", RGB_888, &font->spr[0], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/B.bmp", RGB_888, &font->spr[1], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/C.bmp", RGB_888, &font->spr[2], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/D.bmp", RGB_888, &font->spr[3], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/EE.bmp", RGB_888, &font->spr[4], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/F.bmp", RGB_888, &font->spr[5], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/G.bmp", RGB_888, &font->spr[6], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/H.bmp", RGB_888, &font->spr[7], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/I.bmp", RGB_888, &font->spr[8], font->width - 6, font->height);
	uGDLLoadSprite("gfx/textures/fonts/J.bmp", RGB_888, &font->spr[9], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/K.bmp", RGB_888, &font->spr[10], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/L.bmp", RGB_888, &font->spr[11], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/M.bmp", RGB_888, &font->spr[12], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/N.bmp", RGB_888, &font->spr[13], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/O.bmp", RGB_888, &font->spr[14], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/P.bmp", RGB_888, &font->spr[15], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/Q.bmp", RGB_888, &font->spr[16], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/R.bmp", RGB_888, &font->spr[17], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/S.bmp", RGB_888, &font->spr[18], font->width, font->height);	
	uGDLLoadSprite("gfx/textures/fonts/T.bmp", RGB_888, &font->spr[19], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/U.bmp", RGB_888, &font->spr[20], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/V.bmp", RGB_888, &font->spr[21], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/W.bmp", RGB_888, &font->spr[22], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/X.bmp", RGB_888, &font->spr[23], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/Y.bmp", RGB_888, &font->spr[24], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/Z.bmp", RGB_888, &font->spr[25], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/0.bmp", RGB_888, &font->spr[26], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/1.bmp", RGB_888, &font->spr[27], font->width - 6, font->height);
	uGDLLoadSprite("gfx/textures/fonts/2.bmp", RGB_888, &font->spr[28], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/3.bmp", RGB_888, &font->spr[29], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/4.bmp", RGB_888, &font->spr[30], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/5.bmp", RGB_888, &font->spr[31], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/6.bmp", RGB_888, &font->spr[32], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/7.bmp", RGB_888, &font->spr[33], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/8.bmp", RGB_888, &font->spr[34], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/9.bmp", RGB_888, &font->spr[35], font->width, font->height);
	uGDLLoadSprite("gfx/textures/fonts/period.bmp", RGB_888, &font->spr[36], font->width - 5, font->height);
	uGDLLoadSprite("gfx/textures/fonts/comma.bmp", RGB_888, &font->spr[37], font->width - 5, font->height);
	uGDLLoadSprite("gfx/textures/fonts/apostrophe.bmp", RGB_888, &font->spr[38], font->width - 6, font->height + 1);
	uGDLLoadSprite("gfx/textures/fonts/question.bmp", RGB_888, &font->spr[39], font->width - 1, font->height);
	uGDLLoadSprite("gfx/textures/fonts/exclamation.bmp", RGB_888, &font->spr[40], font->width - 6, font->height);
	uGDLLoadSprite("gfx/textures/fonts/hyphen.bmp", RGB_888, &font->spr[41], font->width - 3, font->height);
	uGDLLoadSprite("gfx/textures/fonts/and.bmp", RGB_888, &font->spr[42], font->width - 1, font->height);
}

void uGDLAddSprite(uGDLFont *font, uGDLSprite spr, int index){
	font->spr[index] = spr;
}

/*
=======================================================================================
	Function   : uGDLFindFontCharacter
	Purpose    : Perfoms linear search on font structure to find desired character sprite
	Parameters : font - A font structure
				 s - The character that we are using in the linear search
	Returns	   : A uGDLSprite structure
=======================================================================================
*/
uGDLSprite uGDLFindFontCharacter(uGDLFont font, char s){
	int i;
	for(i = 0; i < 44; i++){
		if(font.font[i] == s){
			return font.spr[i];
		}
	}
}
/*
=======================================================================================
	Function   : uGDLFreeFont
	Purpose    : Frees the allocated memory of our font structure
	Parameters : font - A font structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeFont(uGDLFont font){
	int i;
	for(i = 0; i < 43; i++){
		free(font.spr[i].clut);
	}
}
/*
=======================================================================================
	Function   : uGDLSetFontColor
	Purpose    : Sets the font to a desired color
	Parameters : font - A font structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLSetFontColor(uGDLFont font, int col){
	font.col = col;
	
	int i;
	for(i = 0; i < 43; i++){
		uGDLBlendSpriteAndCol(font.spr[i], col, 0.95f);
	}
}
