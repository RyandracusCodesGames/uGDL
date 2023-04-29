#include "anim2d.h"
#include <string.h>

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

void uGDLInitAnimation(uGDLAnim2D *anim, int num_of_frames, float curr_frame, char * directory, char * name, char * extension){
	anim->num_of_frames = num_of_frames;
	anim->curr_frame = curr_frame;
	anim->finished = false;
	anim->directory = directory;
	anim->name = name;
	anim->extension = extension;
}

void uGDLPlayAnimation(uint32_t *VRAM, uGDLAnim2D *anim){
	anim->curr_frame = anim->curr_frame + 0.35f;
	if(anim->curr_frame >= anim->num_of_frames){
		anim->curr_frame = 1;
		anim->finished = true;
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
	uGDLDispAnim(VRAM, spr, 0, 0, uGDL_RGB888(100, 214, 21));	
	uGDLFreeSprite(&spr);
}