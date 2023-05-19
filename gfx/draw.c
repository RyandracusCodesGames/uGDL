#include "draw.h"
#include "framebuffer.h"
#include "sprite.h"
#include "color.h"
#include <string.h>

uGDLScissor sciptr;

void SWAP(int* a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int uGDLGetScreenPixel(uint32_t *VRAM, int x, int y, int index, int flag){
	if(flag == SCREEN_POINT){
		if(x >= 0 && y >= 0 && x < sciptr.width && y < sciptr.width){
			return VRAM[x + (y + PLAYSTATION_H) * WIDTH];
		}
	}
	if(flag == SCREEN_INDEX){
		if(index <= (WIDTH - PLAYSTATION_W) * (HEIGHT - PLAYSTATION_H))
			return VRAM[index];
	}
}

void uGDLDrawPoint(uint32_t *VRAM, uGDLPoint2D p, int col){
    if(sciptr.scissor == 1){
		if(p.x >= sciptr.x && p.y >= sciptr.y && p.x < sciptr.width && p.y < sciptr.height){
			VRAM[p.x + p.y * WIDTH] = col;
		}
	}
	else{
		VRAM[p.x + p.y * WIDTH] = col;
	}
}

void uGDLFillScreen(uint32_t *VRAM, int col){
	int i;
	for(i = 0; i < WIDTH * HEIGHT; i++){
		VRAM[i] = col;
	}
}
void uGDLFadeScreen(uGDLSprite screen, uGDLSprite screen_buf, int col){
	uGDLBlendSpriteAndCol(screen, col, 0.00001f);
	if(uGDLAllPixelsSameColor(screen, col)){
		//uGDLBlendSprite(screen, screen_buf, 0.1f);
	}	
}

uGDLSprite uGDLScreenToSprite(uint32_t *VRAM){
	uGDLSprite spr;
	spr.width = WIDTH;
	spr.height = HEIGHT;
	int i;
	for(i = 0; i < WIDTH * HEIGHT; i++){
		spr.clut[i] = VRAM[i];
	}
	return spr;
}

void uGDLDrawVertLine(uint32_t *VRAM, uGDLVertLine v1, int col){
	if(v1.y2 < v1.y1){
		int y;
		for(y = v1.y2; y >= v1.y1; y--){
			uGDLDrawPoint(VRAM, uGDLCreatePoint(v1.x, y), col);
		}
	}
	else{
		int y;
		for(y = v1.y1; y <= v1.y2; y++){
			uGDLDrawPoint(VRAM, uGDLCreatePoint(v1.x, y), col);
		}
	}
}

void uGDLDrawHorzLine(uint32_t *VRAM, uGDLHorzLine hl, int col){
	if(hl.x1 > hl.x2){
		int x;
		for(x = hl.x1; x >= hl.x2; x--){
			uGDLDrawPoint(VRAM, uGDLCreatePoint(x, hl.y), col);
		}
	}
	else{
		int x;
		for(x = hl.x1; x <= hl.x2; x++){
			uGDLDrawPoint(VRAM, uGDLCreatePoint(x, hl.y), col);
		}
	}
}

void uGDLDrawLine(uint32_t *VRAM, uGDLLine line, int col){
	
	int x1 = line.x1, x2 = line.x2, y1 = line.y1, y2 = line.y2;
	int dx, dy, sx, sy, err, e2;
	
	if(x1 == x2){
		uGDLDrawVertLine(VRAM, uGDLCreateVertLine(x1, y1, y2), col);
		return;
	}
	
	if(y1 == y2){;
		uGDLDrawHorzLine(VRAM, uGDLCreateHorzLine(x1, x2, y1), col);
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
	
	do{
		uGDLDrawPoint(VRAM, uGDLCreatePoint(x1, y1), col);
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

void uGDLDrawTriangle(uint32_t *VRAM, uGDLTriangle tri, int col){
	
	uGDLLine line1 = {tri.x1, tri.y1, tri.x2, tri.y2};
	uGDLLine line2 = {tri.x2, tri.y2, tri.x3, tri.y3};
	uGDLLine line3 = {tri.x3, tri.y3, tri.x1, tri.y1};
	
	uGDLDrawLine(VRAM, line1, col);
	uGDLDrawLine(VRAM, line2, col);
	uGDLDrawLine(VRAM, line3, col);
}

void uGDLDrawPolygon(uint32_t *VRAM, uGDLPolygon p, int nx, int ny, int col){
	int ix, iy;
	for(iy = 0; iy < ny; iy+=2)
	{
		for(ix = 0; ix < nx; ix+=2)
		{
			uGDLLine l = {p.x[ix], p.y[iy], p.x[ix+1], p.y[iy+1]};
			
			uGDLDrawLine(VRAM, l, col);
		}
	}
}

void uGDLDrawRect(uint32_t* VRAM, uGDLRect rect, int col)
{
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
	
	uGDLDrawVertLine(VRAM, v1, col);
	uGDLDrawVertLine(VRAM, v2, col);
	uGDLDrawHorzLine(VRAM, h1, col);
	uGDLDrawHorzLine(VRAM, h2, col);
}

void uGDLDrawChar(uint32_t *VRAM, uGDLFont font, char s, int tX, int tY){
	uGDLSprite spr = uGDLFindFontCharacter(font, s);
	uGDLDispSprite(VRAM, spr, tX, tY, BLACK);
}

void uGDLDrawString(uint32_t *VRAM, uGDLFont font, char * s, int tX, int tY){
	int i;
	for(i = 0; i < strlen(s) + 1; i++){		
		if(s[i] == ' '){
			tX = tX + 8;			
		}
		else if(s[i] == 'I' || s[i] == '1'){
			tX = tX + 9;			
			uGDLSprite spr = uGDLFindFontCharacter(font, s[i]);
			uGDLDispSprite(VRAM, spr, tX, tY, BLACK);	
			tX = tX - 5;		
		}		
		else{
			tX = tX + 8;
		
			uGDLSprite spr = uGDLFindFontCharacter(font, s[i]);
			uGDLDispSprite(VRAM, spr, tX, tY, BLACK);			
		}		
	}
}

void uGDLFillFlatTopTriangle(uint32_t *VRAM, uGDLTriangle tri, int col){
	float invslope1 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	float invslope2 = (tri.x3 - tri.x2)/(float)(tri.y3 - tri.y2);
	
	float currx1 = tri.x3;
	float currx2 = tri.x3;
	
	int y;
	for(y = tri.y3; y < tri.y1; y++){
		uGDLDrawHorzLine(VRAM, uGDLCreateHorzLine((int)currx2,(int)currx1, y),col);
		currx1 += invslope1;
		currx2 += invslope2;
	}
}

void uGDLFillFlatBottomTriangle(uint32_t *VRAM, uGDLTriangle tri, int col){
	float invslope1 = (tri.x2 - tri.x1)/(float)(tri.y2 - tri.y1);
	float invslope2 = (tri.x3 - tri.x1)/(float)(tri.y3 - tri.y1);
	
	float currx1 = tri.x1;
	float currx2 = tri.x1;

	int y;
	for(y = tri.y1; y >= tri.y2; y--){
		uGDLDrawHorzLine(VRAM, uGDLCreateHorzLine((int)currx2,(int)currx1, y),col);
		currx1 -= invslope1;
		currx2 -= invslope2;
	}
}

void uGDLFillFastTriangle(uint32_t *VRAM, uGDLTriangle tri,  int col){
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
		uGDLFillFlatBottomTriangle(VRAM, tri, col);
	}
	
	else if(y1 == y2){
		uGDLFillFlatTopTriangle(VRAM, tri, col);
	}
	else{
		int x4 =(int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
		int y4 = y2;
	//	printf("x1 = %d, x2 = %d, x3 = %d, x4 = %d\n",x1,x2,x3,x4);
	//	printf("y1 = %d, y2 = %d, y3 = %d, y4 = %d\n",y1,y2,y3,y4);
		uGDLFillFlatTopTriangle(VRAM, uGDLCreateTriangle(x2,y2,x4,y4,x3,y3),col);
		uGDLFillFlatBottomTriangle(VRAM, uGDLCreateTriangle(x1,y1,x2,y2,x4,y4),col);
	}
}

void uGDLFillTriangle(uint32_t* VRAM, uGDLTriangle t, int col)
{
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
			uGDLDrawHorzLine(VRAM, horz, col);    // Draw line from min to max points found on the y
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
			uGDLDrawHorzLine(VRAM, horz2, col);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
}

void uGDLFillRect(uint32_t *VRAM, uGDLRect rect, int col)
{
	int x = rect.x, maxx = rect.x + rect.width, maxy = rect.y + rect.height, y;
	for(y = rect.y; y < maxy; y++){
		uGDLDrawHorzLine(VRAM, uGDLCreateHorzLine(x, maxx, y), col);
	}
}

void uGDLDrawCircleOutline(uint32_t *VRAM, int x, int y, int xc, int yc, int col){
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc+x, yc+y), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc-x, yc+y), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc+x, yc-y), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc-x, yc-y), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc+y, yc+x), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc-y, yc+x), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc+y, yc-x), col);
	uGDLDrawPoint(VRAM, uGDLCreatePoint(xc-y, yc-x), col);
}

void uGDLDrawCircle(uint32_t *VRAM, uGDLCircle circle, int col){
	int x = 0, y = circle.r;
    int d = 3 - 2 * circle.r;
    uGDLDrawCircleOutline(VRAM, x, y, circle.xc, circle.yc, col);
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
        uGDLDrawCircleOutline(VRAM, x, y, circle.xc, circle.yc, col);
    }
}
/*Be careful about choice of color due to recursive nature of flood fill*/
void uGDLFloodFill(uint32_t* VRAM, int x, int y, int col){
	if(uGDLGetScreenPixel(VRAM,x,y,0,1) == col){
		uGDLDrawPoint(VRAM, uGDLCreatePoint(x,y),col);
		uGDLFloodFill(VRAM, x + 1, y, col);
		uGDLFloodFill(VRAM, x - 1, y, col);
		uGDLFloodFill(VRAM, x, y + 1, col);
		uGDLFloodFill(VRAM, x, y - 1, col);
	}
}
