#include "tile.h"
#include "bmp_img.h"
#include "geometry.h"
#include "color.h"
#include "draw.h"
#include "tile_priority.h"

/*Counter variable to limit the amount of background layers being added*/
int count = 0;
/*Local pointer to root of the BST-based priority queue for background layers*/
BST_NODE *root = NULL;

uGDLTile uGDLLoadTile(char * name, int x, int y, int attr){
	uGDLTile tile;
	tile.x = x;
	tile.y = y;
	tile.transx = 0;
	tile.transy = 0;
	tile.attribute = attr;
	tile.tlut = uGDLLoadCLUT(name, RGB_888, W, H);
	return tile;
}

void uGDLSetTileAttribute(uGDLTile *tile, int attr){
	tile->attribute = attr;
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

void uGDLBeginTileList(uGDLTilemap *map){
	count++;
	if(count > 4){
		printf("Maximum Background Layer is 4\n");
	}
	map->index = 0;
}
void uGDLEndTileList(uGDLTilemap *map){
	map->index = map->index + gTileNum;
	root = uGDLInsertNode(root, map, map->priority);
	gTileNum = 0;
}

void uGDLSetVertScroll(uGDLTilemap *map, float vscroll){
	map->vscroll.x = map->vscroll.x + vscroll;
}

void uGDLSetHorzScroll(uGDLTilemap *map, float hscroll){
	map->hscroll.y = map->hscroll.y + hscroll;
}

void uGDLInitTilemap(uGDLTilemap *map, int priority){
    uGDLVertScroll vscroll = {0};
    uGDLHorzScroll hscroll = {0};
    map->priority = priority;
    map->erase = uGDL_RGB888(4,20,83);
    map->vscroll = vscroll;
    map->hscroll = hscroll;
}

void uGDLLoadBackgroundLayer(uGDLTilemap *map, char * name, int width, int height, ColorFormat cf){
	
	int* tlut = uGDLLoadCLUT(name, cf, width, height);
	
	uGDLBeginTileList(map);
	
	int currX, currY;
	for(currY = 0; currY <= height - H; currY += H){
		for(currX = 0; currX <= width - W; currX += W){
			int* tempCLUT = (int*)malloc(sizeof(int)*(W*H));
			int i, j;
			for(j = 0; j < H; j++){
				for(i = 0; i < W; i++){
					tempCLUT[i + j * W] = tlut[(currX + i) + (currY + j) * width];
				}
			}
			
			uGDLTile tile;
			tile.x = currX / 16;
			tile.y = currY / 16;
			tile.transx = 0;
			tile.transy = 0;
			tile.attribute = 0x0;
			tile.tlut = tempCLUT;
			uGDLAddTile(gTileNum++,map,tile);
		}
		
	}
	
	uGDLEndTileList(map);
	
}

void uGDLAddTile(int gTileNum, uGDLTilemap *map, uGDLTile tile){
	map->map[gTileNum] = tile;
}

void uGDLDispTile(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			if(uGDLGetTileTexel(tile, x, y) != erase){
				uGDLPoint2D p = {(x + tX) + (tile.x * W), (y + tY) + (tile.y * H)};
				uGDLDrawPoint(VRAM, p, uGDLGetTileTexel(tile, x, y));
			}
		}
	}
}

void uGDLDispTileVert(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			if(uGDLGetTileTexel(tile, x, H - y) != erase){
				uGDLPoint2D p = {(x + tX) + (tile.x * W), (y + tY) + (tile.y * H)};
				uGDLDrawPoint(VRAM, p, uGDLGetTileTexel(tile, x, H - y));
			}
		}
	}
}

void uGDLDispTileHorz(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 1; x < W; x++){
			if(uGDLGetTileTexel(tile, W - x, y) != erase){
				uGDLPoint2D p = {(x + tX) + (tile.x * W), (y + tY) + (tile.y * H)};
				uGDLDrawPoint(VRAM, p, uGDLGetTileTexel(tile, W - x, y));
			}
		}
	}
}

void uGDLDispTileHorzAndVert(uint32_t *VRAM, uGDLTile tile, int tX, int tY, int erase){
	int x, y;
	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			if(uGDLGetTileTexel(tile, x, y) != erase){
				uGDLPoint2D p = {(x + tX) + (tile.x * W), (y + tY) + (tile.y * H)};
				uGDLDrawPoint(VRAM, p, uGDLGetTileTexel(tile, W - x, H - y));
			}
		}
	}
}

void uGDLDispTilemap(uint32_t *VRAM, uGDLTilemap *map){
	int i = 0;
	for(i = 0; i < map->index; i++){
		if((map->map[i].x * W)+ map->map[i].transx + map->vscroll.x >= 322){
		//	printf("OUT OF BOUNDS AT (%d,%d)\n",map->map[i].x, map->map[i].y);
			map->map[i].transx -= 336;
		}
		if((map->map[i].x * W)+ map->map[i].transx + map->vscroll.x <= -26){
		//	printf("OUT OF BOUNDS AT (%d,%d)\n",map->map[i].x, map->map[i].y);
			map->map[i].transx += 336;
		}
		
		switch(map->map[i].attribute){
			case G_FLIP_HORZ:{
				uGDLDispTileHorz(VRAM, map->map[i], (int)(map->vscroll.x) + map->map[i].transx, (int)(map->hscroll.y) + map->map[i].transy, map->erase);
			}break;
			case G_FLIP_VERT:{
				uGDLDispTileVert(VRAM, map->map[i], (int)(map->vscroll.x) + map->map[i].transx, (int)(map->hscroll.y) + map->map[i].transy, map->erase);
			}break;
			case (G_FLIP_HORZ + G_FLIP_VERT):{
				uGDLDispTileHorzAndVert(VRAM, map->map[i], (int)(map->vscroll.x) + map->map[i].transx, (int)(map->hscroll.y) + map->map[i].transy, map->erase);
			}break;
			case G_MIRROR:{
				
			}break;
			default:{
				uGDLDispTile(VRAM, map->map[i], (int)(map->vscroll.x) + map->map[i].transx, (int)(map->hscroll.y) + map->map[i].transy, map->erase);
			}break;
		}
	}
}

void uGDLDispTileset(uint32_t *VRAM){
	uGDLRenderTilemapLayers(VRAM, root);
}

void uGDLSwapLayers(uGDLTilemap *a, uGDLTilemap *b){
	uGDLTilemap temp = *a;
	*a = *b;
	*b = temp;
}

int* uGDLGetTileTLUT(uGDLTilemap *map, int index){
	return map->map[index].tlut;
}

void uGDLRemoveTile(uGDLTilemap *map, int index){
	
	if(&map->map[index] == NULL){
		printf("Cannot remove tile that doesn't not exist in map array!\n");
		return;
	}
	
	int i;
	for(i = index; i < map->index - 1; i++){
		map->map[i] = map->map[i+1];
	}
	map->index = map->index - 1;
}

void uGDLSwapTile(uGDLTilemap *map, uGDLTile tile, int index){
	map->map[index].tlut = tile.tlut;
}

void uGDLSetPlaneEraser(uGDLTilemap *map, int erase){
	map->erase = erase;
}

void uGDLFreeTile(uGDLTile *tile){
	if(tile == NULL){
		printf("TILE CANNOT BE FREED\n");
		return;
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
