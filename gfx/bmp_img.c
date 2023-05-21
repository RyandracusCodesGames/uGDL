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
					fread(&(pArr[ind]->a), 1, 1, file);
					clut[ind] = uGDL_RGBA8888(pArr[ind]->r, pArr[ind]->g, pArr[ind]->b, pArr[ind]->a);
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
					pArr[ind] = (struct Pixel*)malloc(sizeof(struct Pixel));
					fread(&(pArr[ind]->b), 1, 1, file); 
					fread(&(pArr[ind]->g), 1, 1, file); 
					clut[ind] = pArr[ind]->b | pArr[ind]->g;
					ind++;
				}
				
				// Padding at the End of Each Row
				fseek(file, padding, SEEK_CUR);  
			}
		}break;
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
	spr->cf = cf;

	removeAll(A,width,height);
	fclose(fp);	
}

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

uGDLImage uGDLCreateImage(char * name, int width, int height, ColorFormat cf){
	uGDLImage img;
	img.name = name;
	img.width = width;
	img.height = height;
	img.clut = (int*)malloc(sizeof(int)*(width*height));
	img.cf = cf;
	return img;
}

void uGDLSyncCLUT(uGDLImage *img, int* clut){
	img->clut = clut;
}

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

void uGDLCaptureScreenshot(FrameBuffer buf){
	uGDLImage img = uGDLCreateImage("screenshot.bmp",buf.width,buf.height, RGB_888);
	uGDLSyncCLUT(&img, buf.VRAM);
	uGDLWriteImage(img);
}

void uGDLCaptureDitheredScreenshot(FrameBuffer buf, uGDLDither dither, int factor){
	uGDLImage img = uGDLCreateImage("screenshot_dithered.bmp",buf.width,buf.height, RGB_888);
	uGDLSyncCLUT(&img, buf.VRAM);
	uGDLDitherImage(img, dither, factor);
	uGDLWriteImage(img);
}

void uGDLCopyImageData(uGDLImage *src, uGDLImage *dest){
	memcpy(src->clut, dest->clut, sizeof(int)*(src->width*src->height));
}

void uGDLClearImage(uGDLImage *img, int col){
	memset(img->clut,col,sizeof(int)*(img->width*img->height));
}

int uGDLGetImagePixel(uGDLImage img, int x, int y){
	if(x >= 0 && y >= 0 && x < img.width && y < img.height){
		return img.clut[x + y * img.width];
	}
}

void uGDLSetImagePixel(uGDLImage *img, int x, int y, int col){
	if(x >= 0 && y >= 0 && x < img->width && y < img->height){
		 img->clut[x + y * img->width] = col;
	}
}

void uGDLConvertImageToGrayscale(uGDLImage *img){
	int i;
	for(i = 0; i < img->width * img->height; i++){
		img->clut[i] = uGDLColToGrayscale(img->clut[i], img->cf);
	}
}

void uGDLFreeImage(uGDLImage *img){
	if(img == NULL){
		printf("IMAGE DOES NOT EXIST\n");
		return;
	}
	free(img->clut);
	img = NULL;
}

char *AppendString(const char * A, const char * B){
	int lenA = strlen(A);
	int lenB = strlen(B);
	
	char *C = (char*)malloc(lenA + lenB + 1);
	
	memcpy(C,A,lenA);
	memcpy(C+lenA,B,lenB);
	
	C[lenA+lenB] = '\0';
	return C;
}
