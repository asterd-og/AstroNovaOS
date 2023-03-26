#include <video/video.hpp>
#include <lib/string.hpp>
#include <memory/heap.hpp>

void Video::init(multiboot* hdr) {
    this->buffer = (uint32_t*)hdr->framebuffer_addr;
    this->width = hdr->framebuffer_width;
    this->height = hdr->framebuffer_height;
    this->bpp = hdr->framebuffer_bpp;
    this->pitch = hdr->framebuffer_pitch;
    this->size = this->width * this->height * 4; // 4 = A R G B
    this->backBuffer = (uint32_t*)heap.alloc(this->size);
}

void Video::setPixel(int x, int y, uint32_t color) {
    this->backBuffer[y * width + x] = color;
}

void Video::drawChar(int x, int y, char c, uint32_t fg, font_t font) {
    if (c == 0) { return; }
    uint32_t p = font.height * c;
    for (size_t cy = 0; cy < font.height; cy++)
    {
        for (size_t cx = 0; cx < font.width; cx++)
        {
            if (bit_address_from_byte(font.data[p + cy], cx + 1))
            { this->setPixel(x + (font.width - cx), y + cy, fg); }
        }
    }
}

void Video::drawString(int x, int y, char* format, uint32_t fg, font_t font) {
    uint32_t len = strlen(format);
    uint32_t xx = x, yy = y;
    for (uint32_t i = 0; i < len; i++)
    {
        if (format[i] == 0) { break; }
        if (format[i] == '\n') { xx = x; yy += font_get_height(font); continue; }
        else { this->drawChar(xx, yy, format[i], fg, font); xx += font_get_width(font); }
    }
}

void Video::clear(uint32_t color) {
    for (int i = 0; i < this->width * this->height; i++) this->backBuffer[i] = color;
}

void Video::update() {
    for (int i = 0; i < this->width * this->height; i++) this->buffer[i] = this->backBuffer[i];
}