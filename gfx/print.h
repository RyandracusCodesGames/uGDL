#ifndef PRINT_H
#define PRINT_H


#include "framebuffer.h"
#include "color.h"
#include "sprite.h"
#include "canvas.h"
#include "draw.h"
#include "font.h"

extern uGDLFont printfont;

void uGDLInitDebugPrint();
void uGDLPrint(uint32_t *VRAM, char *fmt);
void uGDLPrintf(uint32_t *VRAM, char *fmt,...);
void uGDLPrintColoredText(uint32_t *VRAM, char *fmt, int col);

#endif
