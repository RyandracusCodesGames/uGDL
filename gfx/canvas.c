#include <stdlib.h>
#include "canvas.h"
#include "draw.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : canvas.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLCreateCanvas
	Purpose    : Creates a rectangular drawable area with a unique graphics context in the larger display of the frame buffer
	Parameters : x - The x - coordinate offset of the canvas
				 y - The y - coordinate offset of the canvas
				 width - The width of the canvas
				 height - The height of the canvas
				 cf - The color format, the bit depth, of the canvas
	Returns	   : A uGDLCanvas structure.
=======================================================================================
*/
uGDLCanvas uGDLCreateCanvas(int x, int y, int width, int height, ColorFormat cf){
	uGDLCanvas canvas;
	canvas.x = x;
	canvas.y = y;
	canvas.width = width;
	canvas.height = height;
	canvas.VRAM = (uint32_t*)malloc(sizeof(uint32_t)*(width*height));
	return canvas;
}
/*
=======================================================================================
	Function   : uGDLGetCanvasPixel
	Purpose    : Returns the color located at the specificed coordinates of the canvas
	Parameters : x - The x - coordinate
				 y - The y - coordinate
	Returns	   : A color packed into an integer.
=======================================================================================
*/
int uGDLGetCanvasPixel(uGDLCanvas *canvas, int x, int y){
	if(x >= 0 && y >= 0 && x < canvas->width && y < canvas->height){
		return canvas->VRAM[x + y * canvas->width];
	}
}
/*
=======================================================================================
	Function   : uGDLFreeCanvas
	Purpose    : Frees the allocated memory of the canvas
	Parameters : canvas - A reference to a canvas structure
	Returns	   : void
=======================================================================================
*/
void uGDLFreeCanvas(uGDLCanvas *canvas){
	free(canvas->VRAM);
}
/*
=======================================================================================
	Function   : uGDLDispCanvas
	Purpose    : Displays our canvas to the window display
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
	Returns	   : void
=======================================================================================
*/
void uGDLDispCanvas(uGDLCanvas *canvas, FrameBuffer *buf){
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x, y + canvas->y), uGDLGetCanvasPixel(canvas, x, y));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLFlipCanvasVert
	Purpose    : Displays our canvas to the screen vertically flipped with a translation offset
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
				 tX - The x - coordinate translation offset
				 tY - The y - coordinate translation offset
	Returns	   : void
=======================================================================================
*/
void uGDLFlipCanvasVert(uGDLCanvas *canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x + tX, y + canvas->y + tY), uGDLGetCanvasPixel(canvas, x, canvas->height - y));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLFlipCanvasHorz
	Purpose    : Displays our canvas to the screen horizontally flipped with a translation offset
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
				 tX - The x - coordinate translation offset
				 tY - The y - coordinate translation offset
	Returns	   : void
=======================================================================================
*/
void uGDLFlipCanvasHorz(uGDLCanvas *canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x + tX, y + canvas->y + tY), uGDLGetCanvasPixel(canvas, canvas->width - x, y));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLFlipCanvasHorzAndVert
	Purpose    : Displays our canvas to the screen horizontally and vertically flipped with a translation offset
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
				 tX - The x - coordinate translation offset
				 tY - The y - coordinate translation offset
	Returns	   : void
=======================================================================================
*/
void uGDLFlipCanvasHorzAndVert(uGDLCanvas *canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x + tX, y + canvas->y + tY), uGDLGetCanvasPixel(canvas, canvas->width - x, canvas->height - y));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLDispTranslatedCanvas
	Purpose    : Displays our canvas to the screen with a translation offset
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
				 tX - The x - coordinate translation offset
				 tY - The y - coordinate translation offset
	Returns	   : void
=======================================================================================
*/
void uGDLDispTranslatedCanvas(uGDLCanvas *canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas->height; y++){
		for(x = 0; x < canvas->width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x + tX, y + canvas->y + tY), uGDLGetCanvasPixel(canvas, x, y));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLDispScaledCanvas
	Purpose    : Displays a scaled canvas to the window display with a scale factor
	Parameters : canvas - A canvas structure
				 buf - A reference to a frame buffer structure
				 sX - The x - coordinate scale factor
				 sY - The y - coordinate scale factor
	Returns	   : void
=======================================================================================
*/
void uGDLDispScaledCanvas(uGDLCanvas *canvas, FrameBuffer *buf, float sX, float sY){
	int w1 = canvas->width, w2 = (int)(canvas->width * sX);
	int h1 = canvas->height, h2 = (int)(canvas->height * sY);
	
	int x_factor = ((w1<<16)/ w2) + 1;
	int y_factor = ((h1<<16)/ h2) + 1;
	
	int x, y, x2, y2, i;
	for(i = 0; i < w2 * h2; i++){
		x = i % w2, y = i / w2;
		x2 = ((x*x_factor)>>16);
		y2 = ((y*y_factor)>>16);
		uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas->x,y + canvas->y),uGDLGetCanvasPixel(canvas, x2, y2));
	}
}
/*
=======================================================================================
	Function   : uGDLDrawPointOnCanvas
	Purpose    : Draws a singular point to the canvas
	Parameters : canvas - A reference to a canvas structure
				 p - A 2D-Point structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawPointOnCanvas(uGDLCanvas *canvas, uGDLPoint2D p, int col){
	if(p.x >= 0 && p.y >= 0 && p.x < canvas->width && p.y < canvas->height){
		canvas->VRAM[p.x + p.y * canvas->width] = col;
	}
}
/*
=======================================================================================
	Function   : uGDLClearCanvas
	Purpose    : Fills the entire canvas with one color, clearing everything previously drawn to it
	Parameters : canvas - A reference to a canvas structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLClearCanvas(uGDLCanvas *canvas, int col){
	int i;
	for(i = 0; i < canvas->width * canvas->height; i++){
		canvas->VRAM[i] = col;
	}
}
/*
=======================================================================================
	Function   : uGDLDrawVertLineOnCanvas
	Purpose    : Draws a vertical line to a canvas
	Parameters : canvas - A reference to a canvas structure
				 vline - A vertical line structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawVertLineOnCanvas(uGDLCanvas *canvas, uGDLVertLine vline, int col){
	if(vline.y2 < vline.y1){
		int y;
		for(y = vline.y1; y >= vline.y2; y--){
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(vline.x, y), col);
		}
	}
	else{
		int y;
		for(y = vline.y1; y <= vline.y2; y++){
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(vline.x, y), col);
		}
	}
}
/*
=======================================================================================
	Function   : uGDLDrawGouraudVertLineOnCanvas
	Purpose    : Draws a gouraud shaded vertical line to a canvas
	Parameters : canvas - A reference to a canvas structure
				 v1 - A vertical line structure
				 col1 - The first color
				 col2 - The second color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawGouraudVertLineOnCanvas(uGDLCanvas *canvas, uGDLVertLine vl, int col1, int col2){
	if(vl.y2 < vl.y1){
		int y;
		for(y = vl.y1; y >= vl.y2; y--){
			float factor = (vl.y1 - y)/(float)(vl.y1 - vl.y2);
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(vl.x, y), uGDLInterpColor(col1,col2,factor,RGB_888));
		}
	}
	else{
		int y;
		for(y = vl.y1; y <= vl.y2; y++){
			float factor = (vl.y2 - y)/(float)(vl.y2 - vl.y1);
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(vl.x, y), uGDLInterpColor(col1,col2,factor,RGB_888));
		}
	}
}
/*
=======================================================================================
	Function   : uGDLDrawHorzLineOnCanvas
	Purpose    : Draws a horizontal line on the canvas
	Parameters : canvas - A reference to a canvas structure
				 hline - A horizontal line structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hline, int col){
	if(hline.x1 > hline.x2){
		int x;
		for(x = hline.x1; x >= hline.x2; x--){
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, hline.y), col);
		}
	}
	else{
		int x;
		for(x = hline.x1; x <= hline.x2; x++){
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, hline.y), col);
		}
	}
}
/*
=======================================================================================
	Function   : uGDLDrawGouraudHorzLineOnCanvas
	Purpose    : Draws a gouraud shaded horizontal line on the canvas
	Parameters : canvas - A reference to a canvas structure
				 hline - A horizontal line structure
				 col1 - The first color
				 col2 - The second color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawGouraudHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hl, int col1, int col2){
	if(hl.x1 > hl.x2){
		int x;
		for(x = hl.x1 - 2; x > hl.x2 - 1; x--){
			float factor = (hl.x1 - x)/(float)(hl.x1 - hl.x2);
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, hl.y), uGDLInterpColor(col1,col2,factor,RGB_888));
		}
	}
	else{
		int x;
		for(x = hl.x1 - 2; x <= hl.x2 - 1; x++){
			float factor = (hl.x2 - x)/(float)(hl.x2 - hl.x1);
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, hl.y), uGDLInterpColor(col1,col2,factor,RGB_888));
		}
	}
}

/*
=======================================================================================
	Function   : uGDLDrawLineOnCanvas
	Purpose    : Draws any type of line to the canvas
	Parameters : canvas - A reference to a canvas structure
				 line - A line structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawLineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col){
	int x1 = line.x1, x2 = line.x2, y1 = line.y1, y2 = line.y2;
	int dx, dy, sx, sy, err, e2;
	
	if(x1 == x2){
		uGDLDrawVertLineOnCanvas(canvas, uGDLCreateVertLine(x1, y1, y2), col);
		return;
	}
	
	if(y1 == y2){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine(x1, x2, y1), col);
		return;
	}
	
	dx = Abs(x1 - x2);
	dy = Abs(y1 - y2);
	
	if(x1 < x2){
		sx = 1;
	}
	else{
		sx = -1;
	}
	
	if(y1 < y2){
		sy = 1;
	}
	else{
		sy = -1;
	}
	
	err = dx - dy;
	
	do{
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x1,y1),col);
		e2 = err * 2;
		if(e2 > - dy){
			err -= dy;
			x1 += sx;
		}
		if(e2 < dx){
			err += dx;
			y1 += sy;
		}
	}while(x1 != x2 || y1 != y2);
}
/*
=======================================================================================
	Function   : uGDLDrawGouraudLineOnCanvas
	Purpose    : Draws any type of line gouraud shaded on a canvas
	Parameters : canvas - A reference to a canvas structure
				 line - A line structure
				 col1 - The first color
				 col2 - The second color
				 col3 - The third color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawGouraudLineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col1, int col2){
	int x1 = line.x1, x2 = line.x2, y1 = line.y1, y2 = line.y2;
	int dx, dy, sx, sy, err, e2;
	
	if(x1 == x2){
		uGDLDrawGouraudVertLineOnCanvas(canvas, uGDLCreateVertLine(x1, y1, y2), col1, col2);
		return;
	}
	
	if(y1 == y2){;
		uGDLDrawGouraudHorzLineOnCanvas(canvas, uGDLCreateHorzLine(x1, x2, y1), col1, col2);
		return;
	}
	
	dx = Abs(x2 - x1);
	dy = Abs(y2 - y1);
	
	if(x1 < x2){
		sx = 1;
	}
	else{
		sx = -1;
	}
	
	if(y1 < y2){
		sy = 1;
	}
	else{
		sy = -1;
	}
	
	err = dx - dy;
	
	int initx = x1;
	
	do{
		float interp = ((float)(x2 - x1)/(x2-initx));
		
		if(sx == 1){
			interp = ((float)(x2 - x1)/(x2-initx));
		}				
		else{
			interp = 1.0f - ((float)(x2 - x1)/(x2-initx));
		}
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x1, y1), uGDLInterpColor(col1,col2,interp,RGB_888));
		e2 = err * 2;
		if (e2 > -dy) 
		{
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) 
		{
            err += dx;
            y1 += sy;
        }
	}while(x1 != x2 || y1 != y2);
}
/*
=======================================================================================
	Function   : uGDLDrawAALineOnCanvas
	Purpose    : Draws an anti-aliased line to a canvas
	Parameters : canvas - A reference to a canvas structure
				 line - A line structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawAALineOnCanvas(uGDLCanvas *canvas, uGDLLine line, int col){
	int x1 = line.x1, x2 = line.x2, y1 = line.y1, y2 = line.y2;
	
	if(x1 == x2){
		uGDLDrawVertLineOnCanvas(canvas, uGDLCreateVertLine(x1, y1, y2), col);
	}
	
	if(y1 == y2){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine(x1, x2, y1), col);
	}
	
	int steep = Abs(y2 - y1) > Abs(x2 - x1);
	
	if(steep){
		SWAP(&x1, &y1);
		SWAP(&x2, &y2);
	}
	
	if(x1 > x2){
		SWAP(&x1, &x2);
		SWAP(&y1, &y2);
	}
	
	float dx = x2 - x1;
	float dy = y2 - y1;
	
	float slope;
	if(dx == 0.0f){
		slope = 1.0f;
	}
	else{
		slope = dy / dx;
	}
	
	float xend, yend, xgap, xpxl1, ypxl1, xpxl2, ypxl2;
	
	xend = uGDLRound(x1);
	yend = y1 + slope * (xend - x1);
	xgap = invfpart(x1 + 0.5f);
	xpxl1 = xend;
	ypxl1 = ipart(yend);
	
	if (steep){
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ypxl1, xpxl1), col);
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ypxl1+1, xpxl1), col);
	}else{
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xpxl1, ypxl1), col);
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xpxl1, ypxl1+1), col);
	}
        
    float intery = yend + slope;
    
    xend = uGDLRound(x2);
    yend = y2 + slope * (xend - x2);
    xgap = fpart(x2 + 0.5f);
    xpxl2 = xend;
    ypxl2 = ipart(yend);
    
    if(steep){
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ypxl2, xpxl2), col);
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ypxl2+1, xpxl2), col);
    }
    else{
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xpxl2, ypxl2), col);
        uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xpxl2, ypxl2+1), col);
	}
	
    if(steep){
    	int x;
        for (x = xpxl1 + 1; x <= xpxl2 - 1; x++){
        	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ipart(intery), x), col);
            uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(ipart(intery)+1, x), col);
            intery = intery + slope;
        }
    }
    else{
    	int x;
        for (x = xpxl1 + 1; x <= xpxl2 - 1; x++){
        	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, ipart(intery)), col);
            uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, ipart(intery)+1), col);
            intery = intery + slope;
        }
    }         
}
/*
=======================================================================================
	Function   : uGDLDrawTriangleOnCanvas
	Purpose    : Draws a triangle on the canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col){
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x1, tri.y1, tri.x2, tri.y2), col);
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x2, tri.y2, tri.x3, tri.y3), col);
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x3, tri.y3, tri.x1, tri.y1), col);
}
/*
=======================================================================================
	Function   : uGDLDrawGouraudTriangle
	Purpose    : Draws a gouraud shaded triangle to a canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col1 - The first color
				 col2 - The second color
				 col3 - The third color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawGouraudTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3){
	uGDLLine line1 = {tri.x1, tri.y1, tri.x2, tri.y2};
	uGDLLine line2 = {tri.x2, tri.y2, tri.x3, tri.y3};
	uGDLLine line3 = {tri.x3, tri.y3, tri.x1, tri.y1};
	
	uGDLDrawGouraudLineOnCanvas(canvas, line1, col1, col2);
	uGDLDrawGouraudLineOnCanvas(canvas, line2, col2, col3);
	uGDLDrawGouraudLineOnCanvas(canvas, line3, col3, col1);
}
/*
=======================================================================================
	Function   : uGDLDrawAATriangleOnCanvas
	Purpose    : Draws an anti-aliased triangle to the canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawAATriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col){
	uGDLDrawAALineOnCanvas(canvas, uGDLCreateLine(tri.x1, tri.y1, tri.x2, tri.y2), col);
	uGDLDrawAALineOnCanvas(canvas, uGDLCreateLine(tri.x2, tri.y2, tri.x3, tri.y3), col);
	uGDLDrawAALineOnCanvas(canvas, uGDLCreateLine(tri.x3, tri.y3, tri.x1, tri.y1), col);
}
/*
=======================================================================================
	Function   : uGDLDrawRectOnCanvas
	Purpose    : Draws a rectangle on the canvas
	Parameters : canvas - A reference to a canvas structure
				 rect - A rectangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col){
	
	int x = rect.x, y = rect.y, height = rect.height, width = rect.width;
	
	if(x < 0){
		x = 0;
	}
	else if (x > WIDTH){
		x = WIDTH - width;
	}
	
	if(y < 0){
		y = 0;
	}
	else if(y > HEIGHT){
		y = HEIGHT - height;
	}
	
	uGDLVertLine v1 = {x, y, y + height};
	uGDLVertLine v2 = {x + width, y, y + height};
	uGDLHorzLine h1 = {x, x + width, y + height};
	uGDLHorzLine h2 = {x, x + width, y};
	
	uGDLDrawVertLineOnCanvas(canvas, v1, col);
	uGDLDrawVertLineOnCanvas(canvas, v2, col);
	uGDLDrawHorzLineOnCanvas(canvas, h1, col);
	uGDLDrawHorzLineOnCanvas(canvas, h2, col);
}

/*
=======================================================================================
	Function   : uGDLDrawGouraudRectOnCanvas
	Purpose    : Draws a gouraud shaded rectangle to a canvas
	Parameters : canvas - A reference to a canvas structure
				 rect - A rectangle structure
				 col1 - The first color
				 col2 - The second color
				 col3 - The third color
				 col4 - The fourth color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawGouraudRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col1, int col2, int col3, int col4){
	int x = rect.x, y = rect.y, height = rect.height, width = rect.width;
	
	uGDLVertLine v1 = {x, y, y + height};
	uGDLVertLine v2 = {x + width, y, y + height};
	uGDLHorzLine h1 = {x, x + width, y + height};
	uGDLHorzLine h2 = {x, x + width, y};
	
	uGDLDrawGouraudVertLineOnCanvas(canvas, v1, col1, col2);
	uGDLDrawGouraudVertLineOnCanvas(canvas, v2, col3, col4);
	uGDLDrawGouraudHorzLineOnCanvas(canvas, h1, col3, col2);
	uGDLDrawGouraudHorzLineOnCanvas(canvas, h2, col1, col4);
}

/*
=======================================================================================
	Function   : uGDLFillFlatTopTriangleOnCanvas
	Purpose    : Draws a triangle with a flat top, a top with a horizontal line, to the canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillFlatTopTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col){
	float invslope1 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	float invslope2 = (tri.x3 - tri.x2)/(float)(tri.y3 - tri.y2);
	
	float currx1 = tri.x3;
	float currx2 = tri.x3;
	
	int y;
	for(y = tri.y3; y < tri.y1; y++){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine((int)currx2,(int)currx1, y),col);
		currx1 += invslope1;
		currx2 += invslope2;
	}
}
/*
=======================================================================================
	Function   : uGDLFillGouraudFlatTopTriangleOnCanvas
	Purpose    : Draws a gouraud shaded triangle with a flat top, a top with a horizontal line, to a canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col1 - The first color
				 col2 - The second color
				 col3 - The third color
	Returns	   : void
=======================================================================================
*/
void uGDLFillGouraudFlatTopTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3){
	float invslope1 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	float invslope2 = (tri.x3 - tri.x2)/(float)(tri.y3 - tri.y2);
	
	float currx1 = tri.x3;
	float currx2 = tri.x3;
	
	int x, y;
	for(y = tri.y3; y <= tri.y1; y++){
		for(x = currx1 + 1; x < currx2; x++){
			int interpcol1 = uGDLInterpColor(col2, col1, ((y - tri.y3)/(float)(tri.y2-tri.y3)),RGB_888);
        	int interpcol2 = uGDLInterpColor(col3, col1, ((y - tri.y3)/(float)(tri.y2-tri.y3)),RGB_888);
			float factor = ((currx1-x)/(float)(currx2-currx1));
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x,y),uGDLInterpColor(interpcol1,interpcol2,factor,RGB_888));
		}
		currx1 += invslope1;
		currx2 += invslope2;
	}
}
/*
=======================================================================================
	Function   : uGDLFillFlatBottomTriangleOnCanvas
	Purpose    : Draws a triangle with a flat bottom, a bottom, horizontal line, to the canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillFlatBottomTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col){
	float invslope1 = (tri.x2 - tri.x1)/(float)(tri.y2 - tri.y1);
	float invslope2 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	
	float currx1 = tri.x1;
	float currx2 = tri.x1;

	int y;
	for(y = tri.y1; y >= tri.y2; y--){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine((int)currx2,(int)currx1, y),col);
		currx1 -= invslope1;
		currx2 -= invslope2;
	}
}
/*
=======================================================================================
	Function   : uGDLFillGouraudFlatBottomTriangleOnCanvas
	Purpose    : Draws a gouraud shaded triangle with a flat bottom, a bottom with a horizontal line, to the window display
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col1 - The first color
				 col2 - The second color
				 col3 - The third color
	Returns	   : void
=======================================================================================
*/
void uGDLFillGouraudFlatBottomTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col1, int col2, int col3){
	float invslope1 = (tri.x2 - tri.x1)/(float)(tri.y2 - tri.y1);
	float invslope2 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	
	float currx1 = tri.x1;
	float currx2 = tri.x1;

	int x, y;
	for(y = tri.y1; y > tri.y2; y--){
		for(x = currx1 + 1; x < currx2; x++){
			int interpcol1 = uGDLInterpColor(col1, col2, ((y - tri.y1)/(float)(tri.y1-tri.y3)),RGB_888);
        	int interpcol2 = uGDLInterpColor(col1, col3, ((y - tri.y1)/(float)(tri.y1-tri.y3)),RGB_888);
			float factor = ((currx1-x)/(float)(currx2-currx1));
			uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x,y),uGDLInterpColor(interpcol1,interpcol2,factor,RGB_888));
		}
		currx1 -= invslope1;
		currx2 -= invslope2;
	}
}
/*
=======================================================================================
	Function   : uGDLFillFastTriangleOnCanvas
	Purpose    : Fills a quickly drawn triangle to the canvas
	Parameters : canvas - A reference to a canvas structure
				 tri - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillFastTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri,  int col){
	int x1 = tri.x1, x2 = tri.x2, x3 = tri.x3, y1 = tri.y1, y2 = tri.y2, y3 = tri.y3;
	
	if(y1 < y2){
		SWAP(&y1, &y2);
		SWAP(&x1, &x2);
	}
	
	if(y2 < y3){
		SWAP(&y2, &y3);
		SWAP(&x2, &x3);
	}
	
	if(y1 < y3){
		SWAP(&y1, &y3);
		SWAP(&x1, &x3);
	}
	
	if(y2 == y3){
		uGDLFillFlatBottomTriangleOnCanvas(canvas, tri, col);
	}
	
	else if(y1 == y2){
		uGDLFillFlatTopTriangleOnCanvas(canvas, tri, col);
	}
	else{
		int x4 =(int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
		int y4 = y2;
	//	printf("x1 = %d, x2 = %d, x3 = %d, x4 = %d\n",x1,x2,x3,x4);
	//	printf("y1 = %d, y2 = %d, y3 = %d, y4 = %d\n",y1,y2,y3,y4);
		uGDLFillFlatTopTriangleOnCanvas(canvas, uGDLCreateTriangle(x2,y2,x4,y4,x3,y3),col);
		uGDLFillFlatBottomTriangleOnCanvas(canvas, uGDLCreateTriangle(x1,y1,x2,y2,x4,y4),col);
	}
}
void uGDLFillFastGouraudTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri,  int col1, int col2, int col3){
	int x1 = tri.x1, x2 = tri.x2, x3 = tri.x3, y1 = tri.y1, y2 = tri.y2, y3 = tri.y3;
	
	if(y1 < y2){
		SWAP(&y1, &y2);
		SWAP(&x1, &x2);
	}
	
	if(y2 < y3){
		SWAP(&y2, &y3);
		SWAP(&x2, &x3);
	}
	
	if(y1 < y3){
		SWAP(&y1, &y3);
		SWAP(&x1, &x3);
	}
	
	if(y2 == y3){
		uGDLFillGouraudFlatBottomTriangleOnCanvas(canvas, tri, col1, col2, col3);
	}
	
	else if(y1 == y2){
		uGDLFillGouraudFlatTopTriangleOnCanvas(canvas, tri, col1, col2, col3);
	}
	else{
		int x4 =(int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
		int y4 = y2;
	//	printf("x1 = %d, x2 = %d, x3 = %d, x4 = %d\n",x1,x2,x3,x4);
	//	printf("y1 = %d, y2 = %d, y3 = %d, y4 = %d\n",y1,y2,y3,y4);
		uGDLFillGouraudFlatTopTriangleOnCanvas(canvas, uGDLCreateTriangle(x4,y4,x2,y2,x3,y3),col1,col2,col3);
		uGDLFillGouraudFlatBottomTriangleOnCanvas(canvas, uGDLCreateTriangle(x1,y1,x4,y4,x2,y2),col1,col2,col3);
	}
}
/*
=======================================================================================
	Function   : uGDLFillTriangleOnCanvas
	Purpose    : Fills a triangle drawn to the canvas
	Parameters : canvas - A reference to a canvas structure
				 t - A triangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle t, int col){
	int x1 = t.x1, x2 = t.x2, x3 = t.x3, y1 = t.y1, y2 = t.y2, y3 = t.y3;
	
	int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		int changed1 = FALSE;
		int changed2 = FALSE;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		// Sort vertices
		if (y1 > y2) { SWAP(&y1, &y2); SWAP(&x1, &x2); }
		if (y1 > y3) { SWAP(&y1, &y3); SWAP(&x1, &x3); }
		if (y2 > y3) { SWAP(&y2, &y3); SWAP(&x2, &x3); }

		t1x = t2x = x1; y = y1;   // Starting points
		dx1 = (int)(x2 - x1);
		if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1);
		if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) { SWAP(&dx1, &dy1); changed1 = TRUE; }
		if (dy2 > dx2) { SWAP(&dy2, &dx2); changed2 = TRUE; }

		e2 = (int)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);
		
		int i;
		for (i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			uGDLHorzLine horz = {minx, maxx, y};
			uGDLDrawHorzLineOnCanvas(canvas, horz, col);    // Draw line from min to max points found on the y
										// Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;
		}
	next:
		// Second half
		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(&dy1, &dx1);
			changed1 = TRUE;
		}
		else changed1 = FALSE;

		e1 = (int)(dx1 >> 1);
		
		for (i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			uGDLHorzLine horz2 = {minx, maxx, y};
			uGDLDrawHorzLineOnCanvas(canvas, horz2, col);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
}
/*
=======================================================================================
	Function   : uGDLFillRectOnCanvas
	Purpose    : Fills a rectangle drawn to the canvas
	Parameters : canvas - A reference to a canvas structure
				 rect - A rectangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col)
{
	int x = rect.x, maxx = rect.x + rect.width, maxy = rect.y + rect.height, y;
	for(y = rect.y; y < maxy; y++){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine(x, maxx, y), col);
	}
}
/*
=======================================================================================
	Function   : uGDLFillGouraudRectOnCanvas
	Purpose    : Fills a gouraud shaded rectangle drawn to a canvas
	Parameters : canvas - A reference to a canvas structure
				 rect - A rectangle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLFillGouraudRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col1, int col2, int col3, int col4)
{
	int x, y, x2 = rect.x + rect.width, y2 = rect.y + rect.height;
    for(y = rect.y; y < rect.y + rect.height; y++){
    	for(x = rect.x; x < rect.x + rect.width; x++){
        	int interpcol1 = uGDLInterpColor(col2, col1, (rect.y - y)/(float)(y2-rect.y),RGB_888);
        	int interpcol2 = uGDLInterpColor(col3, col4, (rect.y - y)/(float)(y2-rect.y),RGB_888);
        	
        	float factor = (rect.x-x)/(float)(x2-rect.x);
        	
        	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x,y),uGDLInterpColor(interpcol1,interpcol2,factor,RGB_888));
    	}
    }
}
/*
=======================================================================================
	Function   : uGDLDrawCircleOutlineOnCanvas
	Purpose    : Utility function used to draw the outline of a circle to the canvas
	Parameters : canvas - A reference to a canvas structure
				 x - The x - coordinate offset
				 y - The y - coordinate offset
				 xc - The center x - coordinate
				 yc - The center y - coordinate
				 col - The color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawCircleOutlineOnCanvas(uGDLCanvas *canvas, int x, int y, int xc, int yc, int col){
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc+x, yc+y), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc-x, yc+y), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc+x, yc-y), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc-x, yc-y), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc+y, yc+x), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc-y, yc+x), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc+y, yc-x), col);
	uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(xc-y, yc-x), col);
}
/*
=======================================================================================
	Function   : uGDLDrawCircleOnCanvas
	Purpose    : Draws a circle to the canvas
	Parameters : canvas - A reference to a canvas structure
				 circle - A circle structure
				 col - A color
	Returns	   : void
=======================================================================================
*/
void uGDLDrawCircleOnCanvas(uGDLCanvas *canvas, uGDLCircle circle, int col){
	int x = 0, y = circle.r;
    int d = 3 - 2 * circle.r;
    uGDLDrawCircleOutlineOnCanvas(canvas, x, y, circle.xc, circle.yc, col);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
         
        x++;
 
        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        uGDLDrawCircleOutlineOnCanvas(canvas, x, y, circle.xc, circle.yc, col);
    }
}
/*
=======================================================================================
	Function   : uGDLDrawPointOnCanvas
	Purpose    : Converts the entire canvas to a grayscale image
	Parameters : canvas - A reference to a canvas structure
	Returns	   : void
=======================================================================================
*/
void uGDLConvertCanvasToGrayscale(uGDLCanvas *canvas){
	int i;
	for(i = 0; i < canvas->width * canvas->height; i++){
		canvas->VRAM[i] = uGDLColToGrayscale(canvas->VRAM[i],canvas->cf);
	}
}
/*
=======================================================================================
	Function   : uGDLDispGeom
	Purpose    : Polymorphic function that displays any shape to the canvas with well-defined attributes for blending colors, anti-aliasing, and draw/fill conventions
	Parameters : canvas - A reference to a canvas structure
				 shape - Macro defined desired shape
				 geom - A union that contains any shape available in the uGDL
				 cycle - Defines whether or not use draw or fill shape - CYCLE_DRAW OR CYCLE_FILL
				 aa - Use or don't use anti-aliasing
				 blend - Type of color mixing
				 factor - The blending ratio of the two colors
				 col1 - The first color
				 col2 - The second color
				 cf - The color format, bit depth, of the colors
	Returns	   : void
=======================================================================================
*/
void uGDLDispGeomOnCanvas(uGDLCanvas *canvas, int shape, uGDLGeom geom, int cycle, int aa, int blend, float factor, int col1, int col2, ColorFormat cf){
	switch(shape){
		case SHAPE_POINT:{
			uGDLPoint2D p = geom.p;
			uGDLDrawPointOnCanvas(canvas, p, uGDLBlendColorMode(col1,col2,factor,cf,blend));
		}break;
		case SHAPE_RECT:{
			uGDLRect rect = geom.rect;
			if(cycle == CYCLE_DRAW){
				uGDLDrawRectOnCanvas(canvas, rect, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}else{
				uGDLFillRectOnCanvas(canvas, rect, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}
		}break;
		case SHAPE_VLINE:{
			uGDLVertLine vline = geom.vline;
			uGDLDrawVertLineOnCanvas(canvas, vline, uGDLBlendColorMode(col1,col2,factor,cf,blend));
		}break;
		case SHAPE_HLINE:{
			uGDLHorzLine hline = geom.hline;
			uGDLDrawHorzLineOnCanvas(canvas, hline, uGDLBlendColorMode(col1,col2,factor,cf,blend));
		}break;
		case SHAPE_LINE:{
			uGDLLine line = geom.line;
			if(aa == AA){
				uGDLDrawLineOnCanvas(canvas, line, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}else{
				uGDLDrawAALineOnCanvas(canvas, line, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}
		}break;
		case SHAPE_TRI:{
			uGDLTriangle tri = geom.tri;
			if(cycle == CYCLE_DRAW){
				if(aa == AA){
					uGDLDrawTriangleOnCanvas(canvas, tri, uGDLBlendColorMode(col1,col2,factor,cf,blend));
				}else{
					uGDLDrawAATriangleOnCanvas(canvas, tri, uGDLBlendColorMode(col1,col2,factor,cf,blend));
				}
			}else{
				uGDLFillTriangleOnCanvas(canvas, tri, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}
		}break;
		case SHAPE_CIRCLE:{
			uGDLCircle circle = geom.circle;
			if(cycle == CYCLE_DRAW){
				uGDLDrawCircleOnCanvas(canvas, circle, uGDLBlendColorMode(col1,col2,factor,cf,blend));
			}
			else{
				
			}
		}break;
	}
}
