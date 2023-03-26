#include <memory/heap.hpp>
#include <lib/string.hpp>
#include <lib/printf.h>

extern "C" uint32_t kernelEnd;

void Heap::init(multiboot* mboot) {
    this->startingAddress = &kernelEnd + 1024; // we skip 1kb to make sure it wont mess with this class
    uint32_t size = 0;
    for (int i = 0; i < mboot->mmap_length; i++) {
        size += ((multibootMMapEntry*)mboot->mmap_addr + (i * sizeof(multibootMMapEntry)))->len;
    }
    // printf("Memory size is %d GB.\n", size / 1024 / 1024 / 1024);
    this->endingAddress = (uint32_t*)(kernelEnd + size);
    this->currentAddress = this->startingAddress;
    this->looped = false;
}

void* Heap::alloc(size_t size) {
    Block* block = (Block*)this->currentAddress;
    if (block->used == true && block->magic == MAGIC) {
        while (block->magic != MAGIC || block->used != true) {
            this->currentAddress += block->size + sizeof(Block);
            if (this->currentAddress >= this->endingAddress) {
                if (this->looped)
                    return nullptr;
                this->looped = true;
                this->currentAddress = 0;
            }
            block = (Block*)this->currentAddress;
        }
    }
    this->looped = false;
    block->magic = MAGIC;
    block->size = size;
    block->used = true;
    this->currentAddress += sizeof(block) + size;
    return (void*)(this->currentAddress - size);
}