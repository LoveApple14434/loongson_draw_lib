#include "draw.hpp"
#include <stdio.h>

void draw_bmp(const char* filename, u16 start_x, u16 start_y) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return;

    // Read BMP header
    u8 header[54];
    fread(header, sizeof(u8), 54, fp);
    
    // Get image dimensions from header
    u32 bmp_width = *(u32*)&header[18];
    u32 bmp_height = *(u32*)&header[22];
    
    // Cache screen dimensions
    u16 screen_width = get_xres();
    u16 screen_height = get_yres();
    
    // Read and draw pixels from bottom to top (BMP format)
    for (u32 y = 0; y < bmp_height; y++) {
        for (u32 x = 0; x < bmp_width; x++) {
            u8 b = fgetc(fp);
            u8 g = fgetc(fp);
            u8 r = fgetc(fp);
            u32 color = (r << 16) | (g << 8) | b;
            
            // Calculate actual drawing position
            u16 draw_x = start_x + x;
            u16 draw_y = start_y + (bmp_height - 1 - y);
            
            // Only draw if within screen bounds
            if (draw_x < screen_width && draw_y < screen_height) {
                draw_point(draw_x, draw_y, color);
            }
        }
        // Skip padding bytes (BMP rows are aligned to 4 bytes)
        int padding = (bmp_width * 3) % 4;
        if (padding) fseek(fp, padding, SEEK_CUR);
    }

    fclose(fp);
}