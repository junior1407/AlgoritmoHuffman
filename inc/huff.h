#include <stdio.h>

        typedef struct Huff Huff;
        typedef struct Node Node;
        Huff * NewHuff();
        Huff * MakeTree(unsigned int * frequencias);
        Node * NewNode(unsigned char c, int freq);
        Node * PopNode(Huff huff);
        void AddNode(Huff huff, Node newNode);
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

