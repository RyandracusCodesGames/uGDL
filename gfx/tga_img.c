#include "tga_img.h"
#include "bmp_img.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : tga_img.c
	Author  : Ryandracus Chapman
	Date 	: 6/1/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLReadPixelsTGA
	Purpose    : Reads the image data of a TGA image file and flushes those contents into an integer array
	Parameters : file - A reference to a standard library file structure
				 width - The width of the image
				 height - The height of the image
				 clut - The integer array to store the image data
				 cf - The color format, the bit depth, of our image
	Returns	   : void
=======================================================================================
*/
void uGDLReadPixelsTGA(FILE *file, int width, int height, int *clut, ColorFormat cf){
	if(file == NULL){
		return;
	}
	
	TGAHeader tga;
	
	fread(&tga.identsize, sizeof(tga.identsize), 1, file);
	fread(&tga.paltype, sizeof(tga.paltype), 1, file);
	fread(&tga.imgtype, sizeof(tga.imgtype), 1, file);
	fread(&tga.palstart, sizeof(tga.palstart), 1, file);
	fread(&tga.pallength, sizeof(tga.pallength), 1, file);
	fread(&tga.palbitdepth, sizeof(tga.palbitdepth), 1, file);
	fread(&tga.xstart, sizeof(tga.xstart), 1, file);
	fread(&tga.ystart, sizeof(tga.ystart), 1, file);
	fread(&tga.width, sizeof(tga.width), 1, file);
	fread(&tga.height, sizeof(tga.height), 1, file);
	fread(&tga.bitdepth, sizeof(tga.bitdepth), 1, file);
	fread(&tga.descriptor, sizeof(tga.descriptor), 1, file);
	
	if(tga.imgtype != TGA_RGB){
		printf("The uGDL currently only supports raw RGB image data!\n");
	}
	
	if(width != tga.width || height != tga.height){
		printf("Given width and height dimensions do not watch dimension given in TGA file!\n");
		printf("TGA Width = %d, TGA Height = %d\n", tga.width, tga.height);
	}
	
	switch(tga.bitdepth){
		case 24:{
			int i;
			for(i = 0; i < tga.width * tga.height; i++){
				struct Pixel* pixel = (struct Pixel*)malloc(sizeof(struct Pixel));
				fread(&(pixel->b),1,1,file);
				fread(&(pixel->g),1,1,file);
				fread(&(pixel->r),1,1,file);
				clut[i] = uGDL_RGB888(pixel->r,pixel->g,pixel->b); 
				free(pixel);
			}
		}break;
		case 16:{
			int i;
			for(i = 0; i < tga.width * tga.height; i++){
				int col;
				fread(&col,2,1,file);
				int r = getR(col, BGR_565);
				int g = getG(col, BGR_565);
				int b = getB(col, BGR_565);
				clut[i] = uGDL_RGB565(r,g,b);
			}
		}break;
	}
	
}
/*
=======================================================================================
	Function   : uGDLLoadCLUTTGA
	Purpose    : Streams all of the image data contained inside of an image to an integer array
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 width - The width of the image
				 height - The height of the image
	Returns	   : An integer array
=======================================================================================
*/
int* uGDLLoadCLUTTGA(char *name, ColorFormat cf, int width, int height){
	FILE *fp = fopen(name, "rb");
	
	if(fp == NULL){
		printf("File not found at %s\n",name);
	}
	
	int* clut = (int*)malloc(sizeof(int)*(width*height));
	
	uGDLReadPixelsTGA(fp,width,height,clut,cf);
	
	fclose(fp);
	
	return clut;
}
/*
=======================================================================================
	Function   : uGDLLoadSpriteTGA
	Purpose    : Streams all of the image data contained inside of an image to a sprite
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 spr - A reference to a sprite structure
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void uGDLLoadSpriteTGA(char *name, ColorFormat cf, uGDLSprite* spr, int width, int height){
	spr->width = width;
	spr->height = height;
	spr->cf = cf;
	spr->clut = uGDLLoadCLUTTGA(name,cf,width,height);
}
/*
=======================================================================================
	Function   : uGDLLoadTextureTGA
	Purpose    : Streams all of the TGA image data contained inside of a TGA image to a texture
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 tex - A reference to a texture structure
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void uGDLLoadTextureTGA(char *name, ColorFormat cf, uGDLTexture *tex, int width, int height){
	tex->width = width;
	tex->height = height;
	tex->tlut = uGDLLoadCLUTTGA(name,cf,width,height);
}
/*
=======================================================================================
	Function   : uGDLWriteImageTGA
	Purpose    : Writes all of the image data contained inside of an image structure to an old-school TGA image
	Parameters : img - An image structure
	Returns	   : void
=======================================================================================
*/
void uGDLWriteImageTGA(uGDLImage img){
	TGAHeader tga;
	tga.identsize = 0;
	tga.paltype = NO_PAL;
	tga.imgtype = TGA_RGB;
	tga.palstart = 0;
	tga.pallength = 0;
	tga.palbitdepth = 0;
	tga.xstart = 0;
	tga.ystart = 0;
	tga.width = img.width;
	tga.height = img.height;
	if(img.cf == RGB_888){
		tga.bitdepth = 24;
	}
	else{
		tga.bitdepth = 16;
	}
	tga.descriptor = 0;
	
	FILE *file = fopen(img.name, "wb");
	fwrite(&tga.identsize,sizeof(tga.identsize),1,file);
	fwrite(&tga.paltype,sizeof(tga.paltype),1,file);
	fwrite(&tga.imgtype,sizeof(tga.imgtype),1,file);
	fwrite(&tga.palstart,sizeof(tga.palstart),1,file);
	fwrite(&tga.pallength,sizeof(tga.pallength),1,file);
	fwrite(&tga.palbitdepth,sizeof(tga.palbitdepth),1,file);
	fwrite(&tga.xstart,sizeof(tga.xstart),1,file);
	fwrite(&tga.ystart,sizeof(tga.ystart),1,file);
	fwrite(&tga.width,sizeof(tga.width),1,file);
	fwrite(&tga.height,sizeof(tga.height),1,file);
	fwrite(&tga.bitdepth,sizeof(tga.bitdepth),1,file);
	fwrite(&tga.descriptor,sizeof(tga.descriptor),1,file);
	
	int x, y;
	for(y = 0; y < tga.height; y++){
		for(x = 0; x < tga.width; x++){
			int r = getR(img.clut[x+y*img.width], RGB_888);
			int g = getG(img.clut[x+y*img.width], RGB_888);
			int b = getB(img.clut[x+y*img.width], RGB_888);
			
			fwrite(&b,1,1,file);
			fwrite(&g,1,1,file);
			fwrite(&r,1,1,file);
		}
	}
	
	fclose(file);
}
/*
=======================================================================================
	Function   : uGDLCaptureScreenshotTGA
	Purpose    : Writes all of the data contained inside of a frame buffer to an old-school TGA image
	Parameters : buf - A frame buffer structure
	Returns	   : void
=======================================================================================
*/
void uGDLCaptureScreenshotTGA(FrameBuffer frame_buffer){
	uGDLImage img = uGDLCreateImage("screenshot.tga",frame_buffer.width,frame_buffer.height, frame_buffer.cf);
	uGDLSyncCLUT(&img,frame_buffer.VRAM);
	uGDLWriteImageTGA(img);
}
