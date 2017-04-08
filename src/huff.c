#include "../inc/huff.h"
#include <stdlib.h>

struct Node {
    unsigned char c;
    int freq;
    struct Node * next;
    struct Node * left;
    struct Node * right;
};

struct Huff {
    struct Node * head;
    int size;
};

unsigned char GetNodeC(Node *n)
{
    return  n->c;
}

void SetNodeC(Node * n, unsigned char c)
{
    n->c = c;
}

int GetNodeFreq(Node * n)
{
    return  n->freq;
}

void SetNodeFreq(Node * n, int freq)
{
    n->freq=freq;
}

Node * GetNodeNext(Node * n)
{
    return  n->next;
}

void SetNodeNext(Node * n, Node * next)
{
    n->next= next;
}

Node * GetNodeLeft(Node * n)
{
    return  n->left;
}

void SetNodeLeft(Node * n, Node * left)
{
    n->left= left;
}

Node * GetNodeRight(Node * n)
{
    return  n->right;
}

void SetNodeRight(Node * n, Node * right)
{
    n->right= right;
}

Node * GetHuffHead(Huff * h)
{
    return  h->head;
}

void SetHuffHead(Huff * h, Node * head)
{
    h->head = head;
}

int GetHuffSize(Huff * h)
{
    return  h->size;
}

void SetHuffSize(Huff * h, int size)
{
    h->size= size;
}

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
	while(huff->size > 1)
    {
		Node * esquerda = PopNode(huff);
		Node * direita = PopNode(huff);
		Node * soma = NewNode('*', (esquerda->freq + direita->freq));
		soma->left = esquerda;
		soma->right = direita;
		AddNodeInterno(huff, soma);

	}

	return huff;
}

Node * NewNode(unsigned char c, int freq) {
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
    if (huff->size==1) {

        huff->head= NULL;
        (huff->size)--;
        return temp;
    }
	huff->head = temp->next;
	huff->size--;
	return temp;
}

void PrintList(Node * node) {
    while (node!=NULL)
    {
        printf("(%c %d) ",node->c,node->freq);
        node = node->next;
    }
    printf("\n");
} // TO BE REMOVED.



void AddNodeInterno(Huff * huff, Node * newNode) {
    if (huff->size == 0) // Lista vazia
    {
        huff->head = newNode;
        (huff->size)++;
    }
    else if (huff->head->freq>=newNode->freq) // Adiciona na cabeca
    {
        newNode->next = huff->head;
        huff->head=newNode;
        (huff->size)++;
    }
    else // Adiciona meio/fim
    {
        Node * atual= huff->head;
        while(atual!=NULL)
        {
            if (atual->next==NULL) // Chegou no fim da lista
            {
                atual->next= newNode;
                (huff->size)++;
                return;
            }
            if ((atual->freq <= newNode->freq) && ( atual->next->freq >= newNode->freq)) // Adiciona entre
            {
                newNode->next= atual->next;
                atual->next= newNode;
                (huff->size)++;
                return;
            }
            atual=atual->next;

        }

    }
}


void AddNode(Huff * huff, Node * newNode) {
    if (huff->size == 0) // Lista vazia
    {
        huff->head = newNode;
        (huff->size)++;
    }
    else if (huff->head->freq>newNode->freq) // Adiciona na cabeca
    {
        newNode->next = huff->head;
        huff->head=newNode;
        (huff->size)++;
    }
    else // Adiciona meio/fim
    {
        Node * atual= huff->head;
        while(atual!=NULL)
        {
            if (atual->next==NULL) // Chegou no fim da lista
            {
                atual->next= newNode;
                (huff->size)++;
                return;
            }
            if ((atual->freq <= newNode->freq) && ( atual->next->freq > newNode->freq)) // Adiciona entre
            {
                newNode->next= atual->next;
                atual->next= newNode;
                (huff->size)++;
                return;
            }
            atual=atual->next;

        }

    }
}

void CreatesConversionTable(Node*head, Tabela ** tabela, ElementoTabela ** percurso) {
   //Condições de parada.
    // Se for folha, deve salvar percurso e subir.

    if ((head->left==NULL)&&(head->right==NULL))
    {
        ElementoTabela * tabela_element;
        tabela_element = CreateElementCopy(GetElementoTabelaFront(*percurso));
        SetElementoTabelaSize(tabela_element, GetElementoTabelaSize(*percurso));
        SetTabelaElemento(*tabela, tabela_element, head->c);
        Dequeue(*percurso);


        return;
    }
    Enqueue(*percurso,'0');
    CreatesConversionTable(head->left, tabela, percurso);

    Enqueue(*percurso,'1');
    CreatesConversionTable(head->right, tabela, percurso);

    Dequeue(*percurso);

}

void PrintPreOrder(Node * head) {
	if(head != NULL) {
		printf("%c", head->c);
		PrintPreOrder(head->left);
		PrintPreOrder(head->right);
	}
}