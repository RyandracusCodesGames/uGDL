#ifndef TILE_H
#define TILE_H

#include <stdint.h>
#include "framebuffer.h"
#include "canvas.h"

#define W 16
#define H 16
#define MAX_X 20
#define MAX_Y 15

/*Macros will determine if individual tile will be flipped horizontally, vertically, or both*/
#define G_FLIP_HORZ 0x0810
#define G_FLIP_VERT 0x0911
#define G_MIRROR 0x00172
/*Macros will determine rendering priority of tilemaps*/
#define PRIOR_F 1
#define PRIOR_B1 4
#define PRIOR_B2 8
#define PRIOR_B3 12

/*Global variable to hold size of tilemap while adding tiles in a display list*/
extern int gTileNum;

typedef struct{
	float y;
}uGDLHorzScroll;

typedef struct{
	float x;
}uGDLVertScroll;

typedef struct{
	int x, y, transx, transy;
	int attribute;
	int* tlut;
}uGDLTile;

typedef struct{
	int index;
	uGDLVertScroll vscroll;
	uGDLHorzScroll hscroll;
	int priority;
	int erase;
	uGDLTile map[MAX_X * MAX_Y];
}uGDLTilemap;

int uGDLGetTileTexel(uGDLTile tile, int x, int y);
void uGDLSetTileTexel(uGDLTile *tile, int x, int y, int col);
uGDLTile uGDLLoadTile(char * name, int x, int y, int attr);
void uGDLSetTileAttribute(uGDLTile *tile, int attr);
void uGDLDispTile(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispGrayscaleTile(uint32_t *VRAM, uGDLTile tile, int tX, int tY);
void uGDLDispGrayscaleTileOnCanvas(uGDLCanvas *canvas, uGDLTile tile, int tX, int tY);
void uGDLDispTileVert(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileHorz(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileHorzAndVert(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileOnCanvas(uGDLCanvas *canvas, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileVertOnCanvas(uGDLCanvas *canvas, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileHorzOnCanvas(uGDLCanvas *canvas, uGDLTile tile, int tX, int tY, int erase);
void uGDLDispTileHorzAndVertOnCanvas(uGDLCanvas *canvas, uGDLTile tile, int tX, int tY, int erase);
void uGDLBeginTileList(uGDLTilemap *map);
void uGDLEndTileList(uGDLTilemap *map);
void uGDLSetVertScroll(uGDLTilemap *map, float vscroll);
void uGDLSetHorzScroll(uGDLTilemap *map, float hscroll);
void uGDLInitTilemap(uGDLTilemap *map, int priority);
void uGDLLoadBackgroundLayer(uGDLTilemap *map, char * name, int width, int height, ColorFormat cf);
void uGDLAddTile(int gTileNum, uGDLTilemap *map, uGDLTile tile);
void uGDLDispTilemap(uint32_t *VRAM, uGDLTilemap *map);
void uGDLDispTilemapOnCanvas(uGDLCanvas *canvas, uGDLTilemap *map);
void uGDLDispTileset(uint32_t *VRAM);
void uGDLDispTilesetOnCanvas(uGDLCanvas *canvas);
void uGDLSwapTile(uGDLTilemap *map, uGDLTile tile, int index);
void uGDLSetPlaneEraser(uGDLTilemap *map, int erase);
int* uGDLGetTileTLUT(uGDLTilemap *map, int index);
void uGDLRemoveTile(uGDLTilemap *map, int index);
void uGDLFreeTile(uGDLTile *tile);

#endif
