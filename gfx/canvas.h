#ifndef CANVAS_H
#define CANVAS_H

#include "framebuffer.h"
#include "geometry.h"

/*A CANVAS IS A RECTANGULAR DRAWABLE AREA WITH A UNIQUE GRAPHICS CONTEXT IN THE LARGER DISPLAY OF A FRAME BUFFER*/
/*SIMPLISTIC DEFINITION: A TEXTURED RECTANGLE*/
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
void uGDLDrawTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col);
void uGDLDrawRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLFillTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle t, int col);
void uGDLFillRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col);
void uGDLDrawCircleOnCanvas(uGDLCanvas *canvas, uGDLCircle circle, int col);
#endif
