#include "draw.hpp"
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

namespace {
    // 匿名命名空间，效果类似 static
    int fb_fd = -1;
    u32 * fb_ptr = nullptr;
    u16 width = 0, height = 0;
    bool initialized = false;
}

using vinfo= fb_var_screeninfo;
using finfo= fb_fix_screeninfo;

int fb_init(){
    vinfo vars={};
    fb_fd=open("/dev/fb0", O_RDWR);
    if (fb_fd==-1) return -1;
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &vars);
    width=vars.xres_virtual; height=vars.yres_virtual;
    fb_ptr = (uint32_t *)mmap(nullptr, vars.yres_virtual * vars.xres_virtual * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    initialized= true;
    return 0;
}

int fb_close(){
    if (!initialized) {
        return -1;
    }
    munmap(fb_ptr, height * width * 4);
    close(fb_fd);
    return 0;
}

void draw_point(u16 x, u16 y, u32 color){
    if (!initialized) return;
    if (x>=width || x<0 || y>=height || y<0) return;
    fb_ptr[y*width + x]=color;
    return;
}

u16 get_xres(){
    if (initialized) {
        return width;
    }
    else {
        return 0;
    }
}

u16 get_yres(){
    if (initialized) {
        return height;
    }
    else {
        return 0;
    }
}
