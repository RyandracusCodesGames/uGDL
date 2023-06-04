#include <math.h>
#include "dither.h"
#include "bmp_img.h"
#include "mathutils.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : dither.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

const   int BAYER_PATTERN_16X16[16][16] =   
{   //  16x16 Bayer Dithering Matrix.  Color levels: 256
    {     0, 191,  48, 239,  12, 203,  60, 251,   3, 194,  51, 242,  15, 206,  63, 254  }, 
    {   127,  64, 175, 112, 139,  76, 187, 124, 130,  67, 178, 115, 142,  79, 190, 127  },
    {    32, 223,  16, 207,  44, 235,  28, 219,  35, 226,  19, 210,  47, 238,  31, 222  },
    {   159,  96, 143,  80, 171, 108, 155,  92, 162,  99, 146,  83, 174, 111, 158,  95  },
    {     8, 199,  56, 247,   4, 195,  52, 243,  11, 202,  59, 250,   7, 198,  55, 246  },
    {   135,  72, 183, 120, 131,  68, 179, 116, 138,  75, 186, 123, 134,  71, 182, 119  },
    {    40, 231,  24, 215,  36, 227,  20, 211,  43, 234,  27, 218,  39, 230,  23, 214  },
    {   167, 104, 151,  88, 163, 100, 147,  84, 170, 107, 154,  91, 166, 103, 150,  87  },
    {     2, 193,  50, 241,  14, 205,  62, 253,   1, 192,  49, 240,  13, 204,  61, 252  },
    {   129,  66, 177, 114, 141,  78, 189, 126, 128,  65, 176, 113, 140,  77, 188, 125  },
    {    34, 225,  18, 209,  46, 237,  30, 221,  33, 224,  17, 208,  45, 236,  29, 220  },
    {   161,  98, 145,  82, 173, 110, 157,  94, 160,  97, 144,  81, 172, 109, 156,  93  },
    {    10, 201,  58, 249,   6, 197,  54, 245,   9, 200,  57, 248,   5, 196,  53, 244  },
    {   137,  74, 185, 122, 133,  70, 181, 118, 136,  73, 184, 121, 132,  69, 180, 117  },
    {    42, 233,  26, 217,  38, 229,  22, 213,  41, 232,  25, 216,  37, 228,  21, 212  },
    {   169, 106, 153,  90, 165, 102, 149,  86, 168, 105, 152,  89, 164, 101, 148,  85  }
};
/*
=======================================================================================
	Function   : uGDLQuantizeImageColor
	Purpose    : Limits the color range, the bit depth, of a particular color
	Parameters : col - A color
				 factor - The limit factor - 4 for example limits our color to 4 possible colors, 8 limits it to 8 and so on
				 cf - The color format, bit depth, of the color
	Returns	   : A color packed into an integer.
=======================================================================================
*/
int uGDLQuantizeImageColor(int col, int factor, ColorFormat cf){
	float newR = round(factor * getR(col,cf) / 255.00f) * (255.00f / factor);
	float newG = round(factor * getG(col,cf) / 255.00f) * (255.00f / factor);
	float newB = round(factor * getB(col,cf) / 255.00f) * (255.00f / factor);
	return uGDLRGBComponentsToInt(newR,newG,newB,cf);
}

/*
=======================================================================================
	Function   : uGDLErrorDiffuseColor
	Purpose    : Performs error diffusion of a color
	Parameters : 
	Returns	   : A color packed into an integer.
=======================================================================================
*/
int uGDLErrorDiffuseColor(int col, float errR, float errG, float errB, float top, float bottom, ColorFormat cf){
	int r1 = getR(col, cf);
	int g1 = getG(col, cf);
	int b1 = getB(col, cf);
	int a1 = getA(col, cf);
			

	switch(cf){
		case RGBA_8888:{
			r1 = uGDLClamp(0,(r1 + errR * (top/bottom)),255);
			g1 = uGDLClamp(0,(g1 + errG * (top/bottom)),255);
			b1 = uGDLClamp(0,(b1 + errB * (top/bottom)),255);
			return uGDLRGBAComponentsToInt(r1,g1,b1,a1);
		}break;
		case RGB_888:{
			r1 = uGDLClamp(0,(r1 + errR * (top/bottom)),255);
			g1 = uGDLClamp(0,(g1 + errG * (top/bottom)),255);
			b1 = uGDLClamp(0,(b1 + errB * (top/bottom)),255);
			return uGDLRGBComponentsToInt(r1,g1,b1,RGB_888);
		}break;
		case BGR_888:{
			r1 = uGDLClamp(0,(r1 + errR * (top/bottom)),255);
			g1 = uGDLClamp(0,(g1 + errG * (top/bottom)),255);
			b1 = uGDLClamp(0,(b1 + errB * (top/bottom)),255);
			return uGDLRGBComponentsToInt(r1,g1,b1,BGR_888);			
		}break;
		case RGB_565:{
			r1 = uGDLClamp(0,(r1 + errR * (top/bottom)),31);
			g1 = uGDLClamp(0,(g1 + errG * (top/bottom)),31);
			b1 = uGDLClamp(0,(b1 + errB * (top/bottom)),31);
			return uGDLRGBComponentsToInt(r1,g1,b1,RGB_565);
		}break;
		case BGR_565:{
			r1 = uGDLClamp(0,(r1 + errR * (top/bottom)),31);
			g1 = uGDLClamp(0,(g1 + errG * (top/bottom)),31);
			b1 = uGDLClamp(0,(b1 + errB * (top/bottom)),31);
			return uGDLRGBComponentsToInt(r1,g1,b1,BGR_565);			
		}break;
	}
}
/*
=======================================================================================
	Function   : uGDLDitherSprite
	Purpose    : Performs dithering on a sprite
	Parameters : spr - A sprite structure
				 dither - The type of dithering desired to be performed on the sprite
	Returns	   : void
=======================================================================================
*/
void uGDLDitherSprite(uGDLSprite spr, uGDLDither dither, int factor){
	switch(dither){
		case DITHER_FLOYD_STEINBERG:{
			int x, y, i;
			for(i = 0; i < spr.width * spr.height; i++){
					x = i % spr.width, y = i / spr.width;
					int col = uGDLGetPixel(spr, x, y);
					
					int r = getR(col, spr.cf);
					int g = getG(col, spr.cf);
					int b = getB(col, spr.cf);
					
					uGDLSetPixel(&spr, x, y, uGDLQuantizeImageColor(col,factor,spr.cf));
					
					float newR = round(factor * r / 255.00f) * (255.00f / factor);
					float newG = round(factor * g / 255.00f) * (255.00f / factor);
					float newB = round(factor * b / 255.00f) * (255.00f / factor);
					
					float errR = r - newR;
					float errG = g - newG;
					float errB = b - newB;
					
					col = uGDLGetPixel(spr, x + 1, y);
					uGDLSetPixel(&spr, x + 1,  y, uGDLErrorDiffuseColor(col,errR,errG,errB,7.00f,16.00f,spr.cf));
					
					col = uGDLGetPixel(spr, x - 1, y + 1);
					uGDLSetPixel(&spr, x - 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,3.00f,16.00f,spr.cf));
					
					col = uGDLGetPixel(spr, x, y + 1);
					uGDLSetPixel(&spr, x,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,5.00f,16.00f,spr.cf));
					
					col = uGDLGetPixel(spr, x + 1, y + 1);
					uGDLSetPixel(&spr, x + 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,1.00f,16.00f,spr.cf));
			}
		}break;
		case DITHER_ORDERED:{
			
			int x, y, col, row;
			for(y = 0; y < spr.height; y++){
				row = y & 15;
				for(x = 0; x < spr.width; x++){
					col = x & 15;
					
					int color = uGDLGetPixel(spr,x,y);
					
					int r = getR(color, spr.cf);
					int g = getG(color, spr.cf);
					int b = getB(color, spr.cf);
					
					r = (r > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					g = (g > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					b = (b > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					
					uGDLSetPixel(&spr, x, y, uGDLRGBComponentsToInt(r,g,b,spr.cf));
				}
			}
			
		};
	}
}
/*
=======================================================================================
	Function   : uGDLDitherTexture
	Purpose    : Performs dithering on a texture
	Parameters : tex - A texture structure
				 dither - The type of dithering desired to be performed on the texture
	Returns	   : void
=======================================================================================
*/
void uGDLDitherTexture(uGDLTexture tex, uGDLDither dither, int factor, ColorFormat cf){
	switch(dither){
		case DITHER_FLOYD_STEINBERG:{
			int x, y, i;
			for(i = 0; i < tex.width * tex.height; i++){
					x = i % tex.width, y = i / tex.width;
					int col = uGDLGetTexel(tex, x, y);
					
					int r = getR(col, cf);
					int g = getG(col, cf);
					int b = getB(col, cf);
					
					uGDLSetTexel(&tex, x, y, uGDLQuantizeImageColor(col,factor,cf));
					
					float newR = round(factor * r / 255.00f) * (255.00f / factor);
					float newG = round(factor * g / 255.00f) * (255.00f / factor);
					float newB = round(factor * b / 255.00f) * (255.00f / factor);
					
					float errR = r - newR;
					float errG = g - newG;
					float errB = b - newB;
					
					col = uGDLGetTexel(tex, x + 1, y);
					uGDLSetTexel(&tex, x + 1,  y, uGDLErrorDiffuseColor(col,errR,errG,errB,7.00f,16.00f,cf));
					
					col = uGDLGetTexel(tex, x - 1, y + 1);
					uGDLSetTexel(&tex, x - 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,3.00f,16.00f,cf));
					
					col = uGDLGetTexel(tex, x, y + 1);
					uGDLSetTexel(&tex, x,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,5.00f,16.00f,cf));
					
					col = uGDLGetTexel(tex, x + 1, y + 1);
					uGDLSetTexel(&tex, x + 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,1.00f,16.00f,cf));
			}
		}break;
		case DITHER_ORDERED:{
			
			int x, y, col, row;
			for(y = 0; y < tex.height; y++){
				row = y & 15;
				for(x = 0; x < tex.width; x++){
					col = x & 15;
					
					int color = uGDLGetTexel(tex,x,y);
					
					int r = getR(color, cf);
					int g = getG(color, cf);
					int b = getB(color, cf);
					
					r = (r > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					g = (g > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					b = (b > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					
					uGDLSetTexel(&tex, x, y, uGDLRGBComponentsToInt(r,g,b,cf));
				}
			}
			
		};
	}
}
/*
=======================================================================================
	Function   : uGDLDitherImage
	Purpose    : Performs dithering on an image
	Parameters : img - An image structure
				 dither - The type of dithering desired to be performed on the image
	Returns	   : void
=======================================================================================
*/
void uGDLDitherImage(uGDLImage img, uGDLDither dither, int factor){
	switch(dither){
		case DITHER_FLOYD_STEINBERG:{
			int x, y, i;
			for(i = 0; i < img.width * img.height; i++){
					x = i % img.width, y = i / img.width;
					int col = uGDLGetImagePixel(img, x, y);
					
					int r = getR(col, img.cf);
					int g = getG(col, img.cf);
					int b = getB(col, img.cf);
					
					uGDLSetImagePixel(&img, x, y, uGDLQuantizeImageColor(col,factor,img.cf));
					
					float newR = round(factor * r / 255.00f) * (255.00f / factor);
					float newG = round(factor * g / 255.00f) * (255.00f / factor);
					float newB = round(factor * b / 255.00f) * (255.00f / factor);
					
					float errR = r - newR;
					float errG = g - newG;
					float errB = b - newB;
					
					col = uGDLGetImagePixel(img, x + 1, y);
					uGDLSetImagePixel(&img, x + 1,  y, uGDLErrorDiffuseColor(col,errR,errG,errB,7.00f,16.00f,img.cf));
					
					col = uGDLGetImagePixel(img, x - 1, y + 1);
					uGDLSetImagePixel(&img, x - 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,3.00f,16.00f,img.cf));
					
					col = uGDLGetImagePixel(img, x, y + 1);
					uGDLSetImagePixel(&img, x,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,5.00f,16.00f,img.cf));
					
					col = uGDLGetImagePixel(img, x + 1, y + 1);
					uGDLSetImagePixel(&img, x + 1,  y + 1, uGDLErrorDiffuseColor(col,errR,errG,errB,1.00f,16.00f,img.cf));
			}
		}break;
		case DITHER_ORDERED:{
			
			int x, y, col, row;
			for(y = 0; y < img.height; y++){
				row = y & 15;
				for(x = 0; x < img.width; x++){
					col = x & 15;
					
					int color = uGDLGetImagePixel(img,x,y);
					
					int r = getR(color, img.cf);
					int g = getG(color, img.cf);
					int b = getB(color, img.cf);
					
					r = (r > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					g = (g > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					b = (b > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					
					uGDLSetImagePixel(&img, x, y, uGDLRGBComponentsToInt(r,g,b,img.cf));
				}
			}
			
		};
	}
}

void uGDLDitherCanvas(uGDLCanvas *canvas, uGDLDither dither, int factor){
		switch(dither){
		case DITHER_FLOYD_STEINBERG:{
			int x, y, i;
			for(i = 0; i < canvas->width * canvas->height; i++){
					x = i % canvas->width, y = i / canvas->width;
					int col = uGDLGetCanvasPixel(canvas, x, y);
					
					int r = getR(col, canvas->cf);
					int g = getG(col, canvas->cf);
					int b = getB(col, canvas->cf);
					
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, y), uGDLQuantizeImageColor(col,factor,canvas->cf));
					
					float newR = round(factor * r / 255.00f) * (255.00f / factor);
					float newG = round(factor * g / 255.00f) * (255.00f / factor);
					float newB = round(factor * b / 255.00f) * (255.00f / factor);
					
					float errR = r - newR;
					float errG = g - newG;
					float errB = b - newB;
					
					col = uGDLGetCanvasPixel(canvas, x + 1, y);
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x + 1,  y), uGDLErrorDiffuseColor(col,errR,errG,errB,7.00f,16.00f,canvas->cf));
					
					col = uGDLGetCanvasPixel(canvas, x - 1, y + 1);
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x - 1,  y + 1), uGDLErrorDiffuseColor(col,errR,errG,errB,3.00f,16.00f,canvas->cf));
					
					col = uGDLGetCanvasPixel(canvas, x, y + 1);
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x,  y + 1), uGDLErrorDiffuseColor(col,errR,errG,errB,5.00f,16.00f,canvas->cf));
					
					col = uGDLGetCanvasPixel(canvas, x + 1, y + 1);
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x + 1,  y + 1), uGDLErrorDiffuseColor(col,errR,errG,errB,1.00f,16.00f,canvas->cf));
			}
		}break;
		case DITHER_ORDERED:{
			
			int x, y, col, row;
			for(y = 0; y < canvas->height; y++){
				row = y & 15;
				for(x = 0; x < canvas->width; x++){
					col = x & 15;
					
					int color = uGDLGetCanvasPixel(canvas,x,y);
					
					int r = getR(color, canvas->cf);
					int g = getG(color, canvas->cf);
					int b = getB(color, canvas->cf);
					
					r = (r > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					g = (g > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					b = (b > BAYER_PATTERN_16X16[col][row] ? 255 : 0);
					
					uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, y), uGDLRGBComponentsToInt(r,g,b,canvas->cf));
				}
			}
			
		};
	}
}
