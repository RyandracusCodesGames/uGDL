#include "geometry.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : geometry.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : uGDLCreatePoint
	Purpose    : Takes the given x and y screen coordinates and returns a point struct
	Parameters : x - The x - screen coordinate
				 y - The y - screen coordinate
	Returns	   : A uGDLPoint2D structure.
=======================================================================================
*/
uGDLPoint2D uGDLCreatePoint(int x, int y){
	uGDLPoint2D point = {x, y};
	return point;
}

/*
======================================================================================
	Function   : uGDLCreateRect
	Purpose    : Takes the given x and y coordinates as screen coordinate offsets that returns a rectangle
				 with the given width and height as its dimensions
	Parameters : x - The x - screen coordinate offset
				 y - The y - screen coordinate offset
				 width - the width of the rectangle;
				 height - the height of the rectangle;
	Returns	   : A uGDLRect structure.
=======================================================================================
*/
uGDLRect uGDLCreateRect(int x, int y, int width, int height){
	uGDLRect rect = {x, y, width, height};
	return rect;
}

/*
=======================================================================================
	Function   : uGDLCreateHorzLine
	Purpose    : Takes the two given x - coordinates and the y - coordinate to form a horizontal line
				 between the two x - coordinates
	Parameters : x1 - The first x - screen coordinate
				 x2 - The second x - screen coordinate
				 y - The y - screen coordinate
	Returns	   : A uGDLHorzLine structure.
=======================================================================================
*/
uGDLHorzLine uGDLCreateHorzLine(int x1, int x2, int y){
	uGDLHorzLine hline = {x1, x2, y};
	return hline;
}
/*
=======================================================================================
	Function   : uGDLCreateVertLine
	Purpose    : Takes two given y - coordinates and the x - coordinate to form a vertical line
				 between the two y - coordinates
	Parameters : x - The x - screen coordinate
				 y1 - The first y - screen coordinate
				 y2 - The second y - screen coordinate
	Returns	   : A uGDLVertLine structure.
=======================================================================================
*/
uGDLVertLine uGDLCreateVertLine(int x, int y1, int y2){
	uGDLVertLine vline = {x, y1, y2};
	return vline;
}
/*
=======================================================================================
	Function   : uGDLCreateLine
	Purpose    : Takes the given x and y screen coordinates and forms a line between the two points
	Parameters : x1 - The first x - screen coordinate
				 y1 - The first y - screen coordinate
				 x2 - The second x - screen coordinate
				 y2 - The second y - screen coordinate
	Returns	   : A uGDLLine structure.
=======================================================================================
*/
uGDLLine uGDLCreateLine(int x1, int y1, int x2, int y2){
	uGDLLine line = {x1, y1, x2, y2};
	return line;
}
/*
=======================================================================================
	Function   : uGDLCreateTriangle
	Purpose    : Takes the given x and y screen coordinates and forms a connected triangle with the three points
	Parameters : x1 - The first x - screen coordinate
				 y1 - The first y - screen coordinate
				 x2 - The second x - screen coordinate
				 y2 - The second y - screen coordinate
				 x3 - The third x -screen coordinate
				 y3 - The third y - screen coordinate
	Returns	   : A uGDLTriangle structure.
=======================================================================================
*/
uGDLTriangle uGDLCreateTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
	uGDLTriangle tri = {x1, y1, x2, y2, x3, y3};
	return tri;
}
/*
=======================================================================================
	Function   : uGDLCreatePolygon
	Purpose    : Takes the given x and y screen coordinates and forms a convex polygon
	Parameters : x - The x - screen coordinates
				 y - The y - screen coordinates
	Returns	   : A uGDLPolygon structure.
=======================================================================================
*/
uGDLPolygon uGDLCreatePolygon(int x[MAX_LINES], int y[MAX_LINES]){
	uGDLPolygon poly = {x, y};
	return poly;
}
/*
=======================================================================================
	Function   : uGDLCreateCircle
	Purpose    : Takes the given x and y center points and the radius to form a circle.
	Parameters : xc - The x - screen coordinate center
				 yc - The y - screen coordinate center
				 r - The radius of the circle
	Returns	   : A uGDLCircle structure.
=======================================================================================
*/
uGDLCircle uGDLCreateCircle(int xc, int yc, int r){
	uGDLCircle circle = {xc, yc, r};
	return circle;
}
