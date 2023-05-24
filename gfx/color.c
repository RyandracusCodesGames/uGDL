#include "color.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : color.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : getR
	Purpose    : Returns the red component of a color
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A red color component packed into an integer.
=======================================================================================
*/
int getR(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			return ((col >> 24) & 0xff);
		}break;
		case RGB_888:{
			return ((col & 0xff0000) >> 16);
		}break;
		case BGR_888:{
			return ((col & 0xff));
		}break;
		case RGB_565:{
			return ((col & 0xF800) >> 11);
		}break;
		case BGR_565:{
			return ((col & 0x1F));
		}break;
	}
}
/*
=======================================================================================
	Function   : getG
	Purpose    : Returns the green component of a color
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A green color component packed into an integer.
=======================================================================================
*/
int getG(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			return ((col & 0xff0000) >> 16);
		}break;
		case RGB_888:{
			return ((col & 0xff00) >> 8);
		}break;
		case BGR_888:{
			return ((col & 0xff00) >> 8);
		}break;
		case RGB_565:{
			return ((col & 0x7E0) >> 6);
		}break;
		case BGR_565:{
			return ((col & 0x7E0) >> 6);
		}break;
	}
}
/*
=======================================================================================
	Function   : getB
	Purpose    : Returns the blue component of a color
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A blue color component packed into an integer.
=======================================================================================
*/
int getB(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			return ((col & 0xff0000) >> 8);
		}break;
		case RGB_888:{
			return ((col & 0xff));
		}break;
		case BGR_888:{
			return ((col & 0xff0000) >> 16);
		}break;
		case RGB_565:{
			return ((col & 0x1F));
		}break;
		case BGR_565:{
			return ((col & 0xF800) >> 11);
		}break;
	}
}
/*
=======================================================================================
	Function   : getA
	Purpose    : Returns the alpha component of a color
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A alpha color component packed into an integer.
=======================================================================================
*/
int getA(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			return ((col & 0xff));
		}break;
	}
}
/*
=======================================================================================
	Function   : getCol
	Purpose    : Returns the color of the combined rgb component of a uGDL_RGB structure
	Parameters : rgb - A structure encapsulating the three r,g,b component in a singular source
				 cf - The color format, bit depth, of the color
	Returns	   : A color component packed into an integer.
=======================================================================================
*/
int getCol(uGDL_RGB rgb, ColorFormat cf){
	int r = getR(rgb.r, cf);
	int g = getG(rgb.g, cf);
	int b = getB(rgb.b, cf);
	
	switch(cf){
		case RGB_888:{
			return r << 16 | g << 8 | b;
		}break;
		case BGR_888:{
			return b << 16 | g << 8 | r;
		}break;
		case RGB_565:{
			return r << 11 | g << 6 | b;
		}break;
		case BGR_565:{
			return b << 11 | g << 6 | r;			
		}
	}
}
/*
=======================================================================================
	Function   : uGDLSetColor
	Purpose    : Given a color, returns the correctly formatted color by the desired bit depth
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A correctly formatted color packed into an integer.
=======================================================================================
*/
int uGDLSetColor(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			switch(col){
				case BLACK:{
					return BLACK_8888;
					break;
				}
				case WHITE:{
					return WHITE_8888;
					break;
				}
				case GRAY:{
					return GRAY_8888;
					break;
				}
				case BLUE:{
					return BLUE_8888;
					break;
				}
				case GREEN:{
					return GREEN_8888;
					break;
				}
				case RED:{
					return RED_8888;
					break;
				}
				case YELLOW:{
					return YELLOW_8888;
					break;
				}
				case PURPLE:{
					return PURPLE_8888;
					break;
				}
				case ORANGE:{
					return ORANGE_8888;
					break;
				}
				case BROWN:{
					return BROWN_8888;
					break;
				}
			}
		}break;
		case RGB_888:{
				switch(col){
				case BLACK:{
					return BLACK;
					break;
				}
				case WHITE:{
					return WHITE;
					break;
				}
				case GRAY:{
					return GRAY;
					break;
				}
				case BLUE:{
					return BLUE;
					break;
				}
				case GREEN:{
					return GREEN;
					break;
				}
				case RED:{
					return RED;
					break;
				}
				case YELLOW:{
					return YELLOW;
					break;
				}
				case PURPLE:{
					return PURPLE;
					break;
				}
				case ORANGE:{
					return ORANGE;
					break;
				}
				case BROWN:{
					return BROWN;
					break;
				}
			}
		}break;
		case BGR_888:{
			switch(col){
				case BLACK:{
					return BLACK;
					break;
				}
				case WHITE:{
					return WHITE;
					break;
				}
				case GRAY:{
					return GRAY;
					break;
				}
				case BLUE:{
					return BLUE_REVERSE;
					break;
				}
				case GREEN:{
					return GREEN;
					break;
				}
				case RED:{
					return RED_REVERSE;
					break;
				}
				case YELLOW:{
					return YELLOW_REVERSE;
					break;
				}
				case PURPLE:{
					return PURPLE_REVERSE;
					break;
				}
				case ORANGE:{
					return ORANGE_REVERSE;
					break;
				}
				case BROWN:{
					return BROWN_REVERSE;
					break;
				}
			}
		}break;
		case RGB_565:{
			switch(col){
				case BLACK:{
					return BLACK_565;
					break;
				}
				case WHITE:{
					return WHITE_565;
					break;
				}
				case GRAY:{
					return GRAY_565;
					break;
				}
				case BLUE:{
					return BLUE_565;
					break;
				}
				case GREEN:{
					return GREEN_565;
					break;
				}
				case RED:{
					return RED_565;
					break;
				}
				case YELLOW:{
					return YELLOW_565;
					break;
				}
				case PURPLE:{
					return PURPLE_565;
					break;
				}
				case ORANGE:{
					return ORANGE_565;
					break;
				}
				case BROWN:{
					return BROWN_565;
					break;
				}
			}
		}break;
		case BGR_565:{
			switch(col){
				case BLACK:{
					return BLACK_565;
					break;
				}
				case WHITE:{
					return WHITE_565;
					break;
				}
				case GRAY:{
					return GRAY_565;
					break;
				}
				case BLUE:{
					return BLUE_565;
					break;
				}
				case GREEN:{
					return GREEN_565;
					break;
				}
				case RED:{
					return RED_565;
					break;
				}
				case YELLOW:{
					return YELLOW_565;
					break;
				}
				case PURPLE:{
					return PURPLE_565;
					break;
				}
				case ORANGE:{
					return ORANGE_565;
					break;
				}
				case BROWN:{
					return BROWN_565;
					break;
				}
			}
		}break;
		
	}
}
/*
=======================================================================================
	Function   : colToRGB
	Purpose    : Given a color and color format, extracts the color component of the color and puts them into an rgb structure
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A packed uGDL_RGB structure.
=======================================================================================
*/
uGDL_RGB colToRGB(int col, ColorFormat cf){
	
	int r = getR(col, cf);
	int g = getG(col, cf);
	int b = getB(col, cf);
	
	uGDL_RGB rgb = {r, g, b};
	
	return rgb;
}
/*
=======================================================================================
	Function   : colToRGBA
	Purpose    : Given a color with an alpha channel and color format, extracts the color component of the color and puts them into an rgba structure
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A packed uGDL_RGBA structure.
=======================================================================================
*/
uGDL_RGBA colToRGBA(int col, ColorFormat cf){
	
	if(cf == RGBA_8888){
		int r = getR(col, cf);
		int g = getG(col, cf);
		int b = getB(col, cf);
		int a = getA(col, cf);
		uGDL_RGBA rgba = {r, g, b, a};
		
		return rgba;
	}	
}
/*
=======================================================================================
	Function   : uGDLCreatePalette
	Purpose    : Creates a color palette by streaming an array of color values to a palette
	Parameters : pal - A reference to a palette structure
				 col - An integer pointer
	Returns	   : A packed uGDL_PALETTE structure.
	Comments: (SOON TO BE DEPRECATED BY PALETTE SOURCE FILE)
=======================================================================================
*/
uGDL_PALETTE uGDLCreatePalette(uGDL_PALETTE *pal, int* col){
	int i;
	for(i = 0; i < sizeof(col)/sizeof(col[0]); i++){
		pal->palette[i] = col[i];
	}
}
/*
=======================================================================================
	Function   : uGDLLoadTexturePalette
	Purpose    : Loads an image file and streams its image data to a palette
	Parameters : pal - A reference to a palette structure
				 name - The directory, file name, and file extension of the image
				 cf - The color format, bit depth, of the image
	Returns	   : void
	Comments: (SOON TO BE DEPRECATED BY PALETTE SOURCE FILE)
=======================================================================================
*/
void uGDLLoadTexturePalette(uGDL_PALETTE* pal, char * name, ColorFormat cf){
	uGDLTexture tex;
	uGDLLoadTexture(name, cf, &tex, 16, 16);
	
	int i;
	for(i = 0; i < MAXCOLORS; i++){
		pal->palette[i] = tex.tlut[i];
	}
}
/*
=======================================================================================
	Comments: uGDL_PALETTE (SOON TO BE DEPRECATED BY PALETTE SOURCE FILE)
=======================================================================================
*/
void uGDLAddColToPalette(uGDL_PALETTE *pal, int index, int col){
	pal->palette[index] = col;
}
/*
=======================================================================================
	Function   : uGDLBlendColor
	Purpose    : Given two colors, blends the two together with a stronger preference to the first color in the resulting combined color
	Parameters : col1 - The first color
				 col2 - The second color
				 ratio - The blending factor
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLBlendColor(int col1, int col2, float ratio, ColorFormat cf){
	if(ratio > 1.0f){
		ratio = 1.0f;
	}
	else if(ratio < 0){
		ratio = 0;
	}
	float iRatio = 1 - ratio;
	
	int i1 = col1;
	int i2 = col2;
	
	int r1 = getR(i1, cf);
	int g1 = getG(i1, cf);
	int b1 = getB(i1, cf);
	int a1 = getA(i1, cf);
	
	int r2 = getR(i2, cf);
	int g2 = getG(i2, cf);
	int b2 = getB(i2, cf);
	int a2 = getA(i2, cf);
	
	int r = (int)((r1 * iRatio) + (r2 * ratio));
    int g = (int)((g1 * iRatio) + (g2 * ratio));
    int b = (int)((b1 * iRatio) + (b2 * ratio));
    int a = (int)((a1 * iRatio) + (a2 * ratio));
	
	if(cf == RGB_888){
		return uGDLRGBComponentsToInt(r,g,b,RGB_888);	
	}
	else if(cf == RGBA_8888){
		return uGDLRGBAComponentsToInt(r,g,b,a);
	}
	else return uGDLRGBComponentsToInt(r,g,b,BGR_888);
}
/*
=======================================================================================
	Function   : uGDLBlendColorMode
	Purpose    : Given two colors, uses a mode to indicate how the two colors should be blended together
	Parameters : col1 - The first color
				 col2 - The second color
				 factor - The blending ratio, the strength of the blend
				 cf - The color format, bit depth, of the color
				 mode - See header file to see different blending modes explained
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLBlendColorMode(int col1, int col2, float factor, ColorFormat cf, int mode){
	if(factor > 1.0f){
		factor = 1.0f;
	}
	
	if(factor < 0.0f){
		factor = 0.0f;
	}
	
	float iFactor = 1.0f - factor;
	
	int r1 = getR(col1,cf);
	int g1 = getG(col1,cf);
	int b1 = getB(col1,cf);
	int a1 = getA(col1,cf);
	
	int r2 = getR(col2,cf);
	int g2 = getG(col2,cf);
	int b2 = getB(col2,cf);
	int a2 = getA(col2,cf);
	
	if(cf == RGB_888){
		switch(mode){
			case BLEND_COLOR_BOTHINVALPHA:{
				int r = (r1 * iFactor) + (r2 * factor);
				int g = (g1 * iFactor) + (g2 * factor);
				int b = (b1 * iFactor) + (b2 * factor);
				return uGDLRGBComponentsToInt(r,g,b,RGB_888);
			}break;
			case BLEND_COLOR_BOTHSRCALPHA:{
				return uGDLBlendColor(col1, col2, factor, cf);
			}break;
			case BLEND_COLOR_SRCALPHA:{
				return uGDLAddColor(uGDLDotColor(col1,factor,cf), col2,cf);
			}break;
			case BLEND_COLOR_DESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2,factor,cf),cf);
			}break;
			case BLEND_COLOR_INVDESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2, 1.0 - factor,cf),cf);
			}break;
			default: return uGDLAddColor(col1,col2,cf); break;
		}
	}
	else if(cf == BGR_888){
		switch(mode){
			case BLEND_COLOR_BOTHINVALPHA:{
				int r = (r1 * iFactor) + (r2 * factor);
				int g = (g1 * iFactor) + (g2 * factor);
				int b = (b1 * iFactor) + (b2 * factor);
				return uGDLRGBComponentsToInt(r,g,b,RGB_888);
			}break;
			case BLEND_COLOR_BOTHSRCALPHA:{
				return uGDLBlendColor(col1, col2, factor, cf);
			}break;
			case BLEND_COLOR_SRCALPHA:{
				return uGDLAddColor(uGDLDotColor(col1,factor,cf), col2,cf);
			}break;
			case BLEND_COLOR_DESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2,factor,cf),cf);
			}break;
			case BLEND_COLOR_INVDESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2, 1.0 - factor,cf),cf);
			}break;
			default: return uGDLAddColor(col1,col2,cf); break;
		}
	}
	else{
		switch(mode){
			case BLEND_COLOR_BOTHINVALPHA:{
				int r = (r1 * iFactor) + (r2 * factor);
				int g = (g1 * iFactor) + (g2 * factor);
				int b = (b1 * iFactor) + (b2 * factor);
				int a = (a1 * iFactor) + (a2 * factor);
				return uGDLRGBAComponentsToInt(r,g,b,a);
			}break;
			case BLEND_COLOR_BOTHSRCALPHA:{
				return uGDLBlendColor(col1, col2, factor, cf);
			}break;
			case BLEND_COLOR_SRCALPHA:{
				return uGDLAddColor(uGDLDotColor(col1,factor,cf), col2,cf);
			}break;
			case BLEND_COLOR_DESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2,factor,cf),cf);
			}break;
			case BLEND_COLOR_INVDESTALPHA:{
				return uGDLAddColor(col1, uGDLDotColor(col2, 1.0 - factor,cf),cf);
			}break;
			default: return uGDLAddColor(col1,col2,cf); break;
		}
	}
}
/*
=======================================================================================
	Function   : uGDLBlendColorWithVRAM
	Purpose    : Given a color, a location, and our virtual memory, blend our color with that location in our window display to achieve semi-transparency
	Parameters : col11 - A color
				 VRAM - A reference to our video memory of our window display
				 x - The x - coordinate of our color in video memory
				 y - The y - coordinate of our color in video memory
				 factor - The blending factor
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLBlendColorWithVRAM(int col, uint32_t *VRAM, int x, int y, float factor, ColorFormat cf){
	return uGDLBlendColor(col, uGDLGetScreenPixel(VRAM, x, y, 0, 1), factor, cf);
}
/*
=======================================================================================
	Function   : uGDLColToGrayscale
	Purpose    : Given a color, convert said color to a grayscale equivalent
	Parameters : col - A color
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLColToGrayscale(int col, ColorFormat cf){
	float r = getR(col, RGB_888);
	float g = getG(col, RGB_888);
	float b = getB(col, RGB_888);

	if(cf == RGBA_8888){
		int grayscale = (int)((r,g,b)/3.0f);
		return uGDLRGBAComponentsToInt(grayscale, grayscale, grayscale,255);
	}
	else{
		int grayscale = (int)((r+g+b)/3.0f);
		return uGDLRGBComponentsToInt(grayscale, grayscale, grayscale, cf);
	}
}
/*
=======================================================================================
	Function   : uGDLAddColor
	Purpose    : Given two colors, blends the two together with a no preference towards either color
	Parameters : col1 - The first color
				 col2 - The second color
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLAddColor(int col1, int col2, ColorFormat cf){
	int i1 = col1;
	int i2 = col2;
	
	int r1 = getR(i1, cf);
	int g1 = getG(i1, cf);
	int b1 = getB(i1, cf);
	int a1 = getA(i1, cf);
	
	int r2 = getR(i2, cf);
	int g2 = getG(i2, cf);
	int b2 = getB(i2, cf);
	int a2 = getA(i2, cf);
	
	int r = r1 + r2;
    int g = g1 + g2;
    int b = b1 + b2;
    int a = a1 + a2;
	
	if(cf == RGB_888){
		return uGDLRGBComponentsToInt(r,g,b,RGB_888);	
	}
	else if(cf == RGBA_8888){
		return uGDLRGBAComponentsToInt(r,g,b,a);
	}
	else return uGDLRGBComponentsToInt(r,g,b,BGR_888);
}
/*
=======================================================================================
	Function   : uGDLInterpColor
	Purpose    : Given two colors, interpolates between them to find some color between their spectrum in color space
	Parameters : col1 - The first color
				 col2 - The second color
				 interp - The interpolation factor
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLInterpColor(int col1, int col2, float interp, ColorFormat cf){
	
	int r1 = getR(col1, cf);
	int g1 = getG(col1, cf);
	int b1 = getB(col1, cf);
	int a1 = getA(col1, cf);
	
	int r2 = getR(col2, cf);
	int g2 = getG(col2, cf);
	int b2 = getB(col2, cf);
	int a2 = getA(col2, cf);
	
	int r = r1 + interp * (r1 - r2);
	int g = g1 + interp * (g1 - g2);
	int b = b1 + interp * (b1 - b2);
	int a = a1 + interp * (a1 - a2);
	
	if(cf == RGB_888){
		return uGDLRGBComponentsToInt(r,g,b,RGB_888);	
	}
	else if(cf == RGBA_8888){
		return uGDLRGBAComponentsToInt(r,g,b,a);
	}
	else return uGDLRGBComponentsToInt(r,g,b,BGR_888);
}
/*
=======================================================================================
	Function   : uGDLDotColor
	Purpose    : Dims or brightens a color by a certain factor
	Parameters : col1 - A color
				 factor - The dim/brighten factor
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLDotColor(int col1, float factor, ColorFormat cf){
	
	int r1 = getR(col1, cf);
	int g1 = getG(col1, cf);
	int b1 = getB(col1, cf);
	int a1 = getA(col1, cf);
	
	int r = (r1 * factor);
	int g = (g1 * factor);
	int b = (g1 * factor);
	int a = (a1 * factor);
	
	if(cf == RGB_888){
		return uGDLRGBComponentsToInt(r,g,b,RGB_888);	
	}
	else if(cf == RGBA_8888){
		return uGDLRGBAComponentsToInt(r,g,b,a);
	}
	else return uGDLRGBComponentsToInt(r,g,b,BGR_888);
}
/*
=======================================================================================
	Function   : uGDLRGBComponentsToInt
	Purpose    : An alternative to using the equivalent macro, packs our individual rgb component into a singular integer
	Parameters : r - The red component of the color
				 g - The green component of the color
				 b - The blue component of the color
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLRGBComponentsToInt(int r, int g, int b, ColorFormat cf){
	switch(cf){
		case RGB_888:{
			return r << 16 | g << 8 | b;
		}break;
		case BGR_888:{
			return b << 16 | g << 8 | r;
		}
		case RGB_565:{
			return r << 11 | g << 6 | b;
		}break;
		case BGR_565:{
			return b << 11 | g << 6 | r;
		}
		default: return r << 16 | g << 8 | b; break;
	}
}
/*
=======================================================================================
	Function   : uGDLRGBAComponentsToInt
	Purpose    : An alternative to using the equivalent macro, packs our individual rgba component into a singular integer
	Parameters : r - The red component of the color
				 g - The green component of the color
				 b - The blue component of the color
				 a - The alpha component of the color
				 cf - The color format, bit depth, of the color
	Returns	   : A combined color packed into an integer.
=======================================================================================
*/
int uGDLRGBAComponentsToInt(int r, int g, int b, int a){
	return r << 24 | g << 16 | b << 8 | a;
}
