/*
 * A quick implementation for malloc and free on Windows OS. Possible improvements to this code:
 * - Making it thread safe.
 * - Change matching blocking to be best fit instead of first fit.
 * - Keep the allocated blocks list sorted and keep using firs fit.
*/
#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <Windows.h>

#define DEBUG_REALLOCATED 0x01
#define DEBUG_SPLITTED 0x02
#define DEBUG_MERGED 0x04
#define DEBUG_HEAPALLOC 0x08

/*
    Simple implementation for malloc that does not count for free.
*/
PVOID alloc_simple(ULONG size) {
    PVOID buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    if (!buffer) {
        return NULL;
    }

    return buffer;
}

/*
    Block that holds metadata and info about the allocated block on memory.
*/
typedef struct _block_info {
    ULONG size;
    ULONG_PTR next_and_free;
    
    // Added for testing purpose
    BYTE debug;
    UINT index;
} block_info;

/*
    Global reference for the head of the free list
*/
block_info * memory_list;

char is_free(block_info * block) {
    return block->next_and_free & 0x1;
}

block_info * get_next(block_info * block) {
    return (block_info*)((~0x1) & block->next_and_free);
}

/*
    Searches for the first free slot that can cope with the requested size.
*/
block_info * search_free_block(ULONG size) {
    block_info * curr = memory_list;
    while (curr && !(is_free(curr) && curr->size >= size)) {
        curr = get_next(curr);
    }
    return curr;
}

/*
    Inserts a system allocated slot into the free list.
*/
void insert_block(block_info * block) {
    UINT index = 0;
    if (!memory_list) {
        memory_list = block;
    }
    else {
        block_info * curr = memory_list;
        block_info * next = get_next(curr);
        ++index;
        while (next) {
            curr = next;
            next = get_next(curr);
            ++index;
        }
        curr->next_and_free = (0x1 & curr->next_and_free) | ((~0x1) & (ULONG_PTR)block);
    }
    block->index = index;
}

/*
    Allocates new memory slot from the system.
*/
block_info * system_alloc(ULONG size) {
    PVOID buffer = alloc_simple(size + sizeof(block_info));
    if (!buffer) {
        return NULL;
    }
    block_info * block = (block_info *)buffer;
    block->next_and_free = 0x1;
    block->size = size;
    block->debug = DEBUG_HEAPALLOC;
    insert_block(block);
    return block;
}

/*
    Tries to split the given block to reduce the internal fragmentation.
*/
block_info * split_block(block_info * block, ULONG size) {
    assert(block->size >= size);
    LONG splitted_size = block->size - (size + sizeof(block_info));
    // this is equivalent to if (splitted_size <= 0) just having fun doing some bit hacks
    if (!splitted_size || splitted_size >> (sizeof(LONG) * CHAR_BIT - 1)) {
        return block;
    }
    // reduce the size of the already allocated block and mark the block as splitted
    block->size = size;
    block->debug |= DEBUG_SPLITTED;

    // extract a new block allocated from the left over memory
    block_info * splitted = (block_info*)(block + size + sizeof(block_info));
    memset(splitted, 0, sizeof(block_info));

    // set the size of the splitted block
    splitted->size = splitted_size;

    // set free bit & next block pointer on the splitted block
    splitted->next_and_free = 0x1 | block->next_and_free;

    // set the next pointer on the original block to point to the splitted block
    block->next_and_free = (0x1 & block->next_and_free) | ((~0x1) & (ULONG_PTR)splitted);

    // update debugging info
    splitted->debug = DEBUG_SPLITTED;
    block_info * curr = splitted;
    curr->index = curr->index;
    while (curr) {
        curr->index++;
        curr = get_next(curr);
    }

    return block;
}

/*
    Implementation for malloc.
*/
PVOID allocate(ULONG size) {
    block_info * block = search_free_block(size);
    if (!block) {
        block = system_alloc(size);
    }
    else {
        block = split_block(block, size);
        block->debug |= DEBUG_REALLOCATED;
    }
    // unset the free bit
    block->next_and_free &= ~0x1;

    return block + 1;
}

/*
    Merge two given contiguous free memory slots.
*/
void merge_blocks(block_info * merged_block, block_info * block) {
    if (!merged_block || !is_free(merged_block) || !block || !is_free(block)) {
        return;
    }

    // add block->size to merged_block->size
    merged_block->size += block->size + sizeof(block_info);

    // set the next pointer of the merged_block to point to block's next node
    merged_block->next_and_free = 0x1 | ((~0x1) & (ULONG_PTR)block->next_and_free);

    // update debugging info
    merged_block->debug = DEBUG_MERGED;
    block_info * curr = get_next(merged_block);
    while (curr) {
        curr->index--;
        curr = get_next(curr);
    }
}

/*
    Tries to merge the current freed block with it's successor or processor.
*/
void merge_block(block_info * block) {
    assert(memory_list);
    block_info * merged_block = memory_list;
    block_info * next = get_next(merged_block);
    while (next && next != block) {
        merged_block = next;
        next = get_next(merged_block);
    };

    if (block != merged_block) {
        merge_blocks(block, get_next(block));
        merge_blocks(merged_block, block);
    }
}

/*
    Implementation for free.
*/
void deallocate(PVOID ptr) {
    if (!ptr) {
        return;
    }
    block_info * block = ((block_info *)(ptr)) - 1;
    assert(!is_free(block));
    block->next_and_free |= 0x1;
    merge_block(block);
}

/*
    Hashtable used for tests.
*/
PVOID map[10];

/*
    Test a specific configuration from malloc and free.
*/
void test(LONG * to_allocate, LONG * to_free, ULONG bytes, UINT block_index, BYTE debug) {
    // setup
    assert(to_allocate);
    for (int i = 0; to_allocate[i] != -1; ++i) {
        PVOID ptr = allocate(to_allocate[i]);
        block_info * block = ((block_info *)ptr) - 1;
        map[block->index] = ptr;
    }

    for (int i = 0; to_free[i] != -1; ++i) {
        PVOID addr = map[to_free[i]];
        deallocate(addr);
    }
    
    // test
    PVOID ptr = allocate(bytes);
    
    // assert
    assert(ptr);
    block_info * block = ((block_info *)(ptr)) - 1;
    assert(block_index == block->index);
    assert(block->debug == debug);
    assert(block->size >= bytes);

    if (debug & DEBUG_HEAPALLOC && debug & DEBUG_SPLITTED) {
        block_info * splitted = block + block->size + sizeof(block_info);
        assert(splitted->debug & DEBUG_SPLITTED);
        assert(!(splitted->debug & DEBUG_HEAPALLOC));
    }

    // clean
    memory_list = NULL; // TO DO: Call HeapFree to free allocated memory
}

/*
    Program entry
*/
int main() {
    LONG to_allocate1[1] = { -1 };
    LONG to_free1[1] = { -1 };
    test(to_allocate1, to_free1, 10, 0, DEBUG_HEAPALLOC);

    LONG to_allocate2[2] = { 10, -1 };
    LONG to_free2[1] = { -1 };
    test(to_allocate2, to_free2, 20, 1, DEBUG_HEAPALLOC);

    LONG to_allocate3[4] = { 11, 22, 33, -1 };
    LONG to_free3[1] = { -1 };
    test(to_allocate3, to_free3, 44, 3, DEBUG_HEAPALLOC);

    LONG to_allocate4[2] = { 10, -1 };
    LONG to_free4[2] = { 0, -1 };
    test(to_allocate4, to_free4, 9, 0, DEBUG_HEAPALLOC | DEBUG_REALLOCATED);

    LONG to_allocate5[2] = { 10, -1 };
    LONG to_free5[2] = { 0, -1 };
    test(to_allocate5, to_free5, 11, 1, DEBUG_HEAPALLOC);

    LONG to_allocate6[3] = { 10, 20, -1 };
    LONG to_free6[2] = { 1, -1 };
    test(to_allocate6, to_free6, 20, 1, DEBUG_HEAPALLOC | DEBUG_REALLOCATED);

    LONG to_allocate7[2] = { 50, -1 };
    LONG to_free7[2] = { 0, -1 };
    test(to_allocate7, to_free7, 10, 0, DEBUG_HEAPALLOC | DEBUG_REALLOCATED | DEBUG_SPLITTED);

    LONG to_allocate8[4] = { 10, 50, 10, -1 };
    LONG to_free8[3] = { 2, 1, -1 };
    test(to_allocate8, to_free8, 11, 1, DEBUG_REALLOCATED | DEBUG_SPLITTED | DEBUG_MERGED);

    LONG to_allocate9[4] = { 10, 50, 10, -1 };
    LONG to_free9[4] = { 0, 1, 2, -1 };
    test(to_allocate9, to_free9, 11, 0, DEBUG_REALLOCATED | DEBUG_SPLITTED | DEBUG_MERGED);

    return 0;
}