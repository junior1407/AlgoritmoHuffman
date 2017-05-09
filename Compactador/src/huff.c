#include "../inc/huff.h"

struct Node {

    unsigned char c;
    long long int freq;
    struct Node * next;
    struct Node * left;
    struct Node * right;
};

struct Huff {

    int size;
    struct Node * head;
};

Huff * NewHuff() {

	Huff * newHuff = (Huff *)malloc(sizeof(Huff));
	newHuff->head = NULL;
	newHuff->size = 0;
	return newHuff;
}

int IsLeaf(Node * check) {

    if((check->left == NULL) && (check->right == NULL)) {
        return 1;
    }
	return 0;
}

Node * NavigateTree(Node * atual, int direcao) {

    if(direcao == 0) {
        return atual->left;
    } else {
        return  atual->right;
    }
}

Huff * MakeTree(long long int * frequencias) {

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

Huff * MakeTreeFromPreOrder(unsigned char * array, int size) {

    int current = 0;
    Node * node = NewEmptyNode();
    Huff * huff = NewHuff();
    huff->head = MakeTreeFromPreOrderUtil(array, size, &current, node);
    return huff;
}

Node * MakeTreeFromPreOrderUtil(unsigned char * array, int size, int * current, Node * node) {

    if(*current < size) {
        if(array[*current] == '\\') {
            node->c = array[++*(current)];
            ++*(current);
            node->left = node->right = NULL;
            return node;
        } else if (array[*current] != '*') {
            node->c = array[*current];
            ++*(current);
            node->left = node->right = NULL;
            return node;
        } else {
            node->c = array[*current];
            ++*(current);
            node->left = MakeTreeFromPreOrderUtil(array, size, current, NewEmptyNode());
            node->right = MakeTreeFromPreOrderUtil(array, size, current, NewEmptyNode());
            return node;
        }
    }
    return NULL;
}

Node * NewEmptyNode() {

    Node * newNode = (Node *)malloc(sizeof(Node));
    return newNode;
}

Node * NewNode(unsigned char c, long long int freq) {

    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->c = c;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;
    return newNode;
}

Node * PopNode(Huff * huff) {

    Node * temp = huff->head;
    if (huff->size == 1) {
        huff->head = NULL;
        (huff->size)--;
        return temp;
    }
    huff->head = temp->next;
    huff->size--;
    return temp;
}

void AddNode(Huff * huff, Node * newNode) {

    if (huff->size == 0) {
        huff->head = newNode;
        (huff->size)++;
    } else if (huff->head->freq >= newNode->freq) { //Inicio
        newNode->next = huff->head;
        huff->head = newNode;
        (huff->size)++;
    } else {  // Meio/Fim
        Node * atual = huff->head;
        while(atual != NULL) {
            if (atual->next == NULL) { //Fimzaum
                atual->next = newNode;
                (huff->size)++;
                return;
            }
            if ((atual->freq <= newNode->freq) && (atual->next->freq >= newNode->freq)) { //Meinho
                newNode->next = atual->next;
                atual->next = newNode;
                (huff->size)++;
                return;
            }
            atual = atual->next;
        }
    }
}

void PrintPreOrder(Node * head, FILE * new_file) {

	if(head != NULL) {
		if(((head->c == '*') || (head->c == '\\')) && IsLeaf(head)) {
            fprintf(new_file, "\\%c", head->c);
			PrintPreOrder(head->left, new_file);
			PrintPreOrder(head->right, new_file);
		} else {
			fprintf(new_file, "%c", head->c);
			PrintPreOrder(head->left, new_file);
			PrintPreOrder(head->right, new_file);
		}
	}
}

int HowManyNodes(Node * node) {

    if(node != NULL) {
    	if(((node->c == '*') || (node->c == '\\')) && IsLeaf(node)) {
    		return (2 + HowManyNodes(node->left) + HowManyNodes(node->right));
    	} else {
        	return (1 + HowManyNodes(node->left) + HowManyNodes(node->right));
    	}
    }
    return 0;
}

void CreatesConversionTable(Node * head, Tabela ** tabela, Percurso ** percurso) {

    if ((head->left == NULL)&&(head->right == NULL)) {
        Percurso * tabela_element;
        tabela_element = CreatePercursoCopy(GetPercursoFront(*percurso)); // Create copy of the current path.
        SetPercursoSize(tabela_element, GetPercursoSize(*percurso));
        SetTabelaPercurso(*tabela, tabela_element, head->c);
        Dequeue(*percurso);
        return;
    }
    Enqueue(*percurso,'0');
    CreatesConversionTable(head->left, tabela, percurso);
    Enqueue(*percurso,'1');
    CreatesConversionTable(head->right, tabela, percurso);
    Dequeue(*percurso);
}

unsigned char GetNodeC(Node * n) {

    return  n->c;
}

void SetNodeC(Node * n, unsigned char c) {

    n->c = c;
}

int GetNodeFreq(Node * n) {

    return  n->freq;
}

void SetNodeFreq(Node * n, int freq) {

    n->freq=freq;
}

Node * GetNodeNext(Node * n) {

    return  n->next;
}

void SetNodeNext(Node * n, Node * next) {

    n->next= next;
}

Node * GetNodeLeft(Node * n) {

    return  n->left;
}

void SetNodeLeft(Node * n, Node * left) {

    n->left= left;
}

Node * GetNodeRight(Node * n) {

    return  n->right;
}

void SetNodeRight(Node * n, Node * right) {

    n->right= right;
}

Node * GetHuffHead(Huff * h) {

    return  h->head;
}

void SetHuffHead(Huff * h, Node * head) {

    h->head = head;
}

int GetHuffSize(Huff * h) {

    return  h->size;
}

void SetHuffSize(Huff * h, int size) {

    h->size= size;
}