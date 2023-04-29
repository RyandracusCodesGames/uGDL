#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <stdint.h>

/*Enumeration to represent the most common bit-depth's for color in computer graphics*/
typedef enum ColorFormat{
	RGBA_8888 = 0,/*32 Bit BGR*/
	RGB_888 = 1,  /*24 Bit RGB*/
	BGR_888 = 2,  /*24 Bit BGR*/
	RGB_565 = 3,  /*16 Bit RGB*/
	BGR_565 = 4,  /*16 Bit BGR*/
}ColorFormat;

typedef struct{
	int width;
	int height;
	ColorFormat cf;
	uint32_t *VRAM;
}FrameBuffer;

/*The respective screen resolutions for the 5th generation consoles*/
typedef enum TV_SCREEN_WIDTH{
	SEGA_SATURN_W = 320,
	PLAYSTATION_W = 310,
	NINTENDO_64_W = 640,
	GAMEBOY_ADVANCE_W = 240,
}TV_SCREEN_WIDTH;

typedef enum TV_SCEEN_HEIGHT{
	SEGA_SATURN_H = 224,
	PLAYSTATION_H = 220,
	NINTENDO_64_H = 480,
	GAMEBOY_ADVANCE_H = 160,
}TV_SCREEN_HEIGHT;
/*Defines the width, height, beginning x and y points, and name of our window display*/
typedef struct{
	TV_SCREEN_WIDTH tvw;
	TV_SCREEN_HEIGHT tvh;
	int screen_x;
	int screen_y;
	char *name;
}Screen;

void uGDLInitFrameBuffer(FrameBuffer *buf, int width, int height, ColorFormat cf);
/*Some platforms require a manual page flip to avoid page tearing artifacts*/
void uGDLSwapBuffers();
/*Some platforms require the programmer to wait for all vertical scanlines to be done drawing before swapping buffers*/
void uGDLWaitVBlank();
/*Initialize the core components our of ouw window display*/
void uGDLInitDispInfo(Screen *screen, TV_SCREEN_WIDTH tvw, TV_SCREEN_HEIGHT tvh, int screen_x, int screen_y, char* name);
/*Copy the memory of one buffer to another*/
void uGDLCopyBuffer(uint32_t *disp_buffer, uint32_t *draw_buffer);
/*If we decided to swap buffers, useful utility function to clear the memory of the back buffer*/
void uGDLClearBackBuffer(uint32_t *draw_buffer);
#endif
