#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define INT_BIT (32)

typedef struct _bitset {
	unsigned int size; // in bytes
	unsigned int index;
	unsigned int * arr;
	char bit_index;

} bitset;

void bitset_initialize(unsigned int size /* in bytes */, bitset * b) {
	assert(b);
	assert(size >= 4 && size % 4 == 0);
	b->size = size / sizeof(int);
	b->arr = malloc(b->size);
	memset(b->arr, 0, b->size * sizeof(int));
	b->bit_index = 0;
	b->index = 0;
}

void bitset_append(unsigned int data, char size /* in bits */, bitset * b) {
	unsigned int bytes_remaining = b->size - b->index;
	char bits_remaining = (INT_BIT * bytes_remaining) - b->bit_index;
	if (size > bits_remaining) return; // not enough space
	if (size && b->bit_index && (b->bit_index + size >= INT_BIT)) {
		char copied_bits = INT_BIT - b->bit_index;
		b->arr[b->index] |= data >> b->bit_index;
		b->bit_index += copied_bits;
		assert(b->bit_index <= INT_BIT);
		b->bit_index %= INT_BIT;
		if (!b->bit_index) b->index++;
		data <<= copied_bits;
		size -= copied_bits;
	}

	assert(b->bit_index < INT_BIT);
	b->arr[b->index] |= data >> b->bit_index;
	b->bit_index += size % INT_BIT;
}

unsigned int bitset_get(int index, char bit, bitset * b) {
	unsigned int v = b->arr[index] & (0x1 << (INT_BIT - bit - 1));
	return v;
}

unsigned int bitset_get2(int index, bitset * b) {
	return b->arr[index];
}

int main() {
	bitset b;
	bitset_initialize(8, &b);
	bitset_append(0x80000000, 1, &b);
	assert(bitset_get(0, 0, &b));
	assert(!bitset_get(0, 1, &b));
	assert(bitset_get2(0, &b) == 0x80000000);

	return 0;
}