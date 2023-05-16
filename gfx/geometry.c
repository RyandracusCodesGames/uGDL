#include "geometry.h"

uGDLPoint2D uGDLCreatePoint(int x, int y){
	uGDLPoint2D point = {x, y};
	return point;
}

uGDLRect uGDLCreateRect(int x, int y, int width, int height){
	uGDLRect rect = {x, y, width, height};
	return rect;
}

uGDLHorzLine uGDLCreateHorzLine(int x1, int x2, int y){
	uGDLHorzLine hline = {x1, x2, y};
	return hline;
}

uGDLVertLine uGDLCreateVertLine(int x, int y1, int y2){
	uGDLVertLine vline = {x, y1, y2};
	return vline;
}

uGDLLine uGDLCreateLine(int x1, int y1, int x2, int y2){
	uGDLLine line = {x1, y1, x2, y2};
	return line;
}

uGDLTriangle uGDLCreateTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
	uGDLTriangle tri = {x1, y1, x2, y2, x3, y3};
	return tri;
}

uGDLPolygon uGDLCreatePolygon(int x[MAX_LINES], int y[MAX_LINES]){
	uGDLPolygon poly = {x, y};
	return poly;
}

uGDLCircle uGDLCreateCircle(int xc, int yc, int r){
	uGDLCircle circle = {xc, yc, r};
	return circle;
}
