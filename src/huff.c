#include "huff.h"

Huff * NewHuff() {
	Huff newHuff = (Huff*) malloc(sizeof(Huff));
	newHuff->head = NULL;
	newHuff->size = 0;

	return newHuff;
}