#ifndef TILE_PRIORITY
#define TILE_PRIORITY

#include <stdint.h>
#include "tile.h"

typedef struct{
	uGDLTilemap *tilemap;
	int priority;
	struct BST_NODE *left, *right;
}BST_NODE;

/*Global node pointer that holds all the layers to be rendered to the display*/

BST_NODE * uGDLNewNode(uGDLTilemap *map, int priority);
BST_NODE * uGDLInsertNode(BST_NODE *root, uGDLTilemap *map, int priority);
void uGDLRenderTilemapLayers(uint32_t *VRAM, BST_NODE *root);
BST_NODE * uGDLMinNode(BST_NODE *root);
BST_NODE * uGDLMaxNode(BST_NODE *root);
BST_NODE * uGDLDeleteNode(BST_NODE *root, uGDLTilemap *map, int priority);
BST_NODE * uGDLSwapNode(BST_NODE *root, int oldPriority, int newPriority, uGDLTilemap *map);
BST_NODE * uGDLSearchNode(BST_NODE *root, int priority);
BST_NODE * uGDLFreeTree(BST_NODE *root);
#endif
