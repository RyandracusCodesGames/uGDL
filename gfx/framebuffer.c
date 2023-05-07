#include "framebuffer.h"

void uGDLInitFrameBuffer(FrameBuffer *buf, int width, int height, ColorFormat cf){
	buf->width = width;
	buf->height = height;
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

void uGDLCopyBuffer(uint32_t *disp_buffer, uint32_t *draw_buffer){
	memcpy(draw_buffer, disp_buffer, 624 * 441);
}

void uGDLClearBackBuffer(uint32_t *draw_buffer){
	memset(draw_buffer, 0, 624 * 441);
}
