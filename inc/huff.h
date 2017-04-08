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
void CreatesConversionTable(Node*head, Tabela ** tabela, ElementoTabela ** percurso);
void PrintList(Node * node);
int howManyNodes(int count, Node node);
/*
 * Have a point to a Huff type as a parameter.
 * Returns a Node type pointer to the tree head.
 */
//Getters and Setters for the Struct Node
unsigned char GetNodeC(Node *n);
void setNodeC(Node * n, unsigned char c);
int GetNodeFreq(Node * n);
void SetNodeFreq(Node * n, int freq);
Node * GetNodeNext(Node * n);
void SetNodeNext(Node * n, Node * next);
Node * GetNodeLeft(Node * n);
void SetNodeLeft(Node * n, Node * left);
Node * GetNodeRight(Node * n);
void SetNodeRight(Node * n, Node * right);
//Getters and Setters for the Struct HUFF
Node * GetHuffHead(Huff * h);
void SetHuffHead(Huff * h, Node * head);
int GetHuffSize(Huff * h);
void SetHuffSize(Huff * h, int size);




#endif