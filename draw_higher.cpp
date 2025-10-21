#include "draw.h"

extern int width, height;

void draw_line(u16 x1, u16 y1, u16 x2, u16 y2, u32 color){
    if (x1==x2) {
        for (u16 y=y1; y<=y2; y++) draw_point(x1, y, color);
        return;
    }
    if (y1==y2) {
        for (u16 x=x1; x<=x2; x++) draw_point(x, y1, color);
        return;
    }

    float k= (float)(y2 - y1) / (x2 - x1);
    if (k>1) {
        for (u16 y=y1; y<=y2; y++){
            u16 x= x1 + (u16)((y - y1) / k);
            draw_point(x, y, color);
        }
        return;
    } else {
        for (u16 x=x1; x<=x2; x++){
            u16 y= y1 + (u16)(k * (x - x1));
            draw_point(x, y, color);
        }
        return;
    }
}

void draw_block(u16 x1, u16 y1, u16 x2, u16 y2, u32 color){
    for (u16 y=y1; y<=y2; y++){
        for (u16 x=x1; x<=x2; x++){
            draw_point(x, y, color);
        }
    }
    return;
}

void draw_circle(u16 x, u16 y, u16 radius, u32 color){
    int x0= radius, y0=0;
    int err=0;

    while (x0 >= y0){
        draw_point(x + x0, y + y0, color);
        draw_point(x + y0, y + x0, color);
        draw_point(x - y0, y + x0, color);
        draw_point(x - x0, y + y0, color);
        draw_point(x - x0, y - y0, color);
        draw_point(x - y0, y - x0, color);
        draw_point(x + y0, y - x0, color);
        draw_point(x + x0, y - y0, color);

        if (err <= 0){
            y0 += 1;
            err += 2*y0 + 1;
        }
        if (err > 0){
            x0 -= 1;
            err -= 2*x0 + 1;
        }
    }
    return;

}