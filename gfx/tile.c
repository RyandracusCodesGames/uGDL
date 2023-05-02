#include "tile.h"
#include "bmp_img.h"
#include "geometry.h"
#include "color.h"
#include "draw.h"

uGDLTile uGDLLoadTile(char * name, int x, int y){
	uGDLTile tile;
	tile.x = x;
	tile.y = y;
	tile.transx = 0;
	tile.transy = 0;
	tile.tlut = uGDLLoadCLUT(name, RGB_888, W, H);
	return tile;
}

int uGDLGetTileTexel(uGDLTile tile, int x, int y){
	if(x >= 0 && y >= 0 && x < W && y < W){
		return tile.tlut[x + y * W];
	}
}

void uGDLSetTileTexel(uGDLTile *tile, int x, int y, int col){
	if(x >= 0 && y >= 0 && x < W && y < W){
		return;
	}
	
	tile->tlut[x + y * W] = col;
}


void uGDLDispTile(uint32_t *VRAM, uGDLTile tile, int tX, int tY){
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			if(uGDLGetTileTexel(tile, x, y) != uGDL_RGB888(4,20,83)){
				uGDLPoint2D p = {(x + tX) + (tile.x * W), (y + tY) + (tile.y * H)};
				uGDLDrawPoint(VRAM, p, uGDLGetTileTexel(tile, x, y));
			}
		}
	}
}

void uGDLBeginTileList(uGDLTilemap *map){
	map->index = 0;
}
void uGDLEndTileList(uGDLTilemap *map){
	map->index = map->index + gTileNum;
	gTileNum = 0;
}

void uGDLInitTilemap(uGDLTilemap *map){
    uGDLVertScroll vscroll = {0};
    uGDLHorzScroll hscroll = {0};
    
    map->vscroll = vscroll;
    map->hscroll = hscroll;
}

void uGDLAddTile(int gTileNum, uGDLTilemap *map, uGDLTile tile){
	map->map[gTileNum] = tile;
}

void uGDLDispTilemap(uint32_t *VRAM, uGDLTilemap *map){
	int i = 0;
	for(i = 0; i < map->index; i++){
		if((map->map[i].x * W)+ map->map[i].transx + map->vscroll.x >= 306){
		//	printf("OUT OF BOUNDS AT (%d,%d)\n",map->map[i].x, map->map[i].y);
			map->map[i].transx -= 320;
		}
		if((map->map[i].x * W)+ map->map[i].transx + map->vscroll.x <= -16){
			//printf("OUT OF BOUNDS AT (%d,%d)\n",map->map[i].x, map->map[i].y);
			map->map[i].transx += 320;
		}
		uGDLDispTile(VRAM, map->map[i], (int)(map->vscroll.x) + map->map[i].transx, (int)(map->hscroll.y) + map->map[i].transy);
	}
}

void uGDLFreeTile(uGDLTile *tile){
	if(tile == NULL){
		printf("TILE CANNOT BE FREED\n");
	}
	
	free(tile->tlut);
	tile =  NULL;
}

void uGDLFreeTilemap(uGDLTilemap *map){
	int i;
	for(i = 0; i < map->index; i++){
		uGDLFreeTile(&map->map[i]);
	}
}
