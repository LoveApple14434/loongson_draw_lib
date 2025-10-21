#include "draw.h"
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

static int fb_fd;
static u32 * fb_ptr;
static int width, height;

using vinfo= fb_var_screeninfo;
using finfo= fb_fix_screeninfo;

int fb_init(){
    vinfo vars={};
    fb_fd=open("/dev/fb0", O_RDWR);
    if (fb_fd==-1) return -1;
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &vars);
    width=vars.xres_virtual; height=vars.yres_virtual;
    fb_ptr = (uint32_t *)mmap(nullptr, vars.yres_virtual * vars.xres_virtual * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    return 0;
}

int fb_close(){
    munmap(fb_ptr, height * width * 4);
    close(fb_fd);
    return 0;
}

void draw_point(u16 x, u16 y, u32 color){
    if (x>=width || x<0 || y>=height || y<0) return;
    fb_ptr[y*width + x]=color;
    return;
}