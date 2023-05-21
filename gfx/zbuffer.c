#include <stdlib.h>
#include "zbuffer.h"

void uGDLInitDepthBuffer(uGDLDepthBuffer *buf, int width, int height){
	buf->width = width;
	buf->height = height;
	buf->zBuffer = (float*)malloc(sizeof(float)*(width*height));
}

void uGDLClearBuffer(uGDLDepthBuffer *buf){
	int i;
	for(i = 0; i < buf->width * buf->height; i++){
		buf->zBuffer[i] = 0.0f;
	}
}

int uGDLCheckDepth(uGDLDepthBuffer buf, int x, int y, float value){
	
	if(x < 0 || y < 0 || x >= buf.width || y >= buf.height)
    {
        return 0;
    }
	if(buf.zBuffer[x + y * buf.width] < value){
		return 1;
	}
	else return 0;
}

void uGDLSetDepth(uGDLDepthBuffer* buf, int x, int y, float value){
	
	if(x < 0 || y < 0 || x >= buf->width || y >= buf->height)
    {
        return;
    }
          
    buf->zBuffer[x + y * buf->width] = value;
}


void uGDLFreeDepthBuffer(uGDLDepthBuffer *buf){
	free(buf->zBuffer);
}
