#ifndef TILE_H
#define TILE_H

#include <stdint.h>

#define W 16
#define H 16
#define MAX_X 20
#define MAX_Y 15

#define G_FLIP_HORZ 0x0810
#define G_FLIP_VERT 0x0911
#define G_FLIP_HORZ_AND_VERT 0x7212
#define G_MIRROR 0x00172

extern int gTileNum;

typedef struct{
	float y;
}uGDLHorzScroll;

typedef struct{
	float x;
}uGDLVertScroll;

typedef struct{
	int x, y, transx, transy;
	int* tlut;
}uGDLTile;

typedef struct{
	int index;
	uGDLVertScroll vscroll;
	uGDLHorzScroll hscroll;
	uGDLTile map[MAX_X * MAX_Y];
}uGDLTilemap;

int uGDLGetTileTexel(uGDLTile tile, int x, int y);
void uGDLSetTileTexel(uGDLTile *tile, int x, int y, int col);
uGDLTile uGDLLoadTile(char * name, int x, int y);
void uGDLDispTile(uint32_t *VRAM, uGDLTile tile, int tX, int tY);
void uGDLBeginTileList(uGDLTilemap *map);
void uGDLEndTileList(uGDLTilemap *map);
void uGDLInitTilemap(uGDLTilemap *map);
void uGDLAddTile(int gTileNum, uGDLTilemap *map, uGDLTile tile);
void uGDLDispTilemap(uint32_t *VRAM, uGDLTilemap *map);
void uGDLFreeTile(uGDLTile *tile);

#endif
