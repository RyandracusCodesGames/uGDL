# uGDL - The Ultimate Graphics Display Library (uGDL)
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
  * [Shapes](#shapes)
  * [Sprites](#sprites)
  * [Text](#text)
  * [Animation](#animation)
* [Input](#input)
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
### Color
The color programming capabilites of the uGDL was heavily inspired by the Nintendo 64. For its time, the Nintendo 64 featured very
advanced color blending functions powered by its Color Combiner and Blender which were the predecessors of the modern fragement shader.
The Color Combiner mixes and interporlates through multiple layers of colors, and the Blender would mix colors against the corresponding
value already placed in the FrameBuffer resulting in semi-transparent colors without the need for an alpha channel. The uGDL supports 32-Bit
RGBA, 24-Bit RGB, 24-Bit BGR, 16-Bit RGB, and 16-Bit BGR all packaged into 32-Bit unsigned integers. Here are some of the ways to play around
with colors using the uGDL.

Calling a color value in uGDL can be accomplished in multiple ways. First, the uGDL has 5 macros for explicitly calling the different
variants of bit-depth colors. They call begin with the prefix uGDL_ followed by the bit-depth in RGB form. For example, 24-Bit BGR
would be called uGDL_BGR888 with 8 + 8 + 8 adding up to the total 24 bits. Similarly, 16-Bit BGR would be uGDL_BGR565 with 5 + 6 + 5 summing to 16 bits.

uGDL also supports a function called ```uGDLSetColor(BLACK, RGB_888);``` which will use a set of defined constants: BLACK, WHITE, GRAY, BLUE, GREEN,
RED, PURPLE, BROWN, AND ORANGE, to provided a more beginner friendly manner of playing around with colors.

```c
while(1){
	
    int myColor = uGDLSetColor(RED, BGR_565);
    uGDLFillScreen(frame_buffer.VRAM, myColor);

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
  }

```
Much like the Nintendo 64, the uGDL has functions for blending and interpolating two colors together, converting from an RGB or RGBA structure to a packed
integer and vise versa, dimming or brighening a color, or simply adding or subtracting two colors together. Here's a list of the common color blending functions:
	
* uGDLBlendColor(int col1, int col2, float intensity, ColorFormat cf)
* uGDLBlendColorWithVRAM(int col, uint32_t *VRAM, int x, int y, float factor, ColorFormat cf)
* uGDLAddColor(int col1, int col2, ColorFormat cf)
* uGDLInterpColor(int col1, int col2, float interp, ColorFormat cf)
* uGDLDotColor(int col, float factor, ColorFormat cf)

# Shapes
The uGDL is essentially what we were refer to in graphics programming as a rasterizer which is the process of using geometric primitives such as points, lines,
line stripes, triangles, and polygons to render flat, two dimensional shapes onto a computer monitor to render a full scene. The uGDL is rich in functions capable
of producing and coloring such geometric primitives! It provides the 2D shapes via a header file ```<gfx/geometry.h>``` which contains all the structures that our
functions will use to produce shapes onto our display! uGDL supports points, vertical lines, horizontal lines, general lines, rectangles, triangles, circles, and
convex polygons.

```c

while(1){
	
    uGDLRect rect = {30, 30, 50, 25}, rect2 = {100, 120, 25, 25};
    uGDLPoint2D point = {200, 150};
    uGDLTriangle tri = {10, 100, 30, 90, 20, 50};
    uGDLLine line = {70, 30, 100, 70};

    uGDLFillScreen(frame_buffer.VRAM, uGDLSetColor(BLACK, RGB_888));

    uGDLDrawRect(frame_buffer.VRAM, rect, uGDLBlendColor(BLUE, RED, 0.5f, RGB_888));
    uGDLFillRect(frame_buffer.VRAM, rect2, uGDLBlendColor(BLUE, RED, 0.5f, RGB_888));
    uGDLDrawPoint(frame_buffer.VRAM, point, uGDLInterpColor(BLUE, RED, 0.5f, RGB_888));
    uGDLDrawLine(frame_buffer.VRAM, line, GREEN);
    uGDLFillTriangle(frame_buffer.VRAM, tri, BLUE);

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
  }
```

This will be the result of calling these functions!
![shapes](https://user-images.githubusercontent.com/108719757/235565427-04c90626-d5f1-42fc-8160-20c2c89b962c.png)

# Sprites
What would a graphics library be without supporting custom sprites to animate your 16-Bit characters or displaying Spongebob pictures onto the screen??!
The uGDL supports what is commonly known as a sprite. Essentially, a 2D image that consists of a width, height, and CLUT(Color Look-up Table) which is
essentially all the pixels needed to describe how uGDL should render it to the screen. A sprite should, however, not be confused with an Image. An image in the uGDL is simply a BMP or PNG image that is only used to export a screenshot of your display, textures, or sprites. All "Images" are sprites in uGDL as that is the only
way to render images to the screen. The uGDL supports a structure called ```uGDLSprite``` that will encapsulate the data for your sprite. Using a function called
```uGDLLoadSprite("file_path_.bmp", sprite, RGB_888, width, height)``` defined in ```<gfx/bmp_img.h>``` that uGDL can find your image and convert it into a sprite for your use.

Here is an example program loading a spongebob picture to the window!

```c
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/sprite.h>
#include <gfx/bmp_img.h>
#include <gfx/image.h>

while(1){

    uGDLFillScreen(frame_buffer.VRAM, uGDLSetColor(BLUE, RGB_888));
    
    uGDLSprite spongebob;
    uGDLLoadSprite("spongebob.bmp", RGB_888, &spongebob, 100, 100);
    uGDLDispSprite(frame_buffer.VRAM, spongebob, 100, 200, 0x0);
    uGDLFreeSprite(&spongebob);

    InvalidateRect(window_handle, NULL, FALSE);
    UpdateWindow(window_handle);
}
```

![sponge](https://user-images.githubusercontent.com/108719757/235567752-ea1875fe-4e66-4a2e-af37-70f992b7b450.png)

Essentially the ```uGDLLoadSprite()```function takes in your file path, the Color format of the image, a reference pointer to the sprite structures, and the width and
height of the image. There are a plethora of ways to display the sprite to the screen. The simpliest way to do so is to call the ```uGDLDispSprite()``` function which
will take in your virtual memory, your sprite, an x and y translation offset, and a parameter called erase which is essentially what color you would like uGDL to remove from the image as a sort ofpre-rendered transparency. For example, if you wanted to have a transparent sprite that had a black background behind it, simply pass BLACK into the erase slot to notify uGDL that you would like all instances of black to be removed from the sprite ```uGDLDispSprite(frame_buffer.VRAM, spongebob, 100, 200, BLACK);```.

Using our Color mixer, uGDL can blend two sprites together, blend a sprite with a particular color, blend it with the color already placed in the frame buffer to achieve semi-transparcency like what the Nintendo 64 did. This is what the code would like:

```c
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/sprite.h>
#include <gfx/bmp_img.h>
#include <gfx/image.h>

int main(){
     
       while(1){
           
	   uGDLFillScreen(frame_buffer.VRAM, uGDLBlendColor(GRAY, WHITE, 0.4f, RGB_888));
    
	   uGDLSprite spongebob;
	   uGDLLoadSprite("sponge.bmp", RGB_888, &spongebob, 100, 100);
	   uGDLBlendSpriteTransparent(frame_buffer.VRAM, spongebob, 100, 45, 0.9f);
	   uGDLFreeSprite(&spongebob);

	   InvalidateRect(window_handle, NULL, FALSE);
	   UpdateWindow(window_handle);
       
       }
}
```
![fog](https://user-images.githubusercontent.com/108719757/235570925-ffb020dc-ec49-4b62-9435-8f1c6ad753d8.png)

# Text
uGDL supports sprite-based font capabilites which was a very common practice on old hardware that lacked a file system or any feasible way of
processing font file formats, so they instead opted to manually program a structure that consisted of all the sprites that a joystick or keyboard
provided to display text onto the window display. uGDL uses a similar approach and uses pre-defined sprites that can be replaced or manipulated
by the programmer to fit their needs. That being said, this section is very simple since it only consists of three functions.

* uGDLDrawChar()
* uGDLDrawString()
* uGDLPrintf()

As you would expect, provided by the ```<gfx/font.h>``` and ```<gfx/draw.h>``` header files, ```uGDLDrawChar()``` will display a singular character
wherever you would like to the screen, ```uGDLDrawString()``` will allow a string, and the last one being for formatted output. Here's an example program:

```c
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/font.h>
#include <gfx/sprite.h>

int main(){

	uGDLFont font;
	/*Function takes in reference to font structure and takes in the width and height of our font*/
	uGDLInitFont(&font, 9, 9);
       
       while(1){
       
            uGDLFillScreen(frame_buffer.VRAM, BLACK);
    
	    uGDLDrawChar(frame_buffer.VRAM, font, 'E', 170, 140);
	    uGDLDrawString(frame_buffer.VRAM, font, "GRAPHICS PROGRAMMING IS AWESOME!", 20, 120);

	    InvalidateRect(window_handle, NULL, FALSE);
	    UpdateWindow(window_handle);

       }
       /*Don't forget to free the memory after the program is done using these resources*/
       uGDLFreeFont(&font);

}


```
![font](https://user-images.githubusercontent.com/108719757/235572764-3bb5b49d-9e1c-44b2-93b1-5552f6b4a33e.png)

# Animation
uGDL interperets animations in two seperate and distinct ways. The first is "video playback" or simply a "video". The uGDL can render a video to the screen
using a technique known as ```Keyframe Animation```. Essentially, we interpret our video as being a collection of dozens, hundreds, if not thousands of
independant images when played one after another form a sequence that we refer to as an animation. In order to extract the frames of a video, there is an
awesome software tool called VLC Media Players that will extract the frames for you. Using my Java class in the tools section of the repo, you can then convert it to BMP files, the only image type currently supported by the uGDL, and change its size and color format. In order to use the keyframe animation system, I have provided
a header file ```<gfx/anim2d.h>``` which provides two functions, ```uGDLInitAnimation()``` and ```uGDLPlayAnimation()```.

```uGDLInitAnimation()``` will take in a uGDLAnim2D structure, the numbers of frames, a floating-point variable called current frame, a string for the directory
of the animation, a string to represent the name of the animation, and the extension of the image type which should be BMP until further notice. I have provided a sample animation from the PS1 game Alien: Resurrection. Here's how the code and resulting video looks like:

```c
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/sprite.h>
#include <gfx/bmp_img.h>
#include <gfx/anim2d.h>

int main(){
   
       uGDLAnim2D anim;
       uGDLInitAnimation(&anim, 140, 1, "gfx/animations/fox_interactive_anim/","scene",".bmp");
       
       while(1){
           
	   uGDLFillScreen(frame_buffer.VRAM, BLACK);
       	   uGDLPlayAnimation(frame_buffer.VRAM, &anim);
       
           InvalidateRect(window_handle, NULL, FALSE);
	   UpdateWindow(window_handle);
       }
}

```


https://user-images.githubusercontent.com/108719757/235574401-ffaa6dd2-3db3-47d5-b7c9-54f01953eb1b.mp4

The second kind of animation is 2D, sprite-based animations. While this is still a work in progress due to not having the most modular functionality,
here is how I achieved 2D animation. Essentially, you have a pre-defined number of keyframe animations that have directions assosciated with them. For example,
if your character had a 2 keyframe based running animation, you should prefix it with ```sonic_running_1.bmp and sonic_running_2.bmp```. You use an integer called
spriteCounter that will function as a counter variable for deciding when to increment the variable ```spriteNum``` which will serve as what current keyframe you're on.
You define a string called direction which will serve as the way uGDL can help determine what direction your sprite should be facing. uGDL supports vertical and horizontal flipping of images to avoid redudant and wasteful space for up, down, left, and right directions. As long as you provided one direction, uGDL can flip them
according to the direction that you define. Here's an example of that in play:

```c
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/bmp_img.h>
#include <gfx/sprite.h>
#include <gfx/draw.h>

int main(){

       while(1){
       
           /*Drawing Routines*/
	    uGDLFillScreen(frame_buffer.VRAM, BLACK);
	    
	    if(event.rightPressed || event.dPressed){
		direction = "right";

		spriteCounter++;

		if(spriteCounter >= 10)
	         {
	                if(spriteNum == 1)
	                {
	                    spriteNum = 2;
	                }
	            
	                else if(spriteNum == 2)
	                {
	                    spriteNum = 3;
	                }
	            
	                else if(spriteNum == 3)
	                {
	                    spriteNum = 4;
	                }
	                else if(spriteNum == 4)
	                {
	                    spriteNum = 5;
	                }
	                else if(spriteNum == 5)
	                {
	                    spriteNum = 6;
	                }
	                else if(spriteNum == 6)
	                {
	                    spriteNum = 7;
	                }
	                else if(spriteNum == 7)
	                {
	                    spriteNum = 1;
	                }
	                spriteCounter = 0;
	            }
				
			map.vscroll.x -= 1;
			map2.vscroll.x -= 1;
			map3.vscroll.x += 0.50f;
			map4.vscroll.x -= 0.35f;
			x -= vel; x2 -= vel; x3 -= vel;
			}
			
		if(event.leftPressed || event.aPressed){
		direction = "left";

		spriteCounter++;

		if(spriteCounter >= 10)
	            {
	                if(spriteNum == 1)
	                {
	                    spriteNum = 2;
	                }
	            
	                else if(spriteNum == 2)
	                {
	                    spriteNum = 3;
	                }
	            
	                else if(spriteNum == 3)
	                {
	                    spriteNum = 4;
	                }
	                else if(spriteNum == 4)
	                {
	                    spriteNum = 5;
	                }
	                else if(spriteNum == 5)
	                {
	                    spriteNum = 6;
	                }
	                else if(spriteNum == 6)
	                {
	                    spriteNum = 7;
	                }
	                else if(spriteNum == 7)
	                {
	                    spriteNum = 1;
	                }
	                spriteCounter = 0;
	            }
				
			map.vscroll.x += 1;
			map2.vscroll.x += 1;
			map3.vscroll.x -= 0.50f;
			map4.vscroll.x += 0.35f;
			x += vel; x2 += vel; x3 += vel;
		}
		
		uGDLDispTilemap(frame_buffer.VRAM, &map3);
			uGDLDispTilemap(frame_buffer.VRAM, &map);	
			uGDLDispTilemap(frame_buffer.VRAM, &map2);
			uGDLDispTilemap(frame_buffer.VRAM, &map4);	
			
			uGDLSprite spr = sonic;	
			
			if(direction == "left"){
				switch(spriteNum){
					case 1:{
						spr = sonic;
						break;
					}
					case 2:{
						spr = sonic2;
						break;
					}
					case 3:{
						spr = sonic3;
						break;
					}
					case 4:{
						spr = sonic4;
						break;
					}
					case 5:{
						spr = sonic5;
						break;
					}
					case 6:{
						spr = sonic6;
						break;
					}
					case 7:{
						spr = sonic7;
						break;
					}
				}
				uGDLFlipSpriteHorz(frame_buffer.VRAM, spr, 100, 50, BMP, 0x439931);
			}
			if(direction == "right"){
				switch(spriteNum){
					case 1:{
						spr = sonic;
						break;
					}
					case 2:{
						spr = sonic2;
						break;
					}
					case 3:{
						spr = sonic3;
						break;
					}
					case 4:{
						spr = sonic4;
						break;
					}
					case 5:{
						spr = sonic5;
						break;
					}
					case 6:{
						spr = sonic6;
						break;
					}
					case 7:{
						spr = sonic7;
						break;
					}
				}
				uGDLDispSprite(frame_buffer.VRAM, spr, 100, 50, 0x439931);
			}
			
			
			InvalidateRect(window_handle, NULL, FALSE);
	   		UpdateWindow(window_handle);
       
       }

}

```


https://user-images.githubusercontent.com/108719757/235575833-75083d51-1dd8-481c-912f-2a06c2e0b845.mp4

# Input
uGDL utilizes SDL(Simple DirectMedia Layer) in order to have cross-platform joystick/controller support. uGDL also uses the Windows API ```<windows.h>``` in order
to gain access to keyboard input that Windows will notify us of. uGDL then encapsulates these user events via a structure called ```uGDLEvent``` which consists of
booleans that are updated to be false after each update to the window so that the user can know when certain buttons are pressed. Here's example code to show how to
initialize SDL when starting a program and the windows keyboard.

```c
#include <windows.h>
#include <mmsystem.h>
#include <gfx/framebuffer.h>
#include <gfx/color.h>
#include <gfx/input.h>

int main(){

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    	int num_joysticks = SDL_NumJoysticks();
   	 printf("Number of joysticks connected: %d\n", num_joysticks);

    	// Open the first joystick
    	joystick = SDL_JoystickOpen(0);

    	// Get the number of buttons on the joystick
    	int num_buttons = SDL_JoystickNumButtons(joystick);
    	printf("Number of buttons: %d\n", num_buttons);
	
	uGDLEvent event;

	while(1){

	    /*Process Joystick Button Input <X, Y, B, A>  for Xbox and <Square, X, Circle, and Triangle> for Playstation*/
	    joyButtonPressed(joystick, &event);
	   /*Process Joystick DPad Input*/
	    Uint8 hat_state;
	    joyDPADPressed(hat_state, joystick, &event);
	    
	    *Initialize the event state to be false after each update to the display*/
	    uGDLInitEvent(&event);
	    
	    if(event.spacePressed || event.Y_Pressed){
	    	uGDLDrawString(frame_buffer.VRAM, "Space bar or Y Button Pressed", font, 200, 200);
	    }
	}
}

```
