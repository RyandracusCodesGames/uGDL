#ifndef ZBUFFER_H
#define ZBUFFER_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : zbuffer.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

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
