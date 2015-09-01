#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void memcpy(void * dest, void * src, unsigned int bits) {
	assert(dest);
	assert(src);

	int * pDest = (int*)dest;
	int * pSrc = (int*)src;

	while (bits) {
		if (bits >= sizeof(int) * CHAR_BIT) {
			*pDest = *pSrc;
			bits -= sizeof(int);
		}
		else {
			unsigned int srcMask = 0xFFFFFFFF << (32 - bits);
			unsigned int destMask = 0xFFFFFFFF >> bits;
			*pDest = (srcMask & *pSrc) | (destMask & *pDest);
			bits -= bits;
		}
	}
}

int main() {
	unsigned int src1[2] = { 1, 3 };
	unsigned int dest1[2] = { 0, 0 };
	memcpy(dest1, src1, 4);
	assert(dest1[0] == 0);

	unsigned int src2[2] = { 1, 3 };
	unsigned int dest2[2] = { 0, 0 };
	memcpy(dest2, src2, 32);
	assert(dest2[0] == 1);

	unsigned int src3[2] = { 0xFFFFFFFF, 3 };
	unsigned int dest3[2] = { 0, 0 };
	memcpy(dest3, src3, 4);
	assert(dest3[0] == 0xF0000000);

	unsigned int src4[2] = { 0xFFFFFFFF, 3 };
	unsigned int dest4[2] = { 0, 0 };
	memcpy(dest4, src4, 16);
	assert(dest4[0] == 0xFFFFFFFF << (32 - 16));
	
	return 0;
}