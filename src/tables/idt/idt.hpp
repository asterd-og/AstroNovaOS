#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
	uint32_t intNo;
	uint32_t err;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t ss;
} __attribute__((packed)) Registers;

namespace Idt {
    typedef struct {
		uint16_t offsetLow;
		uint16_t cs;
		uint8_t reserved;    // always be zero
		uint8_t attr;
		uint16_t offsetHigh;
	} __attribute__((packed)) IdtEntry;
	
	typedef struct {
		uint16_t limit;
		uint32_t base;
	} __attribute__((packed)) IdtR;

    typedef void(*handler)(void);

    void init();
    void setDesc(uint8_t idx, void* isr);
    void installHandler(uint8_t vec, handler hand);
}