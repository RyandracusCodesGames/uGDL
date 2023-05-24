#ifndef CANVAS_H
#define CANVAS_H

#include "framebuffer.h"
#include "geometry.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : canvas.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*A CANVAS IS A RECTANGULAR DRAWABLE AREA WITH A UNIQUE GRAPHICS CONTEXT IN THE LARGER DISPLAY OF A FRAME BUFFER*/
/*SIMPLISTIC DEFINITION: A GLORIFIED TEXTURED RECTANGLE*/
typedef struct{
	int x, y;	/*x and y screen offset*/
	int width, height; /*width and height of rectangle*/
	ColorFormat cf;
	uint32_t *VRAM;
}uGDLCanvas;

/*Initialization and Essential Utility Functions For a Canvas*/
uGDLCanvas uGDLCreateCanvas(int x, int y, int width, int height, ColorFormat cf);
int uGDLGetCanvasPixel(uGDLCanvas *canvas, int x, int y);
void uGDLFreeCanvas(uGDLCanvas *canvas);
/*Display Canvas to Frame Buffer*/
void uGDLDispCanvas(uGDLCanvas canvas, FrameBuffer *buf);
void uGDLDispTranslatedCanvas(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY);
void uGDLDispScaledCanvas(uGDLCanvas canvas, FrameBuffer *buf, float sX,float sY);
void uGDLFlipCanvasHorz(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY);
void uGDLFlipCanvasVert(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY);
void uGDLDispCanvasHorzAndVert(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY);
/*Rasterization functions applied to the canvas*/
void uGDLDrawPointOnCanvas(uGDLCanvas *canvas, uGDLPoint2D p, int col);
void uGDLClearCanvas(uGDLCanvas *canvas, int col);
void uGDLDrawVertLineOnCanvas(uGDLCanvas *canvas, uGDLVertLine vline, int col);
void uGDLDrawHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hline, int col);
void uGDLDrawLineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col);
void uGDLDrawAALineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col);
void uGDLDrawTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLDrawAATriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLDrawRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLFillFlatTopTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLFillFlatBottomTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLFillFastTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri,  int col);
void uGDLFillTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle t, int col);
void uGDLFillRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLDrawCircleOnCanvas(uGDLCanvas *canvas, uGDLCircle circle, int col);
void uGDLConvertCanvasToGrayscale(uGDLCanvas *canvas);
#endif
