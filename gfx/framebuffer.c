#include "framebuffer.h"

void uGDLInitFrameBuffer(FrameBuffer *buf, int width, int height, ColorFormat cf){
	buf->width = width;
	buf->height = height;
	buf->VRAM = (uint32_t*)malloc(sizeof(uint32_t)*(buf->width*buf->height));
	buf->cf = cf;
}

void uGDLSetScissor(int x, int y, int width, int height){
	sciptr.x = x;
	sciptr.y = y;
	sciptr.width = width;
	sciptr.height = height;
}

void uGDLInitDispInfo(Screen *screen, TV_SCREEN_WIDTH tvw, TV_SCREEN_HEIGHT tvh, int screen_x, int screen_y, char* name){
	screen->tvw = tvw;
	screen->tvh = tvh;
	screen->screen_x = screen_x;
	screen->screen_y = screen_y;
	screen->name = name;
}

void uGDLCopyBuffer(FrameBuffer *buf, uint32_t *draw_buffer){
	memcpy(buf->VRAM, draw_buffer, sizeof(uint32_t) * buf->width * buf->height);
}

void uGDLClearBackBuffer(uint32_t *draw_buffer, int width, int height){
	memset(draw_buffer, 0, sizeof(uint32_t) * width * height);
}

void uGDLFreeFrameBuffer(FrameBuffer *buf){
	free(buf->VRAM);
}
