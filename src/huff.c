#include "../inc/huff.h"
#include <stdlib.h>

Huff * NewHuff() {

	Huff * newHuff = (Huff*) malloc(sizeof(Huff));
	newHuff->head = NULL;
	newHuff->size = 0;

	return newHuff;
}

Node * NewNode(char c, int freq) {
    Node * newNode = (Node*) malloc(sizeof(Node));
    newNode->c = c;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;

    return newNode;
}

Node * PopNode(Huff huff) {
	Node * temp = huff->head;
	huff->head = temp->next;
	free(temp->next);
	huff->size--;

	return temp;
}

void AddNode(Huff huff, Node newNode) {
	if(huff == NULL) {
		huff->head = newNode;
	} else {
		huff * i;
    	for(i = huff->head; i != NULL; i = i->next) {
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
}
