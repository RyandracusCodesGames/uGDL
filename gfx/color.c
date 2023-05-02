#include "color.h"

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

int getA(int col, ColorFormat cf){
	switch(cf){
		case RGBA_8888:{
			return ((col & 0xff));
		}break;
	}
}

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

uGDL_RGB colToRGB(int col, ColorFormat cf){
	
	int r = getR(col, cf);
	int g = getG(col, cf);
	int b = getB(col, cf);
	
	uGDL_RGB rgb = {r, g, b};
	
	return rgb;
}

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

uGDL_PALETTE uGDLCreatePalette(uGDL_PALETTE *pal, int* col){
	int i;
	for(i = 0; i < sizeof(col)/sizeof(col[0]); i++){
		pal->palette[i] = col[i];
	}
}

void uGDLLoadTexturePalette(uGDL_PALETTE* pal, char * name, ColorFormat cf){
	uGDLTexture tex;
	uGDLLoadTexture(name, cf, &tex, 16, 16);
	
	int i;
	for(i = 0; i < MAXCOLORS; i++){
		pal->palette[i] = tex.tlut[i];
	}
}

void uGDLAddColToPalette(uGDL_PALETTE *pal, int index, int col){
	pal->palette[index] = col;
}
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
		return r << 16 | g << 8 | b;	
	}
	else if(cf == RGBA_8888){
		return r << 24 | g << 16 | b << 8 | a;
	}
	else return b << 16 | g << 8 | r;
}

int uGDLBlendColorWithVRAM(int col, uint32_t *VRAM, int x, int y, float factor, ColorFormat cf){
	return uGDLBlendColor(col, uGDLGetScreenPixel(VRAM, x, y, 0, 1), factor, cf);
}

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
		return r << 16 | g << 8 | b;	
	}
	else if(cf == RGBA_8888){
		return r << 24 | g << 16 | b << 8 | a;
	}
	else return b << 16 | g << 8 | r;
}

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
		return r << 16 | g << 8 | b;	
	}
	else if(cf == RGBA_8888){
		return r << 24 | g << 16 | b << 8 | a;
	}
	else return b << 16 | g << 8 | r;
}
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
		return r << 16 | g << 8 | b;	
	}
	else if(cf == RGBA_8888){
		return r << 24 | g << 16 | b << 8 | a;
	}
	else return b << 16 | g << 8 | r;
}
