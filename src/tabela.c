//
// Created by Valdir Jr on 06/04/2017.
//
#include "../inc/tabela.h"

struct Linha{

    unsigned char i;
    struct Linha * next;
};

struct ElementoTabela {

    int size;
    struct Linha * front;
    struct Linha * rear;
};

struct Tabela {

    struct ElementoTabela ** elems; // Array de 256 Posições.
};

Linha * CreateLinha(unsigned char i) {

    Linha * novo = (Linha *) malloc(sizeof(Linha));
    novo->i=i;
    novo->next=NULL;
    return novo;
}

ElementoTabela * CreateElementoTabela() {

    ElementoTabela * novo = (ElementoTabela *)malloc(sizeof(ElementoTabela));
    novo->size=0;
    novo->front=NULL;
    return  novo;
}

Tabela * CreateTabela() {

    Tabela * novo = (Tabela *)malloc(sizeof(Tabela));
    novo->elems = (ElementoTabela **)malloc(256*sizeof(ElementoTabela));
    int i;
    for (i = 0; i < 256; i++) {
        (novo->elems)[i] = CreateElementoTabela();
    }
    return novo;
}

void Enqueue(ElementoTabela *tabela, unsigned char i) {

    Linha * novo = CreateLinha(i);
    if (tabela->size==0) {
        tabela->front = novo;
        tabela->rear = novo;
    } else {
        tabela->rear->next = novo;
        tabela->rear = tabela->rear->next;
    }
    (tabela->size)++;
}

ElementoTabela * CreateElementCopy(Linha * head) {

    ElementoTabela * nova = CreateElementoTabela();
    while(head!=NULL) {
        Enqueue(nova, head->i);
        head = head->next;
    }
    return nova;
}

unsigned char Dequeue(ElementoTabela * elem) {

    if (elem->size !=0) {
        if (elem->size == 1) {
            Linha * aux = elem->front;
            elem->front=NULL;
            elem->rear= NULL;
            elem->size =0;
            return aux->i;
        } else {
            Linha * aux = elem->front;
            unsigned char c = elem->rear->i;
            while(aux->next != elem->rear) {
                aux= aux->next;
            }
            free(elem->rear);
            aux->next=NULL;
            elem->rear=aux;
            (elem->size)--;
            return aux->i;
        }
    }
}

unsigned char * GetConvertedBits(ElementoTabela * requested_route) {

    int route_size = requested_route->size;
    int position = 0;
    unsigned char * bits = (unsigned char *)malloc(sizeof(unsigned char)*(route_size+1));
    Linha * current_bit = requested_route->front;
    bits[route_size] = '\0';
    while(route_size > 0) {
        bits[position] = current_bit->i;
        current_bit = current_bit->next;
        position++;
        route_size--;
    }
    return bits;
}

int MaxRoute(Tabela * tabela_conversao) {

    int max = 0;
    int i;
    for(i = 0; i < 256; ++i) {
        if(tabela_conversao->elems[i]->size > max) {
               max = tabela_conversao->elems[i]->size;
        }
    }
    return max;
}

unsigned char GetLinhaI(Linha * l) {

    return l->i;
}

void SetLinhaI(Linha * l, unsigned char i) {

    l->i = i;
}

Linha * GetLinhaNext(Linha * l) {

    return l->next;
}

void SetLinhaNext(Linha * l, Linha * next) {

    l->next= next;
}

int GetElementoTabelaSize(ElementoTabela * elem) {

    return  elem ->size;
}

void SetElementoTabelaSize(ElementoTabela * elem, int size) {

    elem->size = size;
}

Linha * GetElementoTabelaFront(ElementoTabela * elem) {

    return elem->front;
}

void SetElementoTabelaFront(ElementoTabela * elem, Linha * front ) {

    elem->front = front;
}

Linha * GetElementoTabelaRear(ElementoTabela * elem) {

    return elem->rear;
}

void SetElementoTabelaRear(ElementoTabela * elem, Linha * rear ) {

    elem->rear = rear;
}

ElementoTabela * GetTabelaElement(Tabela * tabela, int index) {

    return tabela->elems[index];
}

ElementoTabela ** GetTabelaElements(Tabela * tabela) {

    return tabela->elems;
}

void SetTabelaElemento(Tabela * tabela, ElementoTabela * elemento, int pos) {

    tabela->elems[pos] = elemento;
}