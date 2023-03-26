#include <tables/idt/idt.hpp>
#include <lib/printf.h>

namespace Idt {
    static const char *messages[32] = {
        "Division by zero",
        "Debug",
        "Non-maskable interrupt",
        "Breakpoint",
        "Detected overflow",
        "Out-of-bounds",
        "Invalid opcode",
        "No coprocessor",
        "Double fault",
        "Coprocessor segment overrun",
        "Bad TSS",
        "Segment not present",
        "Stack fault",
        "General protection fault",
        "Page fault",
        "Unknown interrupt",
        "Coprocessor fault",
        "Alignment check",
        "Machine check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
    };

    extern "C" void* intVector[];

    __attribute__((aligned(0x10))) 
    static IdtEntry idt[256];

    handler handlers[16];

    void init() {
        __asm__ volatile ("cli");

        static IdtR idtr = {
            .limit = (uint16_t)sizeof(IdtEntry) * 256 - 1,
            .base = (uintptr_t)&idt[0]
        };

        for (uint8_t idx = 0; idx < 255; idx++)
            setDesc(idx, intVector[idx]);
        
        __asm__ volatile("lidt %0" : : "m"(idtr));
        __asm__ volatile("sti");
    }

    void setDesc(uint8_t idx, void* isr) {
        IdtEntry* entry = &idt[idx];

        entry->offsetLow = (uint32_t)isr & 0xFFFF;
        entry->cs = 0x08;
        entry->attr = 0x8E;
        entry->offsetHigh = (uint32_t)isr >> 16;
        entry->reserved = 0;
    }

    void installHandler(uint8_t idx, handler hand) {
        handlers[idx] = hand;
    }

    extern "C" void intHandler(Registers* regs) {
        if (regs->intNo < 32) {
            __asm__ volatile("cli");

            printf("exception has occurred!\n%s\n\n", messages[regs->intNo]);

            for (;;) __asm__ volatile("hlt");
        }
    }
}