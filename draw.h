#ifndef __DRAW_H
#define __DRAW_H

#include <atomic>
#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

void draw_point(u16 x, u16 y, u32 color);
void draw_line(u16 x1, u16 y1, u16 x2, u16 y2, u32 color);
void draw_block(u16 x1, u16 y1, u16 x2, u16 y2, u32 color);
void draw_circle(u16 x, u16 y, u16 radius);

#endif