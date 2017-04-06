#include "../inc/huff.h"
#include <stdlib.h>
#include "../inc/tabela.h"

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
    //PrintList(huff->head);
	while(huff->size > 1) {

		Node * esquerda = PopNode(huff);
    //    printf("Esquerda %c\n", esquerda->c);
		Node * direita = PopNode(huff);
     //   printf("Direita %c\n", direita->c);
		Node * soma = NewNode('*', (esquerda->freq + direita->freq));
		soma->left = esquerda;
		soma->right = direita;
		AddNode(huff, soma);
      //  PrintList(huff->head);
	}
   // PrintPreOrder(huff->head);
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

void PrintList(Node * node)
{
    while (node!=NULL)
    {
        printf("(%c %d) ",node->c,node->freq);
        node= node->next;
    }
    printf("\n");

}
void AddNode(Huff * huff, Node * newNode) {

  /*  printf("Addando %c\n", newNode->c);
    (huff->size)++;
	if(huff->head == NULL) {
		huff->head = newNode;
	} else {
		Node * i;
    	for(i = huff->head; i != NULL; i = i->next) {
        	if(i->next == NULL) {
            	i->next = newNode;

            	return;
        	}
        	if((i->next->freq > newNode->freq) && (i->freq < newNode->freq)) {
            	newNode->next = i->next;
            	i->next = newNode;

            	return;
        	}
    	}
	}*/

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
         /*   if (atual->freq == newNode->freq) // Casos iguais, vai antes..
            {
                atual->next = newNode;

                (huff->size)++;
                return;
            }*/
            //4 5 6  6*
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

void GeraTabelaConversao(Node*head, Tabela ** tabela, ElementoTabela ** percurso)
{

   //Condições de parada.
    // Se for folha, deve salvar percurso e subir.
    if ((head->left==NULL)&&(head->right==NULL))
    {

        //Linha * nova = CreateCopiaLinha(*percurso);
       // (((*tabela)->elems)[head->c])-> front= nova;
        ((*tabela)->elems)[head->c] = CreateCopiaElemento((*percurso)->front);
        ((*tabela)->elems)[head->c]->size = (*percurso)->size;
        Dequeue(*percurso);
        return;
    }
    Enqueue(*percurso,'0');
    GeraTabelaConversao(head->left, tabela, percurso);

    Enqueue(*percurso,'1');
    GeraTabelaConversao(head->right, tabela, percurso);

    Dequeue(*percurso);



}




void PrintPreOrder(Node * head) {
	if(head != NULL) {
		printf("%c", head->c);
		PrintPreOrder(head->left);
		PrintPreOrder(head->right);
	}
}
