#include <stdlib.h>
#include <string.h>
#include "framebuffer.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : framebuffer.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLInitFrameBuffer
	Purpose    : Initializes the core components needed to describe our frame buffer
	Parameters : buf - A reference to a frame buffer structure
				 width - The width of the frame buffer
				 height - The height of the frame buffer
				 cf - The color format, bit depth, of the frame buffer
	Returns	   : void
=======================================================================================
*/
void uGDLInitFrameBuffer(FrameBuffer *buf, int width, int height, ColorFormat cf){
	buf->width = width;
	buf->height = height;
	buf->VRAM = (uint32_t*)malloc(sizeof(uint32_t)*(buf->width*buf->height));
	buf->cf = cf;
}

/*
=======================================================================================
	Function   : uGDLSetScissor
	Purpose    : Initializes the ability to clip any off-screen pixels from being drawn to avoid crashes
	Parameters : x - The beginning x - coordinate to start our scisccor
				 y - The beginning y - coordinate to start our scissor
				 width - The width of the scissor
				 height - The height of the scissor
	Returns	   : void
=======================================================================================
*/
void uGDLSetScissor(int x, int y, int width, int height){
	sciptr.x = x;
	sciptr.y = y;
	sciptr.width = width;
	sciptr.height = height;
	sciptr.scissor = 1;
}
/*
=======================================================================================
	Function   : uGDLInitDispInfo
	Purpose    : Initializes the core components needed to describe our window display
	Parameters : screen - A reference to a screen structure
	             tvw - The width of our screen
				 tvh - The height of our screen
				 x - The x - coordinate offset to place our window 
				 y - The y - coordinate offset to place our window
				 name - The name of our window application
	Returns	   : void
=======================================================================================
*/
void uGDLInitDispInfo(Screen *screen, TV_SCREEN_WIDTH tvw, TV_SCREEN_HEIGHT tvh, int screen_x, int screen_y, char* name){
	screen->tvw = tvw;
	screen->tvh = tvh;
	screen->screen_x = screen_x;
	screen->screen_y = screen_y;
	screen->name = name;
}
/*
=======================================================================================
	Function   : uGDLCopyBuffer
	Purpose    : Copies the memory of our draw buffer into our display buffer
	Parameters : buf - A reference to a frame buffer structure
				 draw_buffer - A reference to the video memory of our back buffer
	Returns	   : void
=======================================================================================
*/
void uGDLCopyBuffer(FrameBuffer *buf, uint32_t *draw_buffer){
	memcpy(buf->VRAM, draw_buffer, sizeof(uint32_t) * buf->width * buf->height);
}
/*
=======================================================================================
	Function   : uGDLClearBackBuffer
	Purpose    : Clears the memory of the back buffer to a particular color, erasing anything previously drawn to it
	Parameters : draw_buffer - A reference to the video memory of our back buffer
				 width - The width of the back buffer
				 height - The height of the back buffer
	Returns	   : void
=======================================================================================
*/
void uGDLClearBackBuffer(uint32_t *draw_buffer, int width, int height){
	memset(draw_buffer, 0, sizeof(uint32_t) * width * height);
}
/*
=======================================================================================
	Function   : uGDLFreeFrameBuffer
	Purpose    : Frees the allocated memory of our frame buffer
	Parameters : buf - A reference to a frame buffer structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeFrameBuffer(FrameBuffer *buf){
	free(buf->VRAM);
}
