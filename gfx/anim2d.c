#include "anim2d.h"
#include <string.h>

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : anim2d.c
	Author  : Ryandracus Chapamn
	Date 	: 5/23/2023
	Version : 1.0
	
*************************************************************************/

/*
=======================================================================================
	Function   : AppendStrings
	Purpose    : Takes the given char arrays A and B and concatenates them to a resulting string C
	Parameters : *A - The beginning appendage of the resulting concatenated string
				 *B - The ending appendage of the resulting concatenated string
	Returns	   : A char pointer.
=======================================================================================
*/
char* AppendStrings(const char *A, const char*B)
{
	int lenA = strlen(A);
	int lenB = strlen(B);
	char *C = (char*) malloc(lenA + lenB + 1);
	memcpy(C, A, lenA);
	memcpy(C + lenA, B, lenB);
	C[lenA + lenB] = '\0';    
	return C;
}
/*
=======================================================================================
	Function   : uGDLInitAnimation
	Purpose    : Initializes the core components of an animation structure to faciliate video playback/keyframe animation
	Parameters : anim - A reference to a 2D-Animation structure
				 num_of_frames - The total number of frames in the animation
				 curr_frame - The starting frame of the animation
				 directory - The local directory folder containing the animation
				 name - The name of the animations, ex: scene1.bmp and scene2.bmp -> scene
				 extension - The image file extension, currently only bmp files supported by the uGDL
	Returns	   : A uGDLAnim2D structure.
=======================================================================================
*/
void uGDLInitAnimation(uGDLAnim2D *anim, int num_of_frames, float curr_frame, char * directory, char * name, char * extension){
	anim->num_of_frames = num_of_frames;
	anim->curr_frame = curr_frame;
	anim->finished = false;
	anim->directory = directory;
	anim->name = name;
	anim->extension = extension;
	anim->scale = 1;
}
/*
=======================================================================================
	Function   : uGDLPlayAnimation
	Purpose    : Iterates through the individual keyframe animations of a video
	Parameters : VRAM - The virtual memory of the screen to be written to
				 anim - A reference to a 2D-Animation structure
	Returns	   : void
=======================================================================================
*/
void uGDLPlayAnimation(uint32_t *VRAM, uGDLAnim2D *anim){
	if(!anim->finished){
		anim->curr_frame = anim->curr_frame + 0.75f;
		if(anim->curr_frame >= anim->num_of_frames){
			anim->curr_frame = 1;
			uGDLStopAnimation(anim);
		}
		int frame = (int)(anim->curr_frame);
		char* dir_and_name = AppendStrings(anim->directory, anim->name);
		char* nombre = (char*)malloc(sizeof(char)*5);
		itoa(frame,nombre,10);
		char* append = AppendStrings(dir_and_name,nombre);
		char* extend = AppendStrings(append, anim->extension);
	//	printf("%s\n",extend);
		uGDLSprite spr;
		uGDLLoadSprite(extend, RGB_888, &spr, 310, 219);
		uGDLScaleSprite(VRAM, spr, 0, 0, anim->scale, anim->scale);	
		uGDLFreeSprite(&spr);
	}
}
/*
=======================================================================================
	Function   : uGDLSetAnimationScale
	Purpose    : Apples a scaling factor to an animation
	Parameters : anim - A reference to a 2D-Animation structure
				 scale - The scaling factor
	Returns	   : void
=======================================================================================
*/
void uGDLSetAnimationScale(uGDLAnim2D *anim, float scale){
	anim->scale = scale;
}
/*
=======================================================================================
	Function   : uGDLStopAnimation
	Purpose    : Terminates the processing of an animation
	Parameters : anim - A reference to a 2D-Animation structure
	Returns	   : void
=======================================================================================
*/
void uGDLStopAnimation(uGDLAnim2D *anim){
	anim->finished = true;
}
/*
=======================================================================================
	Function   : uGDLUnpauseAnimation
	Purpose    : Unpauses an animation to continue cycling through its frames
	Parameters : anim - A reference to a 2D-Animation structure
	Returns	   : void
=======================================================================================
*/
void uGDLUnpauseAnimation(uGDLAnim2D *anim){
	anim->finished = false;
}
