#ifndef DRAW_H
#define DRAW_H

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
void uGDLDrawTriangle(uint32_t *VRAM, uGDLTriangle tri, int col);
void uGDLDrawPolygon(uint32_t *VRAM, uGDLPolygon p, int nx, int ny, int col);
void uGDLDrawRect(uint32_t *VRAM, uGDLRect rect, int col);
void uGDLDrawChar(uint32_t *VRAM, uGDLFont font, char s, int tX, int tY);
void uGDLDrawString(uint32_t *VRAM, uGDLFont font, char * s, int tX, int tY);
void uGDLDrawCirlceOutline(uint32_t *VRAM, int x, int y, int xc, int yc, int col);
void uGLDrawCircle(uint32_t *VRAM, uGDLCircle circle, int col);
void uGDLFillRect(uint32_t *VRAM, uGDLRect rect, int col);
void uGDLFillTriangle(uint32_t *VRAM, uGDLTriangle t, int col);
void uGDLFastFillTriangle(uint32_t *VRAM, uGDLTriangle t, int ool);
void uGDLFillPolygon(uint32_t *VRAM, uGDLPolygon p, int col);
void uGDLTextureRect(uint32_t *VRAM, uGDLRect rect);
int uGDLGetScreenPixel(uint32_t *VRAM, int x, int y, int index, int flag);
//void uGDLTextureTriangle(uint32_t* VRAM, int x1, int y1, float u1, float v1, float w1, int x2, int y2, float
 //   u2, float v2, float w2, int x3, int y3, float u3, float v3, float w3,T_TEXTURE texture, double visibility, int fog, int directionLighting, float dp);
#endif
