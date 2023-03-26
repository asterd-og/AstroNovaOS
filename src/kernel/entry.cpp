#include <stdint.h>
#include <stddef.h>
#include <mboot.h>
#include <video/video.hpp>
#include <video/term.hpp>
#include <lib/printf.h>
#include <memory/heap.hpp>
#include <lib/string.hpp>
#include <tables/gdt/gdt.hpp>
#include <tables/idt/idt.hpp>

Video vid;
Terminal term;
Heap heap;

int main(uintptr_t ptr) {
    multiboot* mboot = (multiboot*)ptr;

    Gdt::init();
    Idt::init();

    heap.init(mboot);

    vid.init(mboot);

    term.init();
    // term.changeFont(FONT_SYSTEM_8x8);

    printf("GDT Initialised!\n");
    //printf("IDT Initialised!\n");
    printf("AstroNovaOS Booted Successfully!\n");
    printf("  /$$$$$$              /$$                         /$$   /$$                                /$$$$$$   /$$$$$$ \n");
    printf(" /$$__  $$            | $$                        | $$$ | $$                               /$$__  $$ /$$__  $$\n");
    printf("| $$  \\ $$  /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$ | $$$$| $$  /$$$$$$  /$$    /$$ /$$$$$$ | $$  \\ $$| $$  \\__/\n");
    printf("| $$$$$$$$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$| $$ $$ $$ /$$__  $$|  $$  /$$/|____  $$| $$  | $$|  $$$$$$ \n");
    printf("| $$__  $$|  $$$$$$   | $$    | $$  \\__/| $$  \\ $$| $$  $$$$| $$  \\ $$ \\  $$/$$/  /$$$$$$$| $$  | $$ \\____  $$\n");
    printf("| $$  | $$ \\____  $$  | $$ /$$| $$      | $$  | $$| $$\\  $$$| $$  | $$  \\  $$$/  /$$__  $$| $$  | $$ /$$  \\ $$\n");
    printf("| $$  | $$ /$$$$$$$/  |  $$$$/| $$      |  $$$$$$/| $$ \\  $$|  $$$$$$/   \\  $/  |  $$$$$$$|  $$$$$$/|  $$$$$$/\n");
    printf("|__/  |__/|_______/    \\___/  |__/       \\______/ |__/  \\__/ \\______/     \\_/    \\_______/ \\______/  \\______/ ");
                                                                                                              
    //printf("Division by zero occuring in...\n");
    //asm volatile("int $0x0");

    for (;;) {
        vid.update();
    }

    return 0;
}