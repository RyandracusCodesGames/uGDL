#ifndef FONT_H
#define FONT_H

#include "sprite.h"

typedef struct{
	int width;
	int height;
	int col;
	char font[44];
	uGDLSprite spr[44];
}uGDLFont;

void uGDLInitFont(uGDLFont *font, int width, int height);
void uGDLSetFontColor(uGDLFont font, int col);
void uGDLAddSprite(uGDLFont *font, uGDLSprite spr, int index);
uGDLSprite uGDLFindFontCharacter(uGDLFont font, char s);
void uGDLFreeFont(uGDLFont font);

#endif
