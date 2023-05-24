#include "tile_priority.h"
#include <stddef.h>
#include <stdlib.h>

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : tile_priority.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

BST_NODE * uGDLNewNode(uGDLTilemap *map, int priority){
	BST_NODE * root = (BST_NODE*)malloc(sizeof(BST_NODE));
	root->tilemap = map;
	root->priority = priority;
	root->left = root->right = NULL;
	return root;
}

BST_NODE * uGDLInsertNode(BST_NODE *root, uGDLTilemap *map, int priority){
	if(root == NULL){
		return uGDLNewNode(map, priority);
	}
	
	if(priority < root->priority){
		root->left = uGDLInsertNode(root->left, map, priority);
	}
	
	if(priority > root->priority){
		root->right =  uGDLInsertNode(root->right, map, priority);
	}
	
	return root;
}

BST_NODE * uGDLMinNode(BST_NODE *root){
	BST_NODE *current = root;
	while(current->left != NULL){
		current = current->left;
	}
	return current;
}
BST_NODE * uGDLMaxNode(BST_NODE *root){
	BST_NODE *current = root;
	while(current->right != NULL){
		current = current->right;
	}
	return current;
}

BST_NODE * uGDLDeleteNode(BST_NODE *root, uGDLTilemap *map, int priority){
	if(root == NULL){
		return root;
	}
	
	if(priority < root->priority){
		root->left = uGDLDeleteNode(root->left, map, priority);
	}

	else if(priority > root->right){
		root->right = uGDLDeleteNode(root->right, map, priority);
	}
	
	else{
		if (root->left == NULL)
        {
            BST_NODE *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BST_NODE *temp = root->left;
            free(root);
            return temp;
        }
 
        BST_NODE *temp = uGDLMinNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->priority = temp->priority;
 
        // Delete the inorder successor
        root->right = uGDLDeleteNode(root->right, temp->tilemap, temp->priority);
	}
	return root;
}

BST_NODE * uGDLSwapNode(BST_NODE *root, int oldPriority, int newPriority, uGDLTilemap *map)
{
    //  First delete old key value
    root = uGDLDeleteNode(root, map, oldPriority);
 
    // Then insert new key value
    root = uGDLInsertNode(root, map, newPriority);
 
    // Return new root
    return root;
}

void uGDLRenderTilemapLayers(uint32_t *VRAM, BST_NODE *root)
{
    if (root != NULL)
    {
        uGDLRenderTilemapLayers(VRAM, root->right);
        /*Perform Post-Order Rasterization of the Scene*/
        uGDLDispTilemap(VRAM, root->tilemap);
        uGDLRenderTilemapLayers(VRAM, root->left);
    }
}

void uGDLRenderTilemapLayersOnCanvas(uGDLCanvas *canvas, BST_NODE *root)
{
    if (root != NULL)
    {
        uGDLRenderTilemapLayersOnCanvas(canvas, root->right);
        /*Perform Post-Order Rasterization of the Scene*/
        uGDLDispTilemapOnCanvas(canvas, root->tilemap);
        uGDLRenderTilemapLayersOnCanvas(canvas, root->left);
    }
}

BST_NODE * uGDLSearchNode(BST_NODE *root, int priority){
	if(root == NULL){
		return;
	}
	
	free(root->left);
	free(root->right);
}

