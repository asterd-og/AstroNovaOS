/*
Loader by: Nicola Leone Ciardi and Kevin Meerts
(C) Copyright 2022, All rights reserved.
*/

// Kevin Meerts: https://github.com/KM198912
// Couldnt find Nicola's github.

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void main(uintptr_t ptr);

typedef struct {
    uint32_t magic;
    struct
    {
        bool align: 1;
        bool meminfo: 1;
        bool video: 1;
        uint32_t reserved: 29;
    } flags;
    uint32_t checksum;
    uint8_t  reserved[20];
    uint32_t video_mode;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} multiboot_header_t;

multiboot_header_t multiboot __attribute__((section(".multiboot"))) = {
    .magic = 0x1BADB002,
    .flags = {
        .align = true,
        .meminfo = true,
        .video = true
    },
    .checksum = -(0x1BADB002 + ((1 << 0)/*align*/|(1 << 1)/*meminfo*/|(1<<2)/*vidinfo*/)),
    .video_mode = 0,
    .width = 1280,
    .height = 768,
    .depth = 32
};

static uint8_t kstack[2048] __attribute__((section(".bss"))) = {0};

void _start()
{
    uintptr_t mboot_ptr;
    __asm__ __volatile__("mov %%ebx, %0" : "=m"(mboot_ptr));
    main(mboot_ptr);
    __asm__ __volatile__("hlt");
}