#ifndef PALETTE_H
#define PALETTE_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : palette.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/


#include "bmp_img.h"

#define W 16
#define H 16
#define MAX_COLORS 256

typedef struct{
	int magic; /*0x50414C - PAL in ASCII*/
}uGDLPaletteHeader;

typedef struct{
	int pal[MAX_COLORS];
}uGDLPalette;

void uGDLLoadPalette(uGDLPalette *pal, char * name, char * extension);
void uGDLWritePalette(uGDLPalette pal, char * name, int palet[MAX_COLORS]);
#endif
