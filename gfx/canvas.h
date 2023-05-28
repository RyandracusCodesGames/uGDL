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
void uGDLDrawGouraudVertLineOnCanvas(uGDLCanvas *canvas, uGDLVertLine vl, int col1, int col2);
void uGDLDrawHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hline, int col);
void uGDLDrawGouraudHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hl, int col1, int col2);
void uGDLDrawLineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col);
void uGDLDrawGouraudLineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col1, int col2);
void uGDLDrawAALineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col);
void uGDLDrawTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLDrawGouraudTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3);
void uGDLDrawAATriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLDrawRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLDrawGouraudRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col1, int col2, int col3, int col4);
void uGDLFillFlatTopTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLFillGouraudFlatTopTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3);
void uGDLFillFlatBottomTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLFillGouraudFlatBottomTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3);
void uGDLFillFastTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri,  int col);
void uGDLFillFastGouraudTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3);
void uGDLFillTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle t, int col);
void uGDLFillRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLFillGouraudRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col1, int col2, int col3, int col4);
void uGDLDrawCircleOnCanvas(uGDLCanvas *canvas, uGDLCircle circle, int col);
void uGDLConvertCanvasToGrayscale(uGDLCanvas *canvas);
/*Polymorphic function to render any geometric primitive with defined attributes*/
#define SHAPE_POINT  0x1
#define SHAPE_RECT   0x2
#define SHAPE_VLINE  0x3
#define SHAPE_HLINE  0x4
#define SHAPE_LINE   0x5
#define SHAPE_TRI    0x6
#define SHAPE_POLY   0x7
#define SHAPE_CIRCLE 0x8

#define CYCLE_DRAW   0x9
#define CYCLE_FILL	 0x10

#define AA 			 0x11
#define NO_AA 		 0x12
void uGDLDispGeomOnCanvas(uGDLCanvas *canvas, int shape, uGDLGeom geom, int cycle, int aa, int blend, float factor, int col1, int col2, ColorFormat cf);
#endif
