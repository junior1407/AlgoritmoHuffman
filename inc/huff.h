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

int howManyNodes(int count, Node node);
// retorna o número de nós da arvore//
//a variável "count" deve ser setada com 0 se node = huff->head//

#endif