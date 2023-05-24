#include <stdlib.h>
#include <string.h>
#include "bmp_img.h"
#include "color.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : bmp_img.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : readPixelsBMP
	Purpose    : Reads the image data of an image file and flushes those contents into an integer array
	Parameters : file - A reference to a standard library file structure
				 pArr - A reference to an array of pixel structures
				 width - The width of the image
				 height - The height of the image
				 clut - The integer array to store the image data
				 cf - The color format, the bit depth, of our image
	Returns	   : void
=======================================================================================
*/
void readPixelsBMP(FILE* file,struct Pixel*pArr[SIZE],int width,int height, int *clut, ColorFormat cf)
{
	if(file == NULL)
		return;
	
	// A Useful Variable 
	int padding = width % 4; 
	
	// Move 54Bytes (Header Size) 	
	fseek(file, 54, SEEK_SET);
	
	switch(cf){
		case RGB_888:{
			int i, j;
			int ind = 0;
			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
					pArr[ind] = (struct Pixel*)malloc(sizeof(struct Pixel));
					fread(&(pArr[ind]->b), 1, 1, file); 
					fread(&(pArr[ind]->g), 1, 1, file); 
					fread(&(pArr[ind]->r), 1, 1, file); 
					clut[ind] = uGDL_RGB888(pArr[ind]->r, pArr[ind]->g, pArr[ind]->b);
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
		}break;
		case BGR_888:{
			int i, j;
			int ind = 0;
			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
					pArr[ind] = (struct Pixel*)malloc(sizeof(struct Pixel));
					fread(&(pArr[ind]->b), 1, 1, file); 
					fread(&(pArr[ind]->g), 1, 1, file); 
					fread(&(pArr[ind]->r), 1, 1, file); 
					clut[ind] = uGDL_BGR888(pArr[ind]->b, pArr[ind]->g, pArr[ind]->r);
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
		}break;
		case RGBA_8888:{
			int i, j;
			int ind = 0;
			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
					pArr[ind] = (struct Pixel*)malloc(sizeof(struct Pixel));
					fread(&(pArr[ind]->b), 1, 1, file); 
					fread(&(pArr[ind]->g), 1, 1, file); 
					fread(&(pArr[ind]->r), 1, 1, file); 
					clut[ind] = uGDL_RGBA8888(pArr[ind]->r, pArr[ind]->g, pArr[ind]->b, 0xFF);
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
		}break;
		case RGB_565:{
			int i, j;
			int ind = 0;
			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
					int col;
					fread(&col,2,1,file);
					int r = getR(col, RGB_565);
					int g = getG(col, RGB_565);
					int b = getB(col, RGB_565);
					clut[ind] = uGDL_RGB565(r,g,b);
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
		}break;
		case BGR_565:{
			int i, j;
			int ind = 0;
			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
					int col;
					fread(&col,2,1,file);
					int r = getR(col, BGR_565);
					int g = getG(col, BGR_565);
					int b = getB(col, BGR_565);
					clut[ind] = uGDL_BGR565(b,g,r);
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
			
		}break;
	} 
 
}

/*
=======================================================================================
	Function   : displayPixels
	Purpose    : Displays each RGB triplet of our image data to the console window
	Parameters : pArr - A reference to an array of pixel structures
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void displayPixels(struct Pixel*pArr[SIZE],int width,int height)
{
	int i;
	for(i = 0; i < width * height; i++)
	{
		printf("(%d,%d,%d)",pArr[i]->r,pArr[i]->g,pArr[i]->b);
		
		if(i % height == 0){
			printf("\n");
		}
	}
}

/*
=======================================================================================
	Function   : removeAll
	Purpose    : Frees all the allocated memory of our pixel structures
	Parameters : pArr - A reference to an array of pixel structures
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void removeAll(struct Pixel*pArr[SIZE],int width,int height)
{
	int i;
	for(i=0;i<width*height;i++)
	{
		free(pArr[i]);
	}
}
/*
=======================================================================================
	Function   : uGDLFreeSprite
	Purpose    : Frees the allocated memory to our sprite structure
	Parameters : spr - A reference to a sprite structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeSprite(uGDLSprite *spr){
	free(spr->clut);
}
/*
=======================================================================================
	Function   : uGDLFreeTexture
	Purpose    : Frees the allocated memory to our texture structure
	Parameters : tex - A reference to a texture structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeTexture(uGDLTexture *tex){
	free(tex->tlut);
}
/*
=======================================================================================
	Function   : uGDLLoadSprite
	Purpose    : Streams all of the image data contained inside of an image to a sprite
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 spr - A reference to a sprite structure
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void uGDLLoadSprite(char* name, ColorFormat cf, uGDLSprite* spr, int width, int height){
	struct Pixel *A[width*height];
	FILE *fp=NULL;

	fp=fopen(name,"rb");
	
	if(fp == NULL){
		printf("NULL\n");
		printf("%s\n",name);
	}
	
	spr->clut = (int*)malloc(sizeof(int)*(width*height));
	
	readPixelsBMP(fp,A,width,height, spr->clut, cf);
	
	spr->width = width;
	spr->height = height;
	spr->cf = cf;

	removeAll(A,width,height);
	fclose(fp);	
}
/*
=======================================================================================
	Function   : uGDLLoadCLUT
	Purpose    : Streams all of the image data contained inside of an image to an integer array
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 width - The width of the image
				 height - The height of the image
	Returns	   : An integer array
=======================================================================================
*/
int * uGDLLoadCLUT(char * name, ColorFormat cf, int width, int height){
	struct Pixel *A[width*height];
	FILE *fp = fopen(name, "rb");
	
	if(fp == NULL){
		printf("NULL\n");
		printf("%s\n",name);
	}
	
	int* clut = (int*)malloc(sizeof(int)*(width*height));
	
	readPixelsBMP(fp,A,width,height,clut,cf);
	removeAll(A,width,height);
	fclose(fp);
	
	return clut;
}
/*
=======================================================================================
	Function   : uGDLLoadTexture
	Purpose    : Streams all of the image data contained inside of an image to a texture
	Parameters : name - The directory, name, and extension of the image
				 cf - The color format, the bit depth, of the image
				 tex - A reference to a texture structure
				 width - The width of the image
				 height - The height of the image
	Returns	   : void
=======================================================================================
*/
void uGDLLoadTexture(char* name, ColorFormat cf, uGDLTexture *tex, int width, int height){
	struct Pixel *A[width*height];
	FILE *fp=NULL;

	fp=fopen(name,"rb");
	
	tex->tlut = (int*)malloc(sizeof(int)*(width*height));
	
	readPixelsBMP(fp,A,width,height,tex->tlut,cf);
	
	tex->width = width;
	tex->height = height;
	tex->widthMask = width - 1;
	tex->heightMask = height - 1;
	tex->widthShift = countbits(width - 1);
	
	removeAll(A,width,height);
	fclose(fp);	
}
/*
=======================================================================================
	Function   : uGDLCreateImage
	Purpose    : Streams all of the image data contained inside of an image to a uGDL image structure
	Parameters : name - The directory, name, and extension of the image
				 width - The width of the image
				 height - The height of the image
				 cf - The color format, the bit depth, of the image
	Returns	   : A uGDLImage structure
=======================================================================================
*/
uGDLImage uGDLCreateImage(char * name, int width, int height, ColorFormat cf){
	uGDLImage img;
	img.name = name;
	img.width = width;
	img.height = height;
	img.clut = (int*)malloc(sizeof(int)*(width*height));
	img.cf = cf;
	return img;
}
/*
=======================================================================================
	Function   : uGDLSyncCLUT
	Purpose    : Streams all of the color data contained inside of an integer array to an image structure
	Parameters : img - A reference to an image structure
				 clut - An integer array
	Returns	   : void
=======================================================================================
*/
void uGDLSyncCLUT(uGDLImage *img, int* clut){
	img->clut = clut;
}
/*
=======================================================================================
	Function   : uGDLWriteImage
	Purpose    : Writes all of the image data contained inside of an image structure to a real image file
	Parameters : img - An image structure
	Returns	   : void
=======================================================================================
*/
void uGDLWriteImage(uGDLImage img){
	
	if(img.cf == RGB_888 || img.cf == BGR_888){
		int w = img.width;
		int h = img.height;
		
		BMPHeader bmp;
		bmp.type = 0x4d42;
		bmp.size = 54 + ((w * h * 3) + (w * 2));
		bmp.reserved1 = 0;
		bmp.reserved2 = 0;
		bmp.offset = 54;
		bmp.dib_header_size = 40;
		bmp.width_px = w;
		bmp.height_px = h;
		bmp.num_planes = 1;
		bmp.bits_per_pixel = 24;
		bmp.compression = 0;
		bmp.image_size_bytes = w * h * 3;
		bmp.x_resolution_ppm = 0;
		bmp.y_resolution_ppm = 0;
		bmp.num_colors = 0;
		bmp.important_colors = 0;
		
		uint16_t padding = 0;
		
		FILE *file = fopen(img.name,"wb");
		
		fwrite(&bmp.type, sizeof(uint16_t), 1, file);
		fwrite(&bmp.size, sizeof(uint32_t), 1, file);
		fwrite(&bmp.reserved1, sizeof(uint16_t), 1, file);
		fwrite(&bmp.reserved2, sizeof(uint16_t), 1, file);
		fwrite(&bmp.offset, sizeof(uint32_t), 1, file);
		fwrite(&bmp.dib_header_size, sizeof(uint32_t), 1, file);
		fwrite(&bmp.width_px, sizeof(uint32_t), 1, file);
		fwrite(&bmp.height_px, sizeof(uint32_t), 1, file);
		fwrite(&bmp.num_planes, sizeof(uint16_t), 1, file);
		fwrite(&bmp.bits_per_pixel, sizeof(uint16_t), 1, file);
		fwrite(&bmp.compression, sizeof(uint32_t), 1, file);
		fwrite(&bmp.image_size_bytes, sizeof(uint32_t), 1, file);
		fwrite(&bmp.x_resolution_ppm, sizeof(uint32_t), 1, file);
		fwrite(&bmp.y_resolution_ppm, sizeof(uint32_t), 1, file);
		fwrite(&bmp.num_colors, sizeof(uint32_t), 1, file);
		fwrite(&bmp.important_colors, sizeof(uint32_t), 1, file);
		
		int x, y;
		for(y = 0; y < h; y++){
			for(x = 0; x < w; x++){
				int r = getR(img.clut[x+y*w],RGB_888);
				int g = getG(img.clut[x+y*w],RGB_888);
				int b = getB(img.clut[x+y*w],RGB_888);
				
				fwrite(&b,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&r,1,1,file);
			}
			
			if(!(w % 4) == 0){
				fwrite(&padding,2,1,file);
			}
		}
		
		fclose(file);
	}
	else if(img.cf == RGBA_8888){
		int w = img.width;
		int h = img.height;
		
		BMPHeader bmp;
		bmp.type = 0x4d42;
		bmp.size = 54 + ((w * h * 4) + (w * 2));
		bmp.reserved1 = 0;
		bmp.reserved2 = 0;
		bmp.offset = 54;
		bmp.dib_header_size = 40;
		bmp.width_px = w;
		bmp.height_px = h;
		bmp.num_planes = 1;
		bmp.bits_per_pixel = 32;
		bmp.compression = 0;
		bmp.image_size_bytes = w * h * 4;
		bmp.x_resolution_ppm = 0;
		bmp.y_resolution_ppm = 0;
		bmp.num_colors = 0;
		bmp.important_colors = 0;
		
		uint16_t padding = 0;
		
		FILE *file = fopen(img.name,"wb");
		
		fwrite(&bmp.type, sizeof(uint16_t), 1, file);
		fwrite(&bmp.size, sizeof(uint32_t), 1, file);
		fwrite(&bmp.reserved1, sizeof(uint16_t), 1, file);
		fwrite(&bmp.reserved2, sizeof(uint16_t), 1, file);
		fwrite(&bmp.offset, sizeof(uint32_t), 1, file);
		fwrite(&bmp.dib_header_size, sizeof(uint32_t), 1, file);
		fwrite(&bmp.width_px, sizeof(uint32_t), 1, file);
		fwrite(&bmp.height_px, sizeof(uint32_t), 1, file);
		fwrite(&bmp.num_planes, sizeof(uint16_t), 1, file);
		fwrite(&bmp.bits_per_pixel, sizeof(uint16_t), 1, file);
		fwrite(&bmp.compression, sizeof(uint32_t), 1, file);
		fwrite(&bmp.image_size_bytes, sizeof(uint32_t), 1, file);
		fwrite(&bmp.x_resolution_ppm, sizeof(uint32_t), 1, file);
		fwrite(&bmp.y_resolution_ppm, sizeof(uint32_t), 1, file);
		fwrite(&bmp.num_colors, sizeof(uint32_t), 1, file);
		fwrite(&bmp.important_colors, sizeof(uint32_t), 1, file);
		
		int x, y;
		for(y = 0; y < h; y++){
			for(x = 0; x < w; x++){
				int r = getR(img.clut[x+y*w],RGBA_8888);
				int g = getG(img.clut[x+y*w],RGBA_8888);
				int b = getB(img.clut[x+y*w],RGBA_8888);
				int a = getA(img.clut[x+y*w],RGBA_8888);
				
				fwrite(&b,1,1,file);
				fwrite(&g,1,1,file);
				fwrite(&r,1,1,file);
				fwrite(&a,1,1,file);
			}
			
			if(!(w % 4) == 0){
				fwrite(&padding,2,1,file);
			}
		}
		
		fclose(file);
	}
	else{
		
	}
}
/*
=======================================================================================
	Function   : uGDLCaptureScreenshot
	Purpose    : Writes all of the data contained inside of a frame buffer to a real image
	Parameters : buf - A frame buffer structure
	Returns	   : void
=======================================================================================
*/
void uGDLCaptureScreenshot(FrameBuffer buf){
	uGDLImage img = uGDLCreateImage("screenshot.bmp",buf.width,buf.height, RGB_888);
	uGDLSyncCLUT(&img, buf.VRAM);
	uGDLWriteImage(img);
}
/*
=======================================================================================
	Function   : uGDLCaptureDitheredScreenshot
	Purpose    : Writes all of the data contained inside of a frame buffer to a real,dithered image
	Parameters : buf - A frame buffer structure
				 dither - An enumeration containing different modes of dithering
				 factor - The amount of dithering applied to the image
	Returns	   : void
=======================================================================================
*/
void uGDLCaptureDitheredScreenshot(FrameBuffer buf, uGDLDither dither, int factor){
	uGDLImage img = uGDLCreateImage("screenshot_dithered.bmp",buf.width,buf.height, RGB_888);
	uGDLSyncCLUT(&img, buf.VRAM);
	uGDLDitherImage(img, dither, factor);
	uGDLWriteImage(img);
}
/*
=======================================================================================
	Function   : uGDLCopyImageData
	Purpose    : Copies all of the image data from a source image to a destination image
	Parameters : src - A reference to the source image structure
				 dest - A reference to the destination image structure
	Returns	   : void
=======================================================================================
*/
void uGDLCopyImageData(uGDLImage *src, uGDLImage *dest){
	memcpy(src->clut, dest->clut, sizeof(int)*(src->width*src->height));
}
/*
=======================================================================================
	Function   : uGDLClearImage
	Purpose    : Sets all of the image data of an image structure to a particular color
	Parameters : img - A reference to an image structure
				 col - The color to set all of the pixels in the image
	Returns	   : void
=======================================================================================
*/
void uGDLClearImage(uGDLImage *img, int col){
	memset(img->clut,col,sizeof(int)*(img->width*img->height));
}
/*
=======================================================================================
	Function   : uGDLGetImagePixel
	Purpose    : Returns the pixel of the given x and y coordinates
	Parameters : img - An image structure
				 x - The x - coordinate
				 y - The y - coordinate
	Returns	   : An integer
=======================================================================================
*/
int uGDLGetImagePixel(uGDLImage img, int x, int y){
	if(x >= 0 && y >= 0 && x < img.width && y < img.height){
		return img.clut[x + y * img.width];
	}
}
/*
=======================================================================================
	Function   : uGDLSetImagePixel
	Purpose    : Sets the pixel of the given x and y coordinates to a particular color
	Parameters : img - A reference to an image structure
				 x - The x - coordinate
				 y - The y - coordinate
				 col - The color to set the given pixel to
	Returns	   : void
=======================================================================================
*/
void uGDLSetImagePixel(uGDLImage *img, int x, int y, int col){
	if(x >= 0 && y >= 0 && x < img->width && y < img->height){
		 img->clut[x + y * img->width] = col;
	}
}
/*
=======================================================================================
	Function   : uGDLConvertImageToGrayscale
	Purpose    : Converts the given image to a grayscaled equivalent
	Parameters : img - A reference to an image structure
	Returns	   : void
=======================================================================================
*/
void uGDLConvertImageToGrayscale(uGDLImage *img){
	int i;
	for(i = 0; i < img->width * img->height; i++){
		img->clut[i] = uGDLColToGrayscale(img->clut[i], img->cf);
	}
}
/*
=======================================================================================
	Function   : uGDLFreeImage
	Purpose    : Frees the allocated memory of an image structure
	Parameters : img - A reference to an image structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeImage(uGDLImage *img){
	if(img == NULL){
		printf("IMAGE DOES NOT EXIST\n");
		return;
	}
	free(img->clut);
	img = NULL;
}

/*
=======================================================================================
	Function   : AppendStrings
	Purpose    : Takes the given char arrays A and B and concatenates them to a resulting string C
	Parameters : *A - The beginning appendage of the resulting concatenated string
				 *B - The ending appendage of the resulting concatenated string
	Returns	   : A char pointer.
=======================================================================================
*/
char *AppendString(const char * A, const char * B){
	int lenA = strlen(A);
	int lenB = strlen(B);
	
	char *C = (char*)malloc(lenA + lenB + 1);
	
	memcpy(C,A,lenA);
	memcpy(C+lenA,B,lenB);
	
	C[lenA+lenB] = '\0';
	return C;
}
