#include <video/term.hpp>
#include <video/video.hpp>
#include <lib/string.hpp>

void Terminal::init() {
    this->font = FONT_SYSTEM_8x16;
    this->fg = 0xFFFFFFFF;
    this->bg = 0x0;
    this->x = 0;
    this->y = 0;
    vid.clear(0);
}

void Terminal::changeFont(font_t font) {
    this->font = font;
}

void Terminal::write(char c) {
    if (c == '\n') {
        this->x = 0;
        this->y += font_get_height(this->font);
    } else {
        vid.drawChar(this->x, this->y, c, this->fg, this->font);

        if (this->x + font_get_width(this->font) > vid.width) {
            this->x = 0;
            this->y += font_get_height(this->font);
        } else this->x += font_get_width(this->font);
    }
    //vid.update();
}

void Terminal::print(char* str) {
    for (int i = 0; i < strlen(str); i++) this->write(str[i]);
}

extern "C" void _putchar(char c) {
    term.write(c);
}