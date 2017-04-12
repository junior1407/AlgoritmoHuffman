#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

/*
 * Data Structure for the Huffman Tree.
 */
typedef struct Huff Huff;

/*
 * Data Structure for the Huffman Tree's Nodes.
 */
typedef struct Node Node;

/*
 * Creates an empty Huffman Tree.
 */
Huff * NewHuff();

/*
 * Given the frequency list of Bytes, this method Generates the Huffman Tree. Returns the New Tree.
 */
Huff * MakeTree(unsigned int * frequencias);

/*
 * Given the PreOrderTree, It generates the HuffMan's Tree. Returns the Tree.
 */
Huff * MakeTreeFromPreOrder(unsigned char * array, int size);
Node * MakeTreeFromPreOrderUtil(unsigned char * array, int size, int * current, Node * node);

/*
 * Given the Node's Atribbutes, It generates a new HuffMan's Tree Node. Returns the New Node.
 */
Node * NewNode(unsigned char c, int freq);
Node * NewEmptyNode();

/*
 * Pops the first node of a Huffman's tree. Returns the deleted Node.
 */
Node * PopNode(Huff * huff);

/*
 * Adds a Node to a given Huffman's Tree in ascending order.
 */
void AddNode(Huff * huff, Node * newNode);

/*
 * Prints the given Huffman's Tree in Preorder transversal in the file 'new_file'.
 */
void PrintPreOrder(Node * head, FILE * new_file);

/*
 * Given an "*" or "\" node, this method check if it's a leaf or not. Returns the result.
 */
int IsLeaf(Node * check);

/*
 * Creates a Conversion table to speed up the process of encoding.
 * Given the First Node of a Huffman's Tree, An Empty Tabela in order to be filled in, An Empy Elemento Tabela representing the navigation of the tree.
 */
void CreatesConversionTable(Node * head, Tabela ** tabela, ElementoTabela ** percurso);

/*
 * It receives a Node * type, 'node', as a parameter and returns a int with the tree size (total number of nodes);
 */
int HowManyNodes(Node * node);


Huff * MakeTreeFromPreOrder(unsigned char * array, int size);
Node * NavigateTree(Node * atual, int direcao);

/*
 * Getters and Setters for the Struct Node.
 */
unsigned char GetNodeC(Node * n);
void SetNodeC(Node * n, unsigned char c);
int GetNodeFreq(Node * n);
void SetNodeFreq(Node * n, int freq);
Node * GetNodeNext(Node * n);
void SetNodeNext(Node * n, Node * next);
Node * GetNodeLeft(Node * n);
void SetNodeLeft(Node * n, Node * left);
Node * GetNodeRight(Node * n);
void SetNodeRight(Node * n, Node * right);

/*
 * Getters and Setters for the Struct HUFF.
 */
Node * GetHuffHead(Huff * h);
void SetHuffHead(Huff * h, Node * head);
int GetHuffSize(Huff * h);
void SetHuffSize(Huff * h, int size);

#endif