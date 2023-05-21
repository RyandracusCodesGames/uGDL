#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "print.h"

uGDLFont printfont;

void uGDLInitDebugPrint(){
	uGDLInitFont(&printfont, 9, 9);
}

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

void uGDLPrintf(uint32_t *VRAM, char *fmt,...){
	va_list argptr;
	char msg[500];
	va_start(argptr, fmt);
	vsprintf(msg,fmt,argptr);
	va_end(argptr);
	
	uGDLPrint(VRAM, msg);
}

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
