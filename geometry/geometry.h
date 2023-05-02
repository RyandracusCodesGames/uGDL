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

#define uGDL_LINE_STRIPS
#define uGDL_LINES

typedef struct{
	int type;
	int x[MAX_LINES], y[MAX_LINES];
}uGDLPolygon;

typedef struct{
	
}uGDLCircle;

#endif
