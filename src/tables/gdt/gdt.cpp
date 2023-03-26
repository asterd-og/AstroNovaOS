#include <tables/gdt/gdt.hpp>

namespace Gdt {
    extern "C" void reloadSegs();

    uint64_t data[5] = {
        0x0000000000000000,
    
        0x00009a000000ffff, // 16-bit code
        0x000093000000ffff, // 16-bit data

        0x00cf9a000000ffff, // 32-bit code
        0x00cf93000000ffff, // 32-bit data
    };

    void init() {
        GdtR gdt = {
            .length = (sizeof(uint32_t) * 5) - 1,
            .offset = (uint32_t)&data
        };

        __asm__ volatile("lgdt %0" : : "m"(gdt) : "memory");
        //reloadSegs();
    }
}