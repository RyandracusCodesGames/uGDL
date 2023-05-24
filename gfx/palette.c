#include "palette.h"
#include "color.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : palette.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/


void uGDLLoadPalette(uGDLPalette *pal, char * name, char * extension){
	
	FILE *file = fopen(AppendString(name,pal),"rb");
	
	if(extension != ".pal" || fseek(file,3,SEEK_SET) != 0x50414C){
		printf("Palette must use uGDL based palette file format");
		return;
	}
	
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			int r, g, b;
			fread(&r,1,1,file);
			fread(&g,1,1,file);
			fread(&b,1,1,file);
			pal->pal[x + y * W] = uGDL_RGB888(r,g,b);
		}
	}
	
	fclose(file);
}

void uGDLWritePalette(uGDLPalette pal, char * name, int palet[MAX_COLORS]){
	FILE *file = fopen(AppendString(name,".pal"),"wb");
	
	if(file != NULL){
		printf("Could not open palette file!");
	}
	
	int header = 0x50414C;
	fwrite(&header,3,1,file);
	
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			int r = getR(pal.pal[x + y * W], RGB_888);
			int g = getG(pal.pal[x + y * W], RGB_888);
			int b = getB(pal.pal[x + y * W], RGB_888);
			fwrite(&r,1,1,file);
			fwrite(&g,1,1,file);
			fwrite(&b,1,1,file);
		}
	}
	
	fclose(file);
}

