#ifndef COLOR_H
#define COLOR_H

#include "framebuffer.h"
#include "texture.h"
#include "draw.h"

#define MAXCOLORS 256

/*Essential macros, functions, and structures to create a well-defined color library*/
#define uGDL_RGBA8888(r,g,b,a) ((r) << 24 | (g) << 16 | (b) << 8 | (a))
#define uGDL_RGB888(r,g,b) ((r) << 16 | (g) << 8 | b)
#define uGDL_BGR888(b,g,r) ((b) << 16 | (g) << 8 | r)
#define uGDL_RGB565(r,g,b) ((r) << 11 | (g) << 6 | b)
#define uGDL_BGR565(b,g,r) ((b) << 11 | (g) << 6 | r)
/*Basic Color Palette for 24-Bit RGB Colors*/
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define GRAY 0x808080
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define RED 0xFF0000
#define YELLOW 0x00FFFF
#define ORANGE 0xFFA500
#define BROWN 0x964B00
#define PURPLE 0x4B0082
#define PINK 0xFFC0CB
/*Basic Color Palette for 24-Bit BGR Colors*/
#define BLUE_REVERSE 0xFF0000
#define RED_REVERSE 0x0000FF
#define YELLOW_REVERSE 0xFFFF00
#define ORANGE_REVERSE 0x00A5FF
#define BROWN_REVERSE 0x004B96
#define PURPLE_REVERSE 0x82004B
#define PINK_REVERSE 0xCBC0FF
/*Basic Color Palette for 32-Bit RGB Colors*/
#define BLACK_8888 0x000000FF
#define WHITE_8888 0xFFFFFFFF
#define GRAY_8888 0x808080FF
#define BLUE_8888 0x0000FFFF
#define GREEN_8888 0x00FF00FF
#define RED_8888 0xFF0000FF
#define YELLOW_8888 0x00FFFFFF
#define ORANGE_8888 0xFFA500FF
#define BROWN_8888 0x964B00FF
#define PURPLE_8888 0x4B0082FF
#define PINK_8888 0xFFC0CBFF
/*Basic Color Palette for 16-Bit RGB Colors*/
#define BLACK_565 0x0001
#define WHITE_565 0xFFFF
#define GRAY_565 0x528A
#define RED_565 0xF801
#define BLUE_565 0x003F
#define GREEN_565 0x07C1
#define YELLOW_565 0xFFC1
#define PURPLE_565 0xA81F
#define ORANGE_565 0xFD20
#define BROWN_565 0x9240
/*Sega Dreamcast Inspired Color Mixing Modes*/
/*MULTIPLY SOURCE COLOR BY (1-As, 1-As, 1-As, 1-As) AND DESTINATION COLOR BY (As, As, As, As) AND BLEND*/
#define BLEND_COLOR_BOTHINVALPHA 0x14
/*MULTIPLY SOURCE COLOR BY (As, As, As, As) AND DESTINATION COLOR BY (1-As, 1-As, 1-As, 1-As) AND BLEND*/
#define BLEND_COLOR_BOTHSRCALPHA 0x15
/*MULTIPLY SOURCE COLOR BY (Ad, Ad, Ad, Ad) AND BLEND*/
#define BLEND_COLOR_DESTALPHA 0x16
/*MULTIPLY DESTINATION COLOR BY (Ad, Ad, Ad, Ad) AND BLEND*/
#define BLEND_COLOR_SRCALPHA 0x17
/*MULTIPLY SPECIFIED SOURCE BY (1-Ad, 1-Ad, 1-Ad, 1-Ad) AND BLEND*/
#define BLEND_COLOR_INVDESTALPHA 0x18
typedef struct{
	int r, g, b;
}uGDL_RGB;

typedef struct{
	int r, g, b, a;
}uGDL_RGBA;

typedef struct{
	int palette[MAXCOLORS];
}uGDL_PALETTE;

int getB(int col, ColorFormat cf);
int getA(int col, ColorFormat cf);
int getCol(uGDL_RGB rgb, ColorFormat cf);
int uGDLSetColor(int col, ColorFormat cf);
int randColor();
uGDL_RGB colToRGB(int col, ColorFormat cf);
uGDL_RGBA colToRGBA(int col, ColorFormat cf);
uGDL_PALETTE uGDLCreatePalette(uGDL_PALETTE* pal, int* col);
void uGDLLoadTexturePalette(uGDL_PALETTE* pal, char * name, ColorFormat cf);
void uGDLAddColToPalette(uGDL_PALETTE *pal, int index, int col);
int uGDLBlendColor(int col1, int col2, float ratio, ColorFormat cf);
int uGDLBlendColorMode(int col1, int col2, float factor, ColorFormat cf, int mode);
int uGDLBlendColorWithVRAM(int col, uint32_t *VRAM, int x, int y, float factor, ColorFormat cf);
int uGDLAddColor(int col1, int col2, ColorFormat cf);
int uGDLInterpColor(int col1, int col2, float interp, ColorFormat cf);
int uGDLColToGrayscale(int col, ColorFormat cf);
int uGDLDotColor(int col1, float factor, ColorFormat cf);
int uGDLClampColor(int col1, int max, int min, int target, ColorFormat cf);
int uGDLRGBComponentsToInt(int r, int g, int b, ColorFormat cf);
int uGDLRGBAComponentsToInt(int r, int g, int b, int a);
#endif
