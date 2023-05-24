#ifndef PRINT_H
#define PRINT_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : print.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#include "framebuffer.h"
#include "color.h"
#include "sprite.h"
#include "canvas.h"
#include "draw.h"
#include "font.h"

extern uGDLFont printfont;

void uGDLInitDebugPrint();
void uGDLPrint(uint32_t *VRAM, char *fmt);
void uGDLPrintf(uint32_t *VRAM, char *fmt,...);
void uGDLPrintColoredText(uint32_t *VRAM, char *fmt, int col);

#endif
