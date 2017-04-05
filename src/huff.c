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
	newNode->next = NULL;
	if(huff == NULL) {
		huff = newNode;
	} else {
		huff * i;
    	for(i = huff; i != NULL; i = i->next) {
        if(i->next == NULL) {
            i->next = newNode;
            return;
        }
        if((i->next->freq >= freq) && (i->freq <= freq)) {
            newNode->next = i->next;
            i->next = newNode;
            return;
        }
    }
}