#ifndef DRAW_H
#define DRAW_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : draw.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/


#include "geometry.h"
#include "font.h"
#include "sprite.h"
#include <stdint.h>

#define WIDTH 624
#define HEIGHT 441
#define SCREEN_POINT 0
#define SCREEN_INDEX 1

/*uGDL uses geometric primitives such as points, lines, line-strips, triangles, and polygons 
  to render flat, two-dimensional shapes on to a computer monitor to render a full scene. */
  
/*Primitive Rasterization Functions*/
void uGDLDrawPoint(uint32_t *VRAM, uGDLPoint2D p, int col);
void uGDLFillScreen(uint32_t *VRAM, int col);
uGDLSprite uGDLScreenToSprite(uint32_t *VRAM);
void uGDLFadeScreen(uGDLSprite screen, uGDLSprite screen_buf, int col);
void uGDLDrawVertLine(uint32_t *VRAM, uGDLVertLine vl, int col);
void uGDLDrawHorzLine(uint32_t *VRAM, uGDLHorzLine hl, int col);
void uGDLDrawLine(uint32_t *VRAM, uGDLLine line, int col);
void uGDLDrawAALine(uint32_t *VRAM, uGDLLine line, int col);
void uGDLDrawTriangle(uint32_t *VRAM, uGDLTriangle tri, int col);
void uGDLDrawAATriangle(uint32_t *VRAM, uGDLTriangle tri, int col);
void uGDLDrawPolygon(uint32_t *VRAM, uGDLPolygon p, int nx, int ny, int col);
void uGDLDrawRect(uint32_t *VRAM, uGDLRect rect, int col);
void uGDLDrawChar(uint32_t *VRAM, uGDLFont font, char s, int tX, int tY, float sX, float sY);
void uGDLDrawString(uint32_t *VRAM, uGDLFont font, char * s, int tX, int tY, float sX, float sY);
void uGDLDrawCharOnCanvas(uGDLCanvas *canvas, uGDLFont font, char s, int tX, int tY, float sX, float sY);
void uGDLDrawStringOnCanvas(uGDLCanvas *canvas, uGDLFont font, char * s, int tX, int tY, float sX, float sY);
void uGDLDrawCirlceOutline(uint32_t *VRAM, int x, int y, int xc, int yc, int col);
void uGLDrawCircle(uint32_t *VRAM, uGDLCircle circle, int col);
void uGDLFillRect(uint32_t *VRAM, uGDLRect rect, int col);
void uGDLFillFlatTopTriangle(uint32_t *VRAM, uGDLTriangle tri, int col);
void uGDLFillFlatBottomTriangle(uint32_t *VRAM, uGDLTriangle tri, int col);
void uGDLFillTriangle(uint32_t *VRAM, uGDLTriangle t, int col);
void uGDLFillFastTriangle(uint32_t *VRAM, uGDLTriangle tri, int ool);
void uGDLFillPolygon(uint32_t *VRAM, uGDLPolygon p, int col);
void uGDLTextureRect(uint32_t *VRAM, uGDLRect rect);
int uGDLGetScreenPixel(uint32_t *VRAM, int x, int y, int index, int flag);
void uGDLFloodFill(uint32_t* VRAM, int x, int y, int col);
//void uGDLTextureTriangle(uint32_t* VRAM, int x1, int y1, float u1, float v1, float w1, int x2, int y2, float
 //   u2, float v2, float w2, int x3, int y3, float u3, float v3, float w3,T_TEXTURE texture, double visibility, int fog, int directionLighting, float dp);
 
 
/*TODO: Replace math utility functions in seperate source file*/
#define Abs(a) ((a) < 0 ? -(a) : a)
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define Max(a,b) ((a) > (b) ? (a) : (b))

#define TRUE 1
#define FALSE 0

int ipart(float x);
float uGDLRound(float x);
float fpart(float x);
float invfpart(float x);

#endif
