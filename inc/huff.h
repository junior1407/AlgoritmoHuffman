#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>
#include "tabela.h"

typedef struct Huff Huff;
typedef struct Node Node;

Huff * NewHuff();
Huff * MakeTree(unsigned int * frequencias);
Node * NewNode(unsigned char c, int freq);
Node * PopNode(Huff * huff);
void AddNode(Huff * huff, Node * newNode);
void PrintPreOrder(Node * head);
void GeraTabelaConversao(Node*head, Tabela ** tabela, ElementoTabela ** percurso);
void PrintList(Node * node);
//Save the tree using �*� and the pre-order traversal

#endif