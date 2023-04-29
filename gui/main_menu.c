#include "main_menu.h"

/*Locally defined variable used throughout the main menu functions*/
uGDLMenu menu = MN_FOX_ANIM;
int dark_count = 0;
/*Load Bar Is 210 Units Long*/
int max_bar = 105;
uGDLRect rect = {102, 69, 1, 2};
/*Counter variable to store input event changes*/
int menuSpriteCounter = 0, saveSpriteCounter = 0, optionSpriteCounter = 0, soundSpriteCounter = 0, subSoundCounter = 1, subSoundCounter2 = 8;
int gameSpriteCounter = 0, subDiffCounter = 1, subCrossCounter = 0, subHeadCounter = 0;

int random[256] = 
{0,0,3,0,2,3,1,1,3,3,2,2,1,2,1,2,
1,0,3,2,3,2,3,1,0,3,3,0,0,1,1,2,
2,1,1,2,3,3,0,3,3,0,3,2,3,1,1,0,
3,2,2,1,0,0,2,0,0,1,2,1,2,3,2,1,
2,0,2,0,0,1,0,3,0,1,0,0,3,3,3,2,
1,1,2,0,3,1,2,1,3,1,0,1,1,0,2,0,
1,2,0,2,2,3,1,3,2,0,3,0,1,1,1,3,
3,2,3,2,3,2,1,2,1,1,3,1,2,3,3,0,
1,3,3,2,2,1,1,2,3,3,2,0,3,1,2,1,
3,1,1,3,2,0,3,1,2,3,0,3,1,3,3,2,
1,1,3,2,1,1,0,3,3,0,1,1,0,3,2,0,
2,3,3,3,0,2,1,3,1,2,1,3,0,2,2,2,
0,2,2,2,3,3,2,0,2,3,3,1,1,3,3,1,
2,1,2,3,3,2,2,0,1,2,2,3,3,1,2,2,
3,0,3,2,1,0,3,0,0,2,2,2,2,2,2,2,
1,3,1,2,1,2,3,2,1,1,2,2,0,0,3,1,};

int r_index = 0;

int uGDLRandInt(){
	 r_index = (r_index+1)&0xff;
    return random[r_index];
}

void uGDLLoadFoxAnim(uint32_t *VRAM, uGDLAnim2D *fox){
	
	if(fox->finished == true){
		fox->finished = false;
		menu = MN_ARGONAUT_ANIM;
	}
	else{
		uGDLPlayAnimation(VRAM,fox);
	}
}

void uGDLLoadArgonautAnim(uint32_t *VRAM, uGDLAnim2D *argonaut){
	
	if(argonaut->finished == true){
		argonaut->finished = false;
		menu = MN_INTRO_ANIM;
	}
	else{
		uGDLPlayAnimation(VRAM,argonaut);
	}
}

void uGDLLoadIntroAnim(uint32_t *VRAM, uGDLAnim2D *intro, uGDLEvent event){
	
	if(event.A_Pressed || event.spacePressed){
		menu = MN_DARK_SCREEN;
	}
	
	if(intro->finished == true){
		intro->finished = false;
		menu = MN_DARK_SCREEN;
	}
	else{
		uGDLPlayAnimation(VRAM,intro);
	}
}

void uGDLLoadDarkScreen(uint32_t *VRAM){
	dark_count++;
	uGDLSprite dark;
	uGDLLoadSprite("gui/gui_images/dark.bmp", RGB_888, &dark, 310, 219);
	uGDLDispAnim(VRAM, dark, 0, 0, PURPLE);
	if(dark_count >= 248){
		menu = MN_LOAD_SCREEN;
		dark_count = 0;
	}
}

void uGDLLoadWaitScreen(uint32_t *VRAM){
	rect.width += uGDLRandInt();
	uGDLSprite spr;
	uGDLLoadSprite("gui/gui_images/load_data_screen.bmp", RGB_888, &spr, 310, 219);
	uGDLDispSprite(VRAM, spr, 0, 0, PURPLE);
	uGDLFreeSprite(&spr);
	uGDLFillRect(VRAM, rect, uGDL_RGB888(0,140,0));
	
	if(rect.width >= max_bar){
		rect.width = 0;
		menu = MN_MAIN_MENU;
	}
}

void uGDLDrawStringLocal(uint32_t *VRAM, uGDLFont font, char * s, int tX, int tY, int col, float factor){
	int i;
	for(i = 0; i < strlen(s) + 1; i++){		
		if(s[i] == ' '){
			tX = tX + 8;			
		}
		else if(s[i] == 'I' || s[i] == '1'){
			tX = tX + 9;			
			uGDLSprite spr = uGDLFindFontCharacter(font, s[i]);
			uGDLBlendSpriteAndColWithVRAM(VRAM, spr, tX, tY, col, factor);	
			tX = tX - 5;		
		}		
		else{
			tX = tX + 8;
		
			uGDLSprite spr = uGDLFindFontCharacter(font, s[i]);
			uGDLBlendSpriteAndColWithVRAM(VRAM, spr, tX, tY, col, factor);			
		}		
	}
}

void uGDLLoadMainMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	
	bool stateChanged = false;
	
	if(event.downPressed || event.sPressed){
		stateChanged = true;
		menuSpriteCounter++;
		
		if(menuSpriteCounter < 0){
			menuSpriteCounter = 2;
		}
		if(menuSpriteCounter > 2){
			menuSpriteCounter = 0;
		}
	}
	
	if(event.upPressed || event.wPressed){
		stateChanged = true;
		menuSpriteCounter--;
		
		if(menuSpriteCounter < 0){
			menuSpriteCounter = 2;
		}
		if(menuSpriteCounter > 2){
			menuSpriteCounter = 0;
		}
	}
	
	uGDLSprite spr, ar_logo, laser_beam, temp;
	uGDLLoadSprite("gui/gui_images/main_menu.bmp", RGB_888, &spr, 310, 219);
	uGDLLoadSprite("gui/gui_images/alien_menu.bmp", RGB_888, &ar_logo, 265, 45);
	uGDLLoadSprite("gui/gui_images/laser_beam.bmp", RGB_888, &laser_beam, 224, 10);
	uGDLLoadSprite("gui/gui_images/selection_stripe_1.bmp", RGB_888, &temp, 110, 5);
	uGDLDispSprite(VRAM, spr, 0, 0, PURPLE);
	uGDLDispSprite(VRAM, ar_logo, 20, 178, 0x0);
	uGDLDispSprite(VRAM, laser_beam, 40, 175, 0x0);
	
	if(menuSpriteCounter == 0){
		uGDLDispSprite(VRAM, temp, 92, 110, 0x0);
	}
	else if(menuSpriteCounter == 1){
		uGDLDispSprite(VRAM, temp, 92, 98, 0x0);
		
		if(event.A_Pressed || event.spacePressed){
			stateChanged = true;
			menu = MN_LOAD_GAME_MENU;
		}
	}
	else{
		uGDLDispSprite(VRAM, temp, 92, 86, 0x0);
		
		if(event.A_Pressed || event.spacePressed){
			stateChanged = true;
			menu = MN_OPTIONS_MENU;
		}
	}
	
	uGDLDrawString(VRAM, font, "NEW GAME", 108, 108);
	uGDLDrawString(VRAM, font, "LOAD GAME", 103, 96);
	uGDLDrawString(VRAM, font, "OPTIONS", 112, 84);
	
	uGDLDrawChar(VRAM, font, 'R', 45, 175); uGDLDrawChar(VRAM, font, 'E', 63, 175); uGDLDrawChar(VRAM, font, 'S', 83, 175);
	uGDLDrawChar(VRAM, font, 'U', 103, 175); uGDLDrawChar(VRAM, font, 'R', 123, 175); uGDLDrawChar(VRAM, font, 'R', 143, 175);
	uGDLDrawChar(VRAM, font, 'E', 163, 175); uGDLDrawChar(VRAM, font, 'C', 181, 175); uGDLDrawChar(VRAM, font, 'T', 199, 175);
	uGDLDrawChar(VRAM, font, 'I', 217, 175); uGDLDrawChar(VRAM, font, 'O', 230, 175); uGDLDrawChar(VRAM, font, 'N', 248, 175);
	
	uGDLFreeSprite(&spr);
	uGDLFreeSprite(&ar_logo);
	uGDLFreeSprite(&laser_beam);
	uGDLFreeSprite(&temp);
}


void uGDLLoadGameMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	
	bool stateChanged = false;
	
	if(event.Y_Pressed || event.escPressed){
		menu = MN_MAIN_MENU;
	}
	
	if(event.downPressed || event.sPressed){
		saveSpriteCounter++;
		stateChanged = true;
		
		if(saveSpriteCounter > 1){
			saveSpriteCounter = 0;
		}
		if(saveSpriteCounter < 0){
			saveSpriteCounter = 1;
		}
	}
	
	if(event.upPressed || event.wPressed){
		saveSpriteCounter--;
		stateChanged = true;
		
		if(saveSpriteCounter > 1){
			saveSpriteCounter = 0;
		}
		if(saveSpriteCounter < 0){
			saveSpriteCounter = 1;
		}
	}
	
	if(saveSpriteCounter == 0){
		uGDLDrawStringLocal(VRAM, font, "MEMORY CARD SLOT 1", 72, 110, WHITE, 0.2f);
		uGDLDrawString(VRAM, font, "MEMORY CARD SLOT 2", 70, 95);
	}
	else{
		uGDLDrawString(VRAM, font, "MEMORY CARD SLOT 1", 72, 110);
		uGDLDrawStringLocal(VRAM, font, "MEMORY CARD SLOT 2", 70, 95, WHITE, 0.2f);
	}
	
	uGDLSprite load;
	uGDLLoadSprite("gui/gui_images/load_save_state.bmp", RGB_888, &load, 310, 219);
	uGDLDispSprite(VRAM, load, 0, 0, PURPLE);
	
	uGDLDrawString(VRAM, font, "SELECT MEMORY CARD SLOT", 50, 145);
	
	uGDLFreeSprite(&load);
}

void uGDLLoadOptionsMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	
	bool stateChanged = false;
	
	if(event.Y_Pressed || event.escPressed){
		stateChanged = true;
		menu = MN_MAIN_MENU;
	}
	
	if(event.downPressed || event.sPressed){
		stateChanged = true;
		optionSpriteCounter++;
		
		if(optionSpriteCounter > 3){
			optionSpriteCounter = 0;
		}
		
		if(optionSpriteCounter < 0){
			optionSpriteCounter = 3;
		}
	}
	
	if(event.upPressed || event.wPressed){
		stateChanged = true;
		optionSpriteCounter--;
		
		if(optionSpriteCounter > 3){
			optionSpriteCounter = 0;
		}
		
		if(optionSpriteCounter < 0){
			optionSpriteCounter = 3;
		}
	}
	
	uGDLSprite load, temp;
	uGDLLoadSprite("gui/gui_images/load_options_menu.bmp", RGB_888, &load, 310, 219);
	uGDLLoadSprite("gui/gui_images/selection_stripe_11.bmp", RGB_888, &temp, 135, 5);
	
	if(optionSpriteCounter == 0){
		uGDLDispSprite(VRAM, temp, 85, 122, PURPLE);
		
		if(event.A_Pressed || event.spacePressed){
			stateChanged = true;
			menu = MN_GAME_OPTIONS_MENU;
		}
	}
	
	if(optionSpriteCounter == 1){
		uGDLDispSprite(VRAM, temp, 85, 110, PURPLE);
		
		if(event.A_Pressed || event.spacePressed){
			stateChanged = true;
			menu = MN_SOUND_MENU;
		}
	}
	
	if(optionSpriteCounter == 2){
		uGDLDispSprite(VRAM, temp, 85, 98, PURPLE);
	}
	
	if(optionSpriteCounter == 3){
		uGDLDispSprite(VRAM, temp, 85, 86, PURPLE);
		
		if(event.A_Pressed || event.spacePressed){
			stateChanged = true;
			menu = MN_DISPLAY_MENU;
		}
	}
	
	uGDLDispSprite(VRAM, load, 0, 0, PURPLE);
	
	uGDLDrawString(VRAM, font, "GAME OPTIONS", 100, 120);
	uGDLDrawString(VRAM, font, "SOUND OPTIONS", 95, 108);
	uGDLDrawString(VRAM, font, "CONTROL OPTIONS", 85, 96);
	uGDLDrawString(VRAM, font, "DISPLAY OPTIONS", 90, 84);
	
	uGDLFreeSprite(&load);
	uGDLFreeSprite(&temp);
}

void uGDLLoadDisplayMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	bool stateChanged = false;
	
	if(event.Y_Pressed || event.escPressed){
		stateChanged = true;
		menu = MN_OPTIONS_MENU;
	}
	
	uGDLSprite display;
	uGDLLoadSprite("gui/gui_images/display.bmp", RGB_888, &display, 310, 219);
	uGDLDispSprite(VRAM, display, 0, 0, PURPLE);
	uGDLFreeSprite(&display);
}

void uGDLLoadSoundMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	bool stateChanged = false;

	uGDLSprite sound;
	uGDLLoadSprite("gui/gui_images/sound_options_menu.bmp", RGB_888, &sound, 310, 219);
	uGDLDispSprite(VRAM, sound, 0, 0, PURPLE);
	uGDLFreeSprite(&sound);
	
	if(event.Y_Pressed || event.escPressed){
		stateChanged = true;
		menu = MN_OPTIONS_MENU;
	}
	
	if(event.downPressed || event.sPressed){
		stateChanged = true;
		soundSpriteCounter++;
		
		if(soundSpriteCounter < 0){
			soundSpriteCounter = 1;
		}
		
		if(soundSpriteCounter > 1){
			soundSpriteCounter = 0;
		}
	}
	
	if(event.upPressed || event.wPressed){
		stateChanged = true;
		soundSpriteCounter--;
		
		if(soundSpriteCounter < 0){
			soundSpriteCounter = 1;
		}
		
		if(soundSpriteCounter > 1){
			soundSpriteCounter = 0;
		}
	}
	
	if(soundSpriteCounter == 0){
		uGDLSprite beam;
		uGDLLoadSprite("gui/gui_images/selection_stripe_111.bmp", RGB_888, &beam, 205, 5);
		uGDLDispSprite(VRAM, beam, 60, 127, PURPLE);
		uGDLFreeSprite(&beam);
		
		if(event.rightPressed || event.dPressed){
			stateChanged = true;
			subSoundCounter++;
			
			if(subSoundCounter > 2){
				subSoundCounter = 2;
			}
			
			if(subSoundCounter < 0){
				subSoundCounter = 0;
			}
		}
		
		if(event.leftPressed || event.aPressed){
			stateChanged = true;
			subSoundCounter--;
			
			if(subSoundCounter > 2){
				subSoundCounter = 2;
			}
			
			if(subSoundCounter < 0){
				subSoundCounter = 0;
			}
		}
	}
	
	if(soundSpriteCounter == 1){
		uGDLSprite beam;
		uGDLLoadSprite("gui/gui_images/selection_stripe_1111.bmp", RGB_888, &beam, 230, 5);
		uGDLDispSprite(VRAM, beam, 40, 115, PURPLE);
		uGDLFreeSprite(&beam);
		
		if(event.rightPressed || event.dPressed){
			stateChanged = true;
			subSoundCounter2++;
			
			if(subSoundCounter2 > 8){
				subSoundCounter2 = 8;
			}
			
			if(subSoundCounter2 < 1){
				subSoundCounter2 = 1;
			}
		}
		
		if(event.leftPressed || event.aPressed){
			stateChanged = true;
			subSoundCounter2--;
			
			if(subSoundCounter2 > 8){
				subSoundCounter2 = 8;
			}
			
			if(subSoundCounter2 < 1){
				subSoundCounter2 = 1;
			}
		}
	}
	
	uGDLSprite button;
	uGDLLoadSprite("gui/gui_images/sound_button.bmp", RGB_888, &button, 6, 9);
	
	if(subSoundCounter == 0){
		uGDLDrawString(VRAM, font, "MONO", 190, 125);
	}
	else if(subSoundCounter == 1){
		uGDLDrawString(VRAM, font, "STEREO", 190, 125);
	}else{
		uGDLDrawString(VRAM, font, "DOLBY", 190, 125);
	}
	
	int i;
	for(i = 0; i < subSoundCounter2; i++){
		uGDLDispSprite(VRAM, button, 198 + (i * 7), 113, PURPLE);
	}
	
	uGDLDrawString(VRAM, font, "SOUND MODE", 75, 125);
	uGDLDrawString(VRAM, font, "SOUND EFFECTS", 52, 113);
	
	uGDLFreeSprite(&button);
	
}

void uGDLLoadGameOptionsMenu(uint32_t *VRAM, uGDLEvent event, uGDLFont font){
	
	bool stateChanged = false;
	
	uGDLSprite game;
	uGDLLoadSprite("gui/gui_images/game_options_menu1.bmp", RGB_888, &game, 310, 219);
	uGDLDispSprite(VRAM, game, 0, 0, PURPLE);
	uGDLFreeSprite(&game);
	
	uGDLSprite beam;
	uGDLLoadSprite("gui/gui_images/selection_stripe_111.bmp", RGB_888, &beam, 205, 5);
	
	if(event.Y_Pressed || event.escPressed){
		menu = MN_OPTIONS_MENU;
	}
	
	if(event.downPressed || event.sPressed){
		stateChanged = true;
		gameSpriteCounter++;
		
		if(gameSpriteCounter > 3){
			gameSpriteCounter = 0;
		}
		
		if(gameSpriteCounter < 0){
			gameSpriteCounter = 3;
		}
	}
	
	if(event.upPressed || event.wPressed){
		stateChanged = true;
		gameSpriteCounter--;
		
		if(gameSpriteCounter > 3){
			gameSpriteCounter = 0;
		}
		
		if(gameSpriteCounter < 0){
			gameSpriteCounter = 3;
		}
	}
	
	if(gameSpriteCounter == 0){
		uGDLDispSprite(VRAM, beam, 75, 132, PURPLE);
		
		if(event.rightPressed || event.dPressed){
			stateChanged = true;
			subDiffCounter++;
			
			if(subDiffCounter > 2){
				subDiffCounter = 2;
			}
			if(subDiffCounter < 0){
				subDiffCounter = 0;
			}
		}
		
		if(event.leftPressed || event.aPressed){
			stateChanged = true;
			subDiffCounter--;
			
			if(subDiffCounter > 2){
				subDiffCounter = 2;
			}
			if(subDiffCounter < 0){
				subDiffCounter = 0;
			}
		}
	}
	
	if(gameSpriteCounter == 1){
		uGDLDispSprite(VRAM, beam, 75, 112, PURPLE);
		
		if(event.leftPressed || event.aPressed){
			stateChanged = true;
			subCrossCounter++;
			
			if(subCrossCounter > 1){
				subCrossCounter = 1;
			}
			if(subCrossCounter < 0){
				subCrossCounter = 0;
			}
		}
		
		if(event.rightPressed || event.dPressed){
			stateChanged = true;
			subCrossCounter--;
			
			if(subCrossCounter > 1){
				subCrossCounter = 1;
			}
			if(subCrossCounter < 0){
				subCrossCounter = 0;
			}
		}
	}
	
	if(gameSpriteCounter == 2){
		uGDLDispSprite(VRAM, beam, 75, 100, PURPLE);
		
		if(event.leftPressed || event.aPressed){
			stateChanged = true;
			subHeadCounter++;
			
			if(subHeadCounter > 1){
				subHeadCounter = 1;
			}
			if(subHeadCounter < 0){
				subHeadCounter = 0;
			}
		}
		
		if(event.rightPressed || event.dPressed){
			stateChanged = true;
			subHeadCounter--;
			
			if(subHeadCounter > 1){
				subHeadCounter = 1;
			}
			if(subHeadCounter < 0){
				subHeadCounter = 0;
			}
		}
	}
	
	if(gameSpriteCounter == 3){
		uGDLSprite little_beam;
		uGDLLoadSprite("gui/gui_images/selection_stripe_1.bmp", RGB_888, &little_beam, 110, 5);
		uGDLDispSprite(VRAM, little_beam, 110, 83, PURPLE);
		uGDLFreeSprite(&little_beam);
	}
	
	if(subDiffCounter == 0){
		uGDLDrawString(VRAM, font, "EASY", 200, 130);
	}
	
	if(subDiffCounter == 1){
		uGDLDrawString(VRAM, font, "NORMAL", 200, 130);
	}
	
	if(subDiffCounter == 2){
		uGDLDrawString(VRAM, font, "HARD", 200, 130);
	}
	
	if(subCrossCounter == 0){
		uGDLDrawStringLocal(VRAM, font, "OFF", 200, 110, BLACK, 0.5f);
		uGDLDrawString(VRAM, font, "ON", 230, 110);
	}
	
	if(subCrossCounter == 1){
		uGDLDrawString(VRAM, font, "OFF", 200, 110);
		uGDLDrawStringLocal(VRAM, font, "ON", 230, 110, BLACK, 0.5f);
	}
	
	if(subHeadCounter == 0){
		uGDLDrawStringLocal(VRAM, font, "OFF", 200, 98, BLACK, 0.5f);
		uGDLDrawString(VRAM, font, "ON", 230, 98);
	}
	
	if(subHeadCounter == 1){
		uGDLDrawString(VRAM, font, "OFF", 200, 98);
		uGDLDrawStringLocal(VRAM, font, "ON", 230, 98, BLACK, 0.5f);
	}
	
	uGDLDrawString(VRAM, font, "DIFFICULTY", 100, 130);
	uGDLDrawString(VRAM, font, "CROSS HAIR", 96, 110);
	uGDLDrawString(VRAM, font, "HEAD MOTION", 90, 98);
	uGDLDrawString(VRAM, font, "CREDITS", 130, 80);
	
	uGDLFreeSprite(&beam);
}

void uGDLLoadMenu(uint32_t *VRAM, uGDLAnim2D *fox, uGDLAnim2D *argonaut, uGDLAnim2D *ar_intro, uGDLEvent event, uGDLFont font){
	switch(menu){
		case MN_FOX_ANIM:{
			uGDLLoadFoxAnim(VRAM, fox);
		}break;
		case MN_ARGONAUT_ANIM:{
			uGDLLoadArgonautAnim(VRAM, argonaut);
		}break;
		case MN_INTRO_ANIM:{
			uGDLLoadIntroAnim(VRAM, ar_intro, event);
		}break;
		case MN_DARK_SCREEN:{
			uGDLLoadDarkScreen(VRAM);
		}break;
		case MN_LOAD_SCREEN:{
			uGDLLoadWaitScreen(VRAM);
		}break;
		case MN_MAIN_MENU:{
			uGDLLoadMainMenu(VRAM, event, font);
		}break;
		case MN_LOAD_GAME_MENU:{
			uGDLLoadGameMenu(VRAM, event, font);
		}break;
		case MN_OPTIONS_MENU:{
			uGDLLoadOptionsMenu(VRAM, event, font);
		}break;
		case MN_DISPLAY_MENU:{
			uGDLLoadDisplayMenu(VRAM, event, font);
		}break;
		case MN_SOUND_MENU:{
			uGDLLoadSoundMenu(VRAM, event, font);
		}break;
		case MN_GAME_OPTIONS_MENU:{
			uGDLLoadGameOptionsMenu(VRAM, event, font);
		}break;
	}
}
