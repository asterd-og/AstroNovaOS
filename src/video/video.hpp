#pragma once

#include <stdint.h>
#include <stddef.h>
#include <mboot.h>
#include <video/fonts.hpp>

class Video {
public:
    uint32_t* buffer;
    uint32_t* backBuffer;

    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    uint32_t pitch;
    uint32_t size;

    void init(multiboot* hdr);

    // Drawing Functions
    void setPixel(int x, int y, uint32_t color);

    void drawChar(int x, int y, char c, uint32_t fg, font_t font);
    void drawString(int x, int y, char* format, uint32_t fg, font_t font);
    
    // Screen Functions
    void clear(uint32_t color);
    void update();
};

extern Video vid;