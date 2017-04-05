#include "../inc/huff.h"
#include <stdlib.h>

Huff * NewHuff() {

	Huff * newHuff = (Huff*) malloc(sizeof(Huff));
	newHuff->head = NULL;
	newHuff->size = 0;

	return newHuff;
}

Huff * MakeTree(unsigned int * frequencias) {
	Huff * huff = NewHuff();
	int i;
	for(i = 0; i < 256; i++) {
		if(frequencias[i] > 0) {
			AddNode(huff, NewNode(i, frequencias[i]));
		}
	}
	while(huff->size > 1) {
		Node * esquerda = PopNode(huff);
		Node * direita = PopNode(huff);
		Node * soma = NewNode('*', (esquerda->freq + direita->freq));
		soma->left = esquerda;
		soma->right = direita;
		AddNode(huff, soma);
	}

	return huff;
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

Node * PopNode(Huff * huff) {
	Node * temp = huff->head;
	huff->head = temp->next;
	free(temp->next);
	huff->size--;

	return temp;
}

void AddNode(Huff * huff, Node * newNode) {
	if(huff == NULL) {
		huff->head = newNode;
	} else {
		Node * i;
    	for(i = huff->head; i != NULL; i = i->next) {
        	if(i->next == NULL) {
            	i->next = newNode;

            	return;
        	}
        	if((i->next->freq >= newNode->freq) && (i->freq <= newNode->freq)) {
            	newNode->next = i->next;
            	i->next = newNode;

            	return;
        	}
    	}
	}
}

void PrintPreOrder(Node * head) {
	if(head != NULL) {
		printf("%c", head->c);
		PrintPreOrder(head->left);
		PrintPreOrder(head->right);
	}
}
