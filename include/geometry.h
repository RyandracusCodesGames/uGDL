#ifndef GEOMETRY_H
#define GEOMETRY_H

#define MAX_LINES 30

typedef struct{
	int x, y;
}uGDLPoint2D;

typedef struct{
	int x, y, width, height;
}uGDLRect;

typedef struct{
	int x1, x2, y;
}uGDLHorzLine;

typedef struct{
	int x, y1, y2;
}uGDLVertLine;

typedef struct{
	int x1, y1, x2, y2;
}uGDLLine;

typedef struct{
	int x1, y1, x2, y2, x3, y3;
}uGDLTriangle;

typedef struct{
	int type;
	int x[MAX_LINES], y[MAX_LINES];
}uGDLPolygon;

typedef struct{
	int xc, yc, r;
}uGDLCircle;

typedef union{
	uGDLPoint2D p;
	uGDLRect rect;
	uGDLHorzLine hline;
	uGDLVertLine vline;
	uGDLLine line;
	uGDLTriangle tri;
	uGDLPolygon poly;
	uGDLCircle circle;
}uGDLGeom;

uGDLPoint2D uGDLCreatePoint(int x, int y);
uGDLRect uGDLCreateRect(int x, int y, int width, int height);
uGDLHorzLine uGDLCreateHorzLine(int x1, int x2, int y);
uGDLVertLine uGDLCreateVertLine(int x, int y1, int y2);
uGDLLine uGDLCreateLine(int x1, int y1, int x2, int y2);
uGDLTriangle uGDLCreateTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
uGDLPolygon uGDLCreatePolygon(int x[MAX_LINES], int y[MAX_LINES]);
uGDLCircle uGDLCreateCircle(int xc, int yc, int r);

#endif
