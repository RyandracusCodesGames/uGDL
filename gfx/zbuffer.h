#ifndef ZBUFFER_H
#define ZBUFFER_H

typedef struct{
	int width, height;
	float *zBuffer;
}uGDLDepthBuffer;

void uGDLInitDepthBuffer(uGDLDepthBuffer *buf, int width, int height);
void uGDLClearDepthBuffer(uGDLDepthBuffer *buf);
int uGDLCheckDepth(uGDLDepthBuffer buf, int x,int y, float value);
void uGDLSetDepth(uGDLDepthBuffer *buf, int x, int y, float value);
void uGDLFreeDepthBuffer(uGDLDepthBuffer *buf);

#endif
