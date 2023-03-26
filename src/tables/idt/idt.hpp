#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint32_t r15;
	uint32_t r14;
	uint32_t r13;
	uint32_t r12;
	uint32_t r11;
	uint32_t r10;
	uint32_t r9;
	uint32_t r8;
	uint32_t rsi;
	uint32_t rdi;
	uint32_t rbp;
	uint32_t rdx;
	uint32_t rcx;
	uint32_t rbx;
	uint32_t rax;
	uint32_t intNo;
	uint32_t err;
	uint32_t rip;
	uint32_t cs;
	uint32_t rflags;
	uint32_t rsp;
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