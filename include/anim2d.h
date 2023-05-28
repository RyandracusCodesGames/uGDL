#ifndef ANIM2D_H
#define ANIM2D_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : anim2d.h
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

#include "sprite.h"
#include "bmp_img.h"
#include "font.h"
#include "draw.h"
#include "framebuffer.h"
#include "color.h"

#include <stdbool.h>

typedef struct{
	int num_of_frames;
	float curr_frame;
	bool finished;
	char * directory;
	char * name;
	char * extension;
	int width, height;
	float scalex, scaley;
}uGDLAnim2D;

void uGDLInitAnimation(uGDLAnim2D *anim, int num_of_frames, int width, int height, float curr_frame, char *directory, char *name, char *extension);
void uGDLSetAnimationScale(uGDLAnim2D *anim, float scalex, float scaley);
void uGDLPlayAnimation(uint32_t *VRAM, uGDLAnim2D *anim);
void uGDLUnpauseAnimation(uGDLAnim2D *anim);
void uGDLStopAnimation(uGDLAnim2D *anim);
char* AppendStrings(const char *A, const char*B);
#endif
