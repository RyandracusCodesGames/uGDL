#include <windows.h>
#include <mmsystem.h>
#include <stdint.h>
#include <uGDL.h>

/*Game-loop termiating variable*/
static uGDLBool quit;
/*uGDL Structures Setup*/
FrameBuffer frame_buffer; 	/* A uGDL FrameBuffer encapsulates the pixel data of our window along with its color format and dimensions*/
Screen screen;				/* A uGDL Screen structure abstracts the components neccessary to describe our window display*/
uGDLFont font;				/* A uGDL Font structure holds a collection of bitmapped fonts available to draw arrays of character to the window*/
uGDLCanvas canvas;			/* A uGDL Canvas structure is a rectangulara drawable area with a unique graphics context in the larger display of the frame buffer*/ 
uGDLTilemap tilemap;		/* A uGDL Tilemap structure constructs a 16x16 matrix of configurable tiles onto the window which can be scrolled*/
uGDLAnimSprites terminator, knockback;	/*A uGDL AnimSprites structure contains an accessible spritesheet of character animations*/
uGDLSprite t800;
/*WinAPI Structures Setup*/
static BITMAPINFO frame_bitmap_info;
static HBITMAP frame_bitmap = 0;
static HDC frame_device_context = 0;
/*WinAPI callback function designed to process window display info such as graphics and keyboard input*/
LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);

/*Varibles to hold current system time in miliseconds*/
LARGE_INTEGER gTimerFreq;
LARGE_INTEGER gTimerStart;

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

void Initialize(){
	uGDLInitFrameBuffer(&frame_buffer, 640, 480, RGB_888);
	uGDLInitDispInfo(&screen, NINTENDO_64_W, NINTENDO_64_H, 300, 200, "Machine");
	uGDLInitDebugPrint();
	uGDLInitFont(&font, 9, 9);
	canvas = uGDLCreateCanvas(0,0,320,224,RGB_888);
	uGDLLoadBackgroundLayer(&tilemap, "res/past_city.bmp",2253,213,RGB_888);
	uGDLSetPlaneEraser(&tilemap, GREEN);
	uGDLSetTilemapOffsets(&tilemap, 1933 - 32, 0);
	uGDLInitSpriteAnim(&terminator,"res/terminator_anim.bmp",360,60,40,60,RGB_888);
	uGDLInitSpriteAnim(&knockback,"res/knockback_anim.bmp",350,60,50,60,RGB_888);
}

void Cleanup(){
	uGDLFreeFont(font);
	uGDLFlushDebugPrint();
	uGDLFreeSprite(&t800);
	uGDLFreeSpriteSheet(&terminator);
	uGDLFreeSpriteSheet(&knockback);
	uGDLFreeCanvas(&canvas);
	uGDLFreeTilemap(&tilemap);
	uGDLFreeFrameBuffer(&frame_buffer);	
}

void Display(){
	uGDLSetScissor(0,0,WIDTH,HEIGHT);
//	uGDLFillScreen(frame_buffer.VRAM, BLACK);
//	uGDLClearCanvas(&canvas, BLACK);
	uGDLDispTilemapOnCanvas(&canvas, &tilemap);
	t800 = uGDLPlaySpriteAnim(&terminator,0,8);
	uGDLInitSpriteAttributes(&t800,100,20,1,1,0,0xbafeca);
	uGDLDispSpriteOnCanvas(&canvas,t800);
	uGDLDispScaledCanvas(&canvas, &frame_buffer,2,2);
	uGDLDrawString(frame_buffer.VRAM, font, "DEMO BUILD 0.1B", 180, 400, 1.8, 1.8);
	uGDLSetVertScroll(&tilemap, -1.75f);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow){
	
	const wchar_t window_class_name[] = L"My Window Class";
	static WNDCLASS window_class = {0};
	window_class.lpfnWndProc = WindowProcessMessage;
	window_class.hInstance = hInstance;
	window_class.lpszClassName = (PCSTR)window_class_name;
	RegisterClass(&window_class);
	
	timerInit();
	
	Initialize();

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
	
	frame_bitmap_info.bmiHeader.biWidth  = 624;
    frame_bitmap_info.bmiHeader.biHeight = 441;

    if(frame_bitmap) DeleteObject(frame_bitmap);
    frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, &frame_buffer.VRAM, 0, 0);
    SelectObject(frame_device_context, frame_bitmap);

    frame_buffer.width =  624;
    frame_buffer.height = 441;
	
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
        
        printf("%d\n",drawCount);
        
        if(delta >= 1){
			
			Display();
			
            static HDC device_context;
            device_context = GetDC(window_handle);
            BitBlt(device_context,0,0,640,480,frame_device_context,0,0,SRCCOPY);
			ReleaseDC(window_handle,device_context);
	   		
   			drawCount++;
			delta--;
        }
           	                   
   
        if(timer >= 1000){
            drawCount = 0;          	                   
            timer = 0;
        }
    
	}
	   	
		Cleanup();
	
	return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
		case WM_QUIT:
		case WM_DESTROY:{
			quit = true;
		}break;

		case WM_KILLFOCUS: {
			
		} break;

		case WM_SETFOCUS:

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			
		case WM_KEYDOWN:
		case WM_KEYUP: {
			
		} break;
		     
        default: {
            return DefWindowProc(window_handle, message, wParam, lParam);
        }
    }
	return 0;
}
