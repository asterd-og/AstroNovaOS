#pragma once

#include <stdint.h>
#include <stddef.h>
#include <mboot.h>

#define MAGIC 0xdeadbeef  // Very original, IK.

typedef struct {
    size_t size;
    uint32_t magic;
    bool used;
} Block;

class Heap {
private:
    uint32_t* startingAddress;
    uint32_t* currentAddress;
    uint32_t* endingAddress;
    bool looped;
public:
    void  init(multiboot* mbootPtr);
    void* alloc(size_t size);
    void  free(void* ptr);
};

extern Heap heap;