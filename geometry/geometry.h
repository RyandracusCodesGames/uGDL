#ifndef GEOMETRY_H
#define GEOMETRY_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : geometry.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

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

uGDLPoint2D uGDLCreatePoint(int x, int y);
uGDLRect uGDLCreateRect(int x, int y, int width, int height);
uGDLHorzLine uGDLCreateHorzLine(int x1, int x2, int y);
uGDLVertLine uGDLCreateVertLine(int x, int y1, int y2);
uGDLLine uGDLCreateLine(int x1, int y1, int x2, int y2);
uGDLTriangle uGDLCreateTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
uGDLPolygon uGDLCreatePolygon(int x[MAX_LINES], int y[MAX_LINES]);
uGDLCircle uGDLCreateCircle(int xc, int yc, int r);

#endif
