#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "common_gfx.h"

typedef enum uGDLMenu{
	MN_FOX_ANIM = 0,
	MN_ARGONAUT_ANIM = 1,
	MN_INTRO_ANIM = 2,
	MN_DARK_SCREEN = 3,
	MN_LOAD_SCREEN = 4,
	MN_MAIN_MENU = 5,
	MN_LOAD_GAME_MENU = 6,
	MN_OPTIONS_MENU = 7,
	MN_DISPLAY_MENU = 8,
	MN_SOUND_MENU = 9,
	MN_GAME_OPTIONS_MENU = 10,
}uGDLMenu;

void uGDLLoadMenu(uint32_t *VRAM, uGDLAnim2D *fox, uGDLAnim2D *argonaut, uGDLAnim2D *ar_intro, uGDLEvent event, uGDLFont font);

#endif
