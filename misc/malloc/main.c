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

/*
	Simple implementation for malloc that does not count for free.
*/
PVOID alloc_simple(SIZE_T size) {
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
	char free;
	SIZE_T size;
	struct _block_info * next;
	char reallocated;
	UINT index;
} block_info;

/*
	Global reference for the head of the free list
*/
block_info * memory_list;

/*
	Searches for the first free slot that can cope with the requested size.
*/
block_info * search_free_block(SIZE_T size) {
	block_info * curr = memory_list;
	while (curr && !(curr->free && curr->size >= size)) {
		curr = curr->next;
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
		++index;
		while (curr->next) {
			curr = curr->next;
			++index;
		}
		curr->next = block;
	}
	block->index = index;
}

/*
	Allocates new memory slot from the system.
*/
block_info * system_alloc(SIZE_T size) {
	PVOID buffer = alloc_simple(size + sizeof(block_info));
	if (!buffer) {
		return NULL;
	}
	block_info * block = (block_info *)buffer;
	block->next = NULL;
	block->size = size;
	insert_block(block);
	return block;
}

/*
	Implementation for malloc.
*/
PVOID alloc(SIZE_T size) {
	block_info * block = search_free_block(size);
	if (!block) {
		block = system_alloc(size);
		block->reallocated = 0;
	}
	else {
		block->reallocated = 1;
	}
	block->free = 0;

	return block + 1;
}

/*
	Implementation for free.
*/
void free(PVOID ptr) {
	if (!ptr) {
		return;
	}
	block_info * block = ((block_info *)(ptr)) - 1;
	assert(!block->free);
	block->free = 1;
}

/*
	Hashtable used for tests.
*/
PVOID map[10];

/*
	Test a specific configuration from malloc and free.
*/
void test(SIZE_T * to_allocate, SIZE_T * to_free, SIZE_T bytes, UINT block_index, char reallocated) {
	// setup
	assert(to_allocate);
	for (int i = 0; to_allocate[i] != -1; ++i) {
		PVOID ptr = alloc(to_allocate[i]);
		block_info * block = ((block_info *)ptr) - 1;
		map[block->index] = ptr;
	}

	for (int i = 0; to_free[i] != -1; ++i) {
		free(map[to_free[i]]);
	}
	
	// test
	PVOID ptr = alloc(bytes);
	
	// assert
	assert(ptr);
	block_info * block = ((block_info *)(ptr)) - 1;
	assert(block_index == block->index);
	assert(block->reallocated == reallocated);
	if (reallocated) {
		assert(bytes <= block->size);
	}
	else {
		assert(bytes == block->size);
	}

	// clean
	memory_list = NULL; // TO DO: Call HeapFree to free allocated memory
}

/*
	Program entry
*/
int main() {
	SIZE_T to_allocate1[1] = { -1 };
	SIZE_T to_free1[1] = { -1 };
	test(to_allocate1, to_free1, 10, 0, 0);

	SIZE_T to_allocate2[2] = { 10, -1 };
	SIZE_T to_free2[1] = { -1 };
	test(to_allocate2, to_free2, 20, 1, 0);

	SIZE_T to_allocate3[4] = { 11, 22, 33, -1 };
	SIZE_T to_free3[1] = { -1 };
	test(to_allocate3, to_free3, 44, 3, 0);

	SIZE_T to_allocate4[2] = { 10, -1 };
	SIZE_T to_free4[2] = { 0, -1 };
	test(to_allocate4, to_free4, 9, 0, 1);

	SIZE_T to_allocate5[2] = { 10, -1 };
	SIZE_T to_free5[2] = { 0, -1 };
	test(to_allocate5, to_free5, 11, 1, 0);

	SIZE_T to_allocate6[3] = { 10, 20, -1 };
	SIZE_T to_free6[2] = { 1, -1 };
	test(to_allocate6, to_free6, 20, 1, 1);

	return 0;
}