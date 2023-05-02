#include "input.h"

void joyDPADPressed(Uint8 hat_state, SDL_Joystick* joystick, uGDLEvent *event){
	// Check the state of the dpad and print the direction if pressed
    hat_state = SDL_JoystickGetHat(joystick, 0);
    
    switch(hat_state){
    	case DPAD_LEFT:{
    		event->leftPressed = true;
    	//	SDL_Delay(150);
    		printf("DPAD Left pressed\n");
		}break;
		case DPAD_RIGHT:{
			event->rightPressed = true;
		//	SDL_Delay(150);
			printf("DPAD Right pressed\n");
		}break;
		case DPAD_UP:{
			event->upPressed = true;
		//	SDL_Delay(150);
			printf("DPAD Up pressed\n");
		}break;
		case DPAD_DOWN:{
			event->downPressed = true;
		//	SDL_Delay(150);
			printf("DPAD Down pressed\n");
		}break;
	}
}

void joyButtonPressed(SDL_Joystick *joystick, uGDLEvent *event){

	if (SDL_JoystickGetButton(joystick, JOY_X) == 1) {
		event->X_Pressed = true;
        printf("X Pressed\n");
    }
    if (SDL_JoystickGetButton(joystick, JOY_A) == 1) {
    	event->A_Pressed = true;
    //	SDL_Delay(150);
        printf("A Pressed\n");
    }
    if (SDL_JoystickGetButton(joystick, JOY_B) == 1) {
    	event->B_Pressed = true;
        printf("B Pressed\n");
    }
    if (SDL_JoystickGetButton(joystick, JOY_Y) == 1) {
    	event->Y_Pressed = true;
    //	SDL_Delay(150);
        printf("Y Pressed\n");
    }
    if (SDL_JoystickGetButton(joystick, JOY_SELECT) == 1) {
    	event->selectPressed = true;
        printf("Select Pressed\n");
    }
}

void processKeyboardInput(bool key_is_down, uint8_t wParam, uGDLEvent *event){
	if(key_is_down) {
		switch(wParam) {
			case KEY_W:{
				printf("W Pressed");
				event->wPressed = true;
			}break;
			case KEY_A:{
				printf("A Pressed");
				event->aPressed = true;
			}break;
			case KEY_S:{
				printf("S Pressed");
				event->sPressed = true;
			}break;
			case KEY_D:{
				printf("D Pressed");
				event->dPressed = true;
			}break;
			case KEY_ENTER:{
				printf("Enter Pressed");
				event->enterPressed = true;
			}break;
			case KEY_ESCAPE:{
				printf("Escaped Pressed");
				event->escPressed = true;
			}break;
			case KEY_Q:{
				printf("Q Pressed");
				event->qPressed = true;
			}break;
			case KEY_E:{
				printf("E Pressed");
				event->ePressed = true;
			}break;
			case KEY_SPACE:{
				printf("Space Pressed");
				event->spacePressed = true;
			}break;
		}
	}
}

void uGDLInitEvent(uGDLEvent *event){
	event->upPressed = event->downPressed = event->leftPressed = event->rightPressed = event->A_Pressed = event->B_Pressed =
	event->Y_Pressed = event->X_Pressed = event->selectPressed = event->wPressed = event->aPressed = event->dPressed = event->sPressed =
	event->enterPressed = event->escPressed = event->spacePressed = event->cPressed = event->qPressed = event->ePressed = false;
}
