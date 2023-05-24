#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "print.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : print.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

uGDLFont printfont;

/*
=======================================================================================
	Function   : uGDLInitDebugPrint
	Purpose    : Initializes our debug print font to begin debug functionality
	Parameters : 
	Returns	   : void
=======================================================================================
*/
void uGDLInitDebugPrint(){
	uGDLInitFont(&printfont, 9, 9);
}

/*
=======================================================================================
	Function   : uGDLPrint
	Purpose    : Prints a string to the window display with support for escape sequences and line wrapping
	Parameters : VRAM - A reference to the video memory of our window display
				 fmt - A string
	Returns	   : void
=======================================================================================
*/
void uGDLPrint(uint32_t *VRAM, char *fmt){
	float offsetx = 0, offsety = (HEIGHT - 9);
	int i;
	for(i = 0; i < strlen(fmt); i++){
		char c = fmt[i];
		
		if(c != '\0'){
			if(c == ' '){
				offsetx += 8;
			}
			else if(c == 'I' || c == '1' || c == '!' || c == '.' || c == ','){
				offsetx += 9;
				uGDLDrawChar(VRAM, printfont, c, offsetx, offsety, 1, 1);
				offsetx -= 5;
			}
			else if(c == '\n'){
				offsety -= 12;
				offsetx = 0;
			}
			else{
				offsetx += 8;
				uGDLDrawChar(VRAM, printfont, c, offsetx, offsety, 1, 1);
			}
		}
		
		if(offsetx >= WIDTH){
			offsetx = 0;
			offsety -= 12;
		}
	}
}
/*
=======================================================================================
	Function   : uGDLPrintf
	Purpose    : Prints a formatted string to the window display
	Parameters : VRAM - A reference to the video memory of the window display
				 fmt - A string
	Returns	   : void
=======================================================================================
*/
void uGDLPrintf(uint32_t *VRAM, char *fmt,...){
	va_list argptr;
	char msg[500];
	va_start(argptr, fmt);
	vsprintf(msg,fmt,argptr);
	va_end(argptr);
	
	uGDLPrint(VRAM, msg);
}
/*
=======================================================================================
	Function   : uGDLPrintColoredText
	Purpose    : Prints a string with a desired color to the window display
	Parameters : VRAM - A reference to the video memory of our window display
				 fmt - A string
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLPrintColoredText(uint32_t *VRAM, char *fmt, int col){
	float offsetx = 0, offsety = (HEIGHT - 9);
	int i;
	for(i = 0; i < strlen(fmt); i++){
		char c = fmt[i];
		
		if(c != '\0'){
			if(c == ' '){
				offsetx += 8;
			}
			else if(c == 'I' || c == '1' || c == '!' || c == '.' || c == ',' || c == '\''){
				offsetx += 9;
				uGDLDispBlendSpriteAndCol(VRAM, uGDLFindFontCharacter(printfont,c), offsetx, offsety, col, 0.65f);
				offsetx -= 5;
			}
			else if(c == '\n'){
				offsety -= 12;
				offsetx = 0;
			}
			else{
				offsetx += 8;
				uGDLDispBlendSpriteAndCol(VRAM, uGDLFindFontCharacter(printfont,c), offsetx, offsety, col, 0.65f);
			}
		}
		
		if(offsetx >= WIDTH){
			offsetx = 0;
			offsety -= 12;
		}
	}
}
