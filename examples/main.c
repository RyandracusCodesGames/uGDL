#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "input/input.h"
#include <uGDL.h>

/*************************************/
/*              uGDL                 */
/* Ultimate Graphics Display Library */
/*                                   */
/*************************************/

/*Game loop terminating variable*/
static bool quit = false;

LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);
bool keyboard[256] = {0};
/*Defines the dimension and color information for a DIP(Device-Independant Bitmap)*/
static BITMAPINFO frame_bitmap_info;
/*Defines the type, width, height, color format, and bit values of a bitmap*/
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;
/*Structure that abstracts the components of our window display*/
Screen screen;
/*Structure that contains a pointer that will represent all the pixels available in our display*/
FrameBuffer frame_buffer;
/*Structure that will contain all of the font characters for our engine*/
uGDLFont font;
/*Structure that captures the states of keyboard and joystick input to be able to encapuslate these events in booleans*/
uGDLEvent event;
/*Varibles to hold current system time in miliseconds*/
LARGE_INTEGER gTimerFreq;
LARGE_INTEGER gTimerStart;
SDL_Joystick *joystick;

void timerInit()
{
    QueryPerformanceFrequency(&gTimerFreq);
    QueryPerformanceCounter(&gTimerStart);
}

long osGetSystemTimeMS()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return (long)((count.QuadPart - gTimerStart.QuadPart) * 1000L / gTimerFreq.QuadPart);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCMDLine, int nCmdShow){
	
	const wchar_t window_class_name[] = L"My Window Class";
	static WNDCLASS window_class = {0};
	window_class.lpfnWndProc = WindowProcessMessage;
	window_class.hInstance = hInstance;
	window_class.lpszClassName = (PCSTR)window_class_name;
	RegisterClass(&window_class);
	
	timerInit();
	
	/*Initalize Graphics Context*/
	uGDLInitFrameBuffer(&frame_buffer, 640, 480, RGB_888);
	uGDLInitDispInfo(&screen, NINTENDO_64_W, NINTENDO_64_H, 300, 200, "Alien: Resurrection (PS1)");
	uGDLInitFont(&font, 9, 9);
	uGDLInitDebugPrint();
	/*Initialize Bitmap Header Info*/
	frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
	frame_bitmap_info.bmiHeader.biPlanes = 1;
	frame_bitmap_info.bmiHeader.biBitCount = 32;
	frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
	frame_device_context = CreateCompatibleDC(0);
	
	static HWND window_handle;
	window_handle = CreateWindow((PCSTR)window_class_name, screen.name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.screen_x, screen.screen_y,
	screen.tvw, screen.tvh, NULL, NULL, hInstance, NULL);
	
	if(window_handle == NULL){
		return -1;
	}

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

	int num_joysticks = SDL_NumJoysticks();
    printf("Number of joysticks connected: %d\n", num_joysticks);

    // Open the first joystick
    joystick = SDL_JoystickOpen(0);

    // Get the number of buttons on the joystick
    int num_buttons = SDL_JoystickNumButtons(joystick);
    printf("Number of buttons: %d\n", num_buttons);
	
	float drawInterval = 1000.00f/60.00f;
    float delta = 0.0f;
    long lastTime = osGetSystemTimeMS();
    long currentTime;
    int timer = 0;
    int drawCount = 0;

	while(!quit){
		static MSG message = {0};
		while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			DispatchMessage(&message);
		}
		
		currentTime = osGetSystemTimeMS();
            
        delta += (currentTime - lastTime)/drawInterval;
        timer += (currentTime - lastTime);
        
        lastTime = currentTime;
        
       //printf("%d\n",drawCount);
        
        if(delta >= 1){
			/*Process Joystick Button Input <X, Y, B, A>  for Xbox and <Square, X, Circle, and Triangle> for Playstation*/
			joyButtonPressed(joystick, &event);
			/*Process Joystick DPad Input*/
			Uint8 hat_state;
	        joyDPADPressed(hat_state, joystick, &event);
	        
	        /*Drawing Routines*/
	        
	        
			InvalidateRect(window_handle, NULL, FALSE);
	   		UpdateWindow(window_handle);
	   		
	   		if(event.spacePressed){
	   			uGDLCaptureScreenshot(frame_buffer);
	   		}
	   		
			/*Initialize the event state to be false after each update to the display*/
			uGDLInitEvent(&event);
	        
	        delta--;              
   			drawCount++;
        }
           	                   
   
        if(timer >= 1000){
            drawCount = 0;          	                   
            timer = 0;
        }
	}
	
	uGDLFreeFrameBuffer(&frame_buffer);
	
	return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
	static bool has_focus = true;
	switch(message){
		case WM_QUIT:
		case WM_DESTROY:{
			quit = true;
		}break;
		case WM_PAINT:{
		 static PAINTSTRUCT paint;
            static HDC device_context;
            device_context = BeginPaint(window_handle, &paint);
            BitBlt(device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top,
                   frame_device_context,
                   paint.rcPaint.left, paint.rcPaint.top,
                   SRCCOPY);
          //	StretchBlt(device_context, 0, 0, 640, 480, frame_device_context, 0, 0, 320, 240, SRCCOPY);
            EndPaint(window_handle, &paint);
		}break;
		case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth  = LOWORD(lParam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

            if(frame_bitmap) DeleteObject(frame_bitmap);
            frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, &frame_buffer.VRAM, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);

            frame_buffer.width =  LOWORD(lParam);
            frame_buffer.height = HIWORD(lParam);
        } break;
        
        case WM_KILLFOCUS: {
			has_focus = false;
			memset(keyboard, 0, 256 * sizeof(keyboard[0]));
		} break;

		case WM_SETFOCUS: has_focus = true; break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			
		case WM_KEYDOWN:
		case WM_KEYUP: {
			if(has_focus) {
				static bool key_is_down, key_was_down;
				key_is_down  = ((lParam & (1 << 31)) == 0);
				key_was_down = ((lParam & (1 << 30)) != 0);
				if(key_is_down) {
					keyboard[(uint8_t)wParam] = key_is_down;
					/*Function Will Process Essential Keyboard Key Codes*/
					processKeyboardInput(key_is_down, (uint8_t)wParam, &event);
				}
			}
		} break;
		     
        default: {
            return DefWindowProc(window_handle, message, wParam, lParam);
        }
    }
	return 0;
}
