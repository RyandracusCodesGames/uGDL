# uGDL - The Ultimate Display Graphics Library (uGDL)
The ultimate open-source 2D and 3D software rendered graphics library.

![uGDLShowCase](https://user-images.githubusercontent.com/108719757/235556187-221586d5-e169-4da8-9a39-79d6f3fbc6cb.png)

## About
The uGDL is the ultimate open-source function library programmed to faciliate the essentials of 2D and 3D graphics programs
designed completely in software with no explicit use of the GPU. Each function was programmed by hand and is able to be manipulated
at the programmer's desire.

The uGDL is capable of drawing 2D shapes, sprites, textures, supports a 2D-animation system, a sprite-based font system capable of supplying a graphics based printf() function,tile-based smooth side scrolling, exporting images, blending colors, sprites, and textures togther, simple UI components, polygonal 3D shapes, and so much more!

## Contents
<!--ts-->
* [Drawing](#drawing)


<!--te-->

## Drawing
In order to begin drawing using function calls from uGDL, we have to program some boiler plate code in order to begin writing more complex programs.
uGDL was programmed using the Windows API in C, but due to the platform independant nature of its code, any platform that you're on simply needs to be able to accept
the pixels sent by uGDL to its window. Once you have a game loop, while loop, coded it, this is what uGDL will need.

```c
/*Structure that abstracts the components of our window display such as our title, width, and height*/
Screen screen;
/*Structure that contains a pointer that will represent all the pixels available in our display*/
FrameBuffer frame_buffer;

int main(){
  /*This function will initialize the available pixels in our window by passing our FrameBuffer structure, our width and height, and the color format for our display*/
  uGDLInitFrameBuffer(&frame_buffer, 640, 480, RGB_888);
  /*This function will initialize all the information about our screen*/
  uGDLInitDispInfo(&screen, NINTENDO_64_W, NINTENDO_64_H, 300, 200, "Alien: Resurrection (PS1)");
  
  static HWND window_handle;
	window_handle = CreateWindow((PCSTR)window_class_name, screen.name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.screen_x, screen.screen_y,
	screen.tvw, screen.tvh, NULL, NULL, hInstance, NULL);
  
  while(1){

    /*This function will fill the entire window display with a particular color*/
    /*The first parameter will take in your virtual memory containings all available pixels for your window*/
    /*The second will taken in a color value commonly packaged into a triplet referred to as an RGB value(Red, Green, Blue)*/
    uGDLFillScreen(frame_buffer.VRAM, uGDL_RGB(4,20,83));

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
  }
}
```
