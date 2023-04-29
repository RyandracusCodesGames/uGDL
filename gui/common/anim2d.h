#ifndef ANIM2D_H
#define ANIM2D_H

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
}uGDLAnim2D;

void uGDLInitAnimation(uGDLAnim2D *anim, int num_of_frames, float curr_frame, char *directory, char *name, char *extension);
void uGDLPlayAnimation(uint32_t *VRAM, uGDLAnim2D *anim);
void uGDLPauseAnimation(uGDLAnim2D *anim);
void uGDLStopAnimation(uGDLAnim2D *anim);
char* AppendStrings(const char *A, const char*B);
#endif
