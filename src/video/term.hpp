#pragma once

#include <stdint.h>
#include <stddef.h>
#include <video/fonts.hpp>

class Terminal {
public:
    font_t font;

    int x;
    int y;
    uint32_t bg;
    uint32_t fg;

    void init();
    void changeFont(font_t font);
    void write(char c);
    void print(char* str);
};

extern Terminal term;