#include "gaussianblur.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : gaussianblur.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLDispGaussianSprite
	Purpose    : Displays a sprite with a blur effect to the window display
	Parameters : VRAM - A reference to the video memory of our window display
				 spr - A sprite structure
				 tX - The x - coordinate translation offset
				 tY - The y - coordinate translation offset
	Returns	   : void
=======================================================================================
*/
void uGDLDispGaussianSprite(uint32_t *VRAM, uGDLSprite spr, int tX, int tY){
	
	float sumr = 0;
	float sumg = 0;
	float sumb = 0;
	
	int gauss_fact[gauss_width]={1,6,15,20,15,6,1};

	int gauss_sum = 64;
	
	int x, y;
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetPixel(spr, x-((gauss_width-1)>>1)+k, y);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			int r = (int)(sumr/gauss_sum), g = (int)(sumg/gauss_sum), b = (int)(sumb/gauss_sum);
			
			uGDLDrawPoint(VRAM, uGDLCreatePoint(x + tX, y + tY), uGDL_RGB888(r,g,b));
		}
	}
	
	for(y = 0; y < spr.height; y++){
		for(x = 0; x < spr.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetPixel(spr, x,y-((gauss_width-1)>>1)+k);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			sumr /= gauss_sum;
			sumg /= gauss_sum;
			sumb /= gauss_sum;
			
			uGDLDrawPoint(VRAM, uGDLCreatePoint(x + tX, y + tY), uGDLRGBComponentsToInt((int)(sumr),(int)(sumg),(int)(sumb),RGB_888));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLMakeTextureGaussian
	Purpose    : Performs a blur effect to a texture
	Parameters : tex - A texture structure
	Returns	   : void
=======================================================================================
*/
void uGDLMakeTextureGaussian(uGDLTexture tex){
	
	float sumr = 0;
	float sumg = 0;
	float sumb = 0;
	
	int gauss_fact[gauss_width]={1,6,15,20,15,6,1};

	int gauss_sum = 64;
	
	int x, y;
	for(y = 0; y < tex.height; y++){
		for(x = 0; x < tex.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetTexel(tex, x-((gauss_width-1)>>1)+k, y);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			int r = (int)(sumr/gauss_sum), g = (int)(sumg/gauss_sum), b = (int)(sumb/gauss_sum);
			
			uGDLSetTexel(&tex,x,y,uGDL_RGB888(r,g,b));
		}
	}
	
	for(y = 0; y < tex.height; y++){
		for(x = 0; x < tex.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetTexel(tex, x,y-((gauss_width-1)>>1)+k);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			sumr /= gauss_sum;
			sumg /= gauss_sum;
			sumb /= gauss_sum;
			
			uGDLSetTexel(&tex,x,y,uGDLRGBComponentsToInt((int)(sumr),(int)(sumg),(int)(sumb),RGB_888));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLBlurCanvas
	Purpose    : Performs a blur effect to a canvas
	Parameters : canvas - A reference to a canvas structure
	Returns	   : void
=======================================================================================
*/
void uGDLBlurCanvas(uGDLCanvas *canvas){
	float sumr = 0;
	float sumg = 0;
	float sumb = 0;
	
	int gauss_fact[gauss_width]={1,6,15,20,15,6,1};

	int gauss_sum = 64;
	
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetCanvasPixel(canvas, x-((gauss_width-1)>>1)+k, y);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			int r = (int)(sumr/gauss_sum), g = (int)(sumg/gauss_sum), b = (int)(sumb/gauss_sum);
			
			uGDLDrawPointOnCanvas(canvas,uGDLCreatePoint(x,y),uGDL_RGB888(r,g,b));
		}
	}
	
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetCanvasPixel(canvas, x,y-((gauss_width-1)>>1)+k);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			sumr /= gauss_sum;
			sumg /= gauss_sum;
			sumb /= gauss_sum;
			
			uGDLDrawPointOnCanvas(canvas,uGDLCreatePoint(x,y),uGDLRGBComponentsToInt((int)(sumr),(int)(sumg),(int)(sumb),RGB_888));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLBlurImage
	Purpose    : Performs a blur effect to an image structure
	Parameters : img - An image structure
	Returns	   : void
=======================================================================================
*/
void uGDLBlurImage(uGDLImage img){
	float sumr = 0;
	float sumg = 0;
	float sumb = 0;
	
	int gauss_fact[gauss_width]={1,6,15,20,15,6,1};

	int gauss_sum = 64;
	
	int x, y;
	for(y = 0; y < img.height; y++){
		for(x = 0; x < img.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetImagePixel(img, x-((gauss_width-1)>>1)+k, y);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			int r = (int)(sumr/gauss_sum), g = (int)(sumg/gauss_sum), b = (int)(sumb/gauss_sum);
			
			uGDLSetImagePixel(&img,x,y,uGDL_RGB888(r,g,b));
		}
	}
	
	for(y = 0; y < img.height; y++){
		for(x = 0; x < img.width; x++){
			sumr = 0;
			sumg = 0;
			sumb = 0;
			int k;
			for(k = 0; k < gauss_width; k++){
				int col = uGDLGetImagePixel(img, x,y-((gauss_width-1)>>1)+k);
				float r = getR(col,RGB_888);
				float g = getG(col,RGB_888);
				float b = getB(col,RGB_888);
				sumr+=r*gauss_fact[k];
				sumg+=g*gauss_fact[k];
				sumb+=b*gauss_fact[k];
			}
			
			sumr /= gauss_sum;
			sumg /= gauss_sum;
			sumb /= gauss_sum;
			
			uGDLSetImagePixel(&img,x,y,uGDLRGBComponentsToInt((int)(sumr),(int)(sumg),(int)(sumb),RGB_888));
		}
	}
}
