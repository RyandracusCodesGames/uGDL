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
  * [Color](#color)

<!--te-->

## Drawing
In order to begin drawing using function calls from uGDL, we have to program some boiler plate code in order to begin writing more complex programs.
uGDL was programmed using the Windows API in C, but due to the platform independant nature of its code, any platform that you're on simply needs to be able to accept
the pixels sent by uGDL to its window. Once you have a game loop, while loop, coded it, this is what uGDL will need.

```c
#include <windows.h>
#include <gfx/framebuffer.h>
#include <gfx/color.h>
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
    /*The first parameter will take in your virtual memory containing all available pixels for your window*/
    /*The second will taken in a color value commonly packaged into a triplet referred to as an RGB value(Red, Green, Blue)*/
    uGDLFillScreen(frame_buffer.VRAM, uGDL_RGB888(4,20,83));

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
  }
}
```
# Color
The color programming capabilites of the uGDL was heavily inspired by the Nintendo 64. For its time, the Nintendo 64 featured very
advanced color blending functions powered by its Color Combiner and Blender which were the predecessors of the modern fragement shader.
The Color Combiner mixes and interporlates through multiple layers of colors, and the Blender would mix colors against the corresponding
value already placed in the FrameBuffer resulting in semi-transparent colors without the need for an alpha channel. The uGDL supports 32-Bit
RGBA, 24-Bit RGB, 24-Bit BGR, 16-Bit RGB, and 16-Bit BGR all packaged into 32-Bit unsigned integers. Here are some of the ways to play around
with colors using the uGDL.

Calling a color value in uGDL can be accomplished in multiple ways. First, the uGDL has 5 macros for explicitly calling the different
variants of bit-depth colors. They call begin with the prefix uGDL_ followed by the bit-depth in RGB form. For example, 24-Bit BGR
would be called uGDL_BGR888 with 8 + 8 + 8 adding up to the total 24 bits. Similarly, 16-Bit BGR would be uGDL_BGR565 with 5 + 6 + 5 summing to 16 bits.

uGDL also supports a function called ```c uGDLSetColor(BLACK);``` which will use a set of defined constants: BLACK, WHITE, GRAY, BLUE, GREEN,
RED, PURPLE, BROWN, AND ORANGE, to provided a more beginner friendly manner of playing around with colors.

```c
while(1){

    uGDLFillScreen(frame_buffer.VRAM, uGDL_BGR565(4,20,4));

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
  }

```
