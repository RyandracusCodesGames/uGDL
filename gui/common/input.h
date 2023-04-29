#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#ifndef SDL_INPUT
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_gamecontroller.h>
#endif

typedef struct{
	bool upPressed, downPressed, leftPressed, rightPressed, A_Pressed, B_Pressed,
	Y_Pressed, X_Pressed, selectPressed, wPressed, aPressed, dPressed, sPressed, enterPressed, escPressed, spacePressed, cPressed,
	qPressed, ePressed;
}uGDLEvent;

/*Common Key-Bindings for Windows Virtual Key Codes*/
#define KEY_ENTER 0x0D
#define KEY_SHIFT 0x10
#define KEY_ESCAPE 0x1B
#define KEY_SPACE 0x20
#define KEY_W 0x57
#define KEY_A 0x41
#define KEY_S 0x53
#define KEY_D 0x44
#define KEY_Q 0x51
#define KEY_E 0x45
/*SDL Controller Key-Bindings*/
#define DPAD_LEFT SDL_HAT_LEFT
#define DPAD_RIGHT SDL_HAT_RIGHT
#define DPAD_UP SDL_HAT_UP
#define DPAD_DOWN SDL_HAT_DOWN
#define JOY_X  2
#define JOY_A  0
#define JOY_B  1
#define JOY_Y  3
#define JOY_SELECT 7
/*Functions To Process SDL Game Controller Input*/
void joyDPADPressed(Uint8 hat_state, SDL_Joystick *joystick, uGDLEvent *event);
void joyButtonPressed(SDL_Joystick *joystick, uGDLEvent *event);
/*Function To Process Keyboard Input*/
void processKeyboardInput(bool key_is_down, uint8_t wParam, uGDLEvent *event);
void uGDLInitEvent(uGDLEvent *event);
#endif
