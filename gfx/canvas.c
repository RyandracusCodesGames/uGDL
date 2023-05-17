#include <stdlib.h>
#include "canvas.h"
#include "draw.h"

uGDLCanvas uGDLCreateCanvas(int x, int y, int width, int height, ColorFormat cf){
	uGDLCanvas canvas;
	canvas.x = x;
	canvas.y = y;
	canvas.width = width;
	canvas.height = height;
	canvas.VRAM = (uint32_t*)malloc(sizeof(uint32_t)*(width*height));
	return canvas;
}

int uGDLGetCanvasPixel(uGDLCanvas *canvas, int x, int y){
	if(x >= 0 && y >= 0 && x < canvas->width && y < canvas->height){
		return canvas->VRAM[x + y * canvas->width];
	}
}

void uGDLFreeCanvas(uGDLCanvas *canvas){
	free(canvas->VRAM);
}

void uGDLDispCanvas(uGDLCanvas canvas, FrameBuffer *buf){
	int x, y;
	for(y = 0; y < canvas.height; y++){
		for(x = 0; x < canvas.width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x, y + canvas.y), uGDLGetCanvasPixel(&canvas, x, y));
		}
	}
}

void uGDLFlipCanvasVert(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas.height; y++){
		for(x = 0; x < canvas.width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x + tX, y + canvas.y + tY), uGDLGetCanvasPixel(&canvas, x, canvas.height - y));
		}
	}
}

void uGDLFlipCanvasHorz(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas.height; y++){
		for(x = 0; x < canvas.width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x + tX, y + canvas.y + tY), uGDLGetCanvasPixel(&canvas, canvas.width - x, y));
		}
	}
}

void uGDLFlipCanvasHorzAndVert(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas.height; y++){
		for(x = 0; x < canvas.width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x + tX, y + canvas.y + tY), uGDLGetCanvasPixel(&canvas, canvas.width - x, canvas.height - y));
		}
	}
}

void uGDLDispTranslatedCanvas(uGDLCanvas canvas, FrameBuffer *buf, int tX, int tY){
	int x, y;
	for(y = 0; y < canvas.height; y++){
		for(x = 0; x < canvas.width; x++){
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x + tX, y + canvas.y + tY), uGDLGetCanvasPixel(&canvas, x, y));
		}
	}
}

void uGDLDispScaledCanvas(uGDLCanvas canvas, FrameBuffer *buf, float sX, float sY){
	int w1 = canvas.width, w2 = (int)(canvas.width * sX);
	int h1 = canvas.height, h2 = (int)(canvas.height * sY);
	
	int x_factor = (int)((w1<<16)/ w2) + 1;
	int y_factor = (int)((h1<<16)/ h2) + 1;
	
	int x, y, x2, y2;
	for(y = 0; y < h2; y++){
		for(x = 0; x < w2; x++){
			x2 = ((x*x_factor)>>16);
			y2 = ((y*y_factor)>>16);
			uGDLDrawPoint(buf->VRAM, uGDLCreatePoint(x + canvas.x,y + canvas.y),uGDLGetCanvasPixel(&canvas, x2, y2));
		}
	}
}

void uGDLDrawPointOnCanvas(uGDLCanvas *canvas, uGDLPoint2D p, int col){
	if(p.x >= 0 && p.y >= 0 && p.x < canvas->width && p.y < canvas->height){
		canvas->VRAM[p.x + p.y * canvas->width] = col;
	}
}

void uGDLClearCanvas(uGDLCanvas *canvas, int col){
	int i;
	for(i = 0; i < canvas->width * canvas->height; i++){
		canvas->VRAM[i] = col;
	}
}

void uGDLDrawVertLineOnCanvas(uGDLCanvas *canvas, uGDLVertLine vline, int col){
	int y;
	for(y = vline.y1; y <= vline.y2; y++){
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(vline.x, y), col);
	}
}

void uGDLDrawHorzLineOnCanvas(uGDLCanvas *canvas, uGDLHorzLine hline, int col){
	int x;
	for(x = hline.x1; x <= hline.x2; x++){
		uGDLDrawPointOnCanvas(canvas, uGDLCreatePoint(x, hline.y), col);
	}
}

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

void uGDLDrawTriangleOnCanvas(uGDLCanvas *canvas, uGDLTriangle tri, int col){
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x1, tri.y1, tri.x2, tri.y2), col);
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x2, tri.y2, tri.x3, tri.y3), col);
	uGDLDrawLineOnCanvas(canvas, uGDLCreateLine(tri.x3, tri.y3, tri.x1, tri.y1), col);
}

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

void uGDLFillRectOnCanvas(uGDLCanvas *canvas, uGDLRect rect, int col)
{
	int x = rect.x, maxx = rect.x + rect.width, maxy = rect.y + rect.height, y;
	for(y = rect.y; y < maxy; y++){
		uGDLDrawHorzLineOnCanvas(canvas, uGDLCreateHorzLine(x, maxx, y), col);
	}
}

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
