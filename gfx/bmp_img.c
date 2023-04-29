#include "bmp_img.h"
#include "color.h"

/**
 * read Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void readPixelsBMP(FILE* file,struct Pixel*pArr[SIZE],int width,int height, int *clut, ColorFormat cf)
{
	if(file == NULL)
		return;
	
	// A Useful Variable 
	int padding = width % 4; 
	
	// Move 54Bytes (Header Size) 	
	fseek(file, 54, SEEK_SET); 
 
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
			switch(cf){
				case RGB_888:{
					clut[ind] = uGDL_RGB888(pArr[ind]->r, pArr[ind]->g, pArr[ind]->b);
				}break;
				case BGR_888:{
					clut[ind] = uGDL_BGR888(pArr[ind]->b, pArr[ind]->g, pArr[ind]->r);
				}break;
			}
			ind++;
		}
		
		// Padding at the End of Each Row
		fseek(file, padding, SEEK_CUR);  
	}
}

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

void removeAll(struct Pixel*pArr[SIZE],int width,int height)
{
	int i;
	for(i=0;i<width*height;i++)
	{
		free(pArr[i]);
	}
}

void uGDLFreeSprite(uGDLSprite *spr){
	free(spr->clut);
}

void uGDLFreeTexture(uGDLTexture *tex){
	free(tex->tlut);
}

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

	removeAll(A,width,height);
	fclose(fp);	
}

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
