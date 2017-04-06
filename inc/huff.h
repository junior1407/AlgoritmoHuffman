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
struct Node {
    unsigned char c;
    int freq;
    Node * next;
    Node * left;
    Node * right;
};
struct Huff {
    Node * head;
    int size;
};

/*/


 typedef struct Huff Huff;
typedef struct Node Node;
Huff * NewHuff();
Huff * MakeTree(unsigned int * frequencias);
Node * NewNode(char c, int freq);
Node * PopNode(Huff * huff);
void AddNode(Huff * huff, Node * newNode);
void PrintPreOrder(Node * head);
void PrintList(Node * node);

         struct Tabela {
          	//Array de elementos
            ElementoTabela **elems;
            int size; //256 SEMPRE
        };
        struct ElementoTabela {

          	unsigned char c;
            int size;
            Linha * linha;
        };
        struct Linha{
          char i;
          Linha * next;
    		}


        d

        a -> 0 0 1
        b -> 1 0 1
        c -> ...
        d -> ....
        f -> ....
 */