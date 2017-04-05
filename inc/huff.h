//Arquivo huff.h
        typedef struct Huff Huff;
        typedef struct Node Node;
        Huff * NewHuff();
        void NewNode(Huff huff, char c, int freq);
        //Save the tree using “*” and the pre-order traversal
         struct Node {
                char c;
                int freq;
                Node * next;
                Node * left;
                Node * right;
        };
        struct Huff {
                Node * head;
                int size;        
        };    

