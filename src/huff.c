#include "huff.h"

Huff * NewHuff() {
	Huff newHuff = (Huff*) malloc(sizeof(Huff));
	newHuff->head = NULL;
	newHuff->size = 0;

	return newHuff;
}

void NewNode(Huff huff, char c, int freq) {
	Node newNode = (Node*) malloc(sizeof(Node));
	newNode->c = c;
	newNode->freq = freq;
	newNode->left = NULL;
	newNode->right = NULL;
}