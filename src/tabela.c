//
// Created by Valdir Jr on 06/04/2017.
//
#include "../inc/tabela.h"

struct Linha{

    unsigned char i;
    struct Linha * next;
};

struct Percurso {

    int size;
    struct Linha * front;
    struct Linha * rear;
};

struct Tabela {

    struct Percurso ** elems; // Array de 256 Posições.


};

Linha * CreateLinha(unsigned char i) {

    Linha * novo = (Linha *) malloc(sizeof(Linha));
    novo->i=i;
    novo->next=NULL;
    return novo;
}

Percurso * CreatePercurso() {

    Percurso * novo = (Percurso *)malloc(sizeof(Percurso));
    novo->size=0;
    novo->front=NULL;
    return  novo;
}

Tabela * CreateTabela() {

    Tabela * novo = (Tabela *)malloc(sizeof(Tabela));
    novo->elems = (Percurso **)malloc(256*sizeof(Percurso));
    int i;
    for (i = 0; i < 256; i++) {
        (novo->elems)[i] = CreatePercurso();
    }
    return novo;
}

void Enqueue(Percurso *tabela, unsigned char i) {

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

Percurso * CreatePercursoCopy(Linha * head) {

    Percurso * nova = CreatePercurso();
    while(head!=NULL) {
        Enqueue(nova, head->i);
        head = head->next;
    }
    return nova;
}

unsigned char Dequeue(Percurso * elem) {

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

unsigned char * TransformaCaminhoString(Percurso * requested_route) {
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

int GetPercursoSize(Percurso * elem) {

    return  elem ->size;
}

void SetPercursoSize(Percurso * elem, int size) {

    elem->size = size;
}

Linha * GetPercursoFront(Percurso * elem) {

    return elem->front;
}

void SetPercursoFront(Percurso * elem, Linha * front ) {

    elem->front = front;
}

Linha * GetPercursoRear(Percurso * elem) {

    return elem->rear;
}

void SetPercursoRear(Percurso * elem, Linha * rear ) {

    elem->rear = rear;
}

Percurso * GetTabelaElement(Tabela * tabela, int index) {

    return tabela->elems[index];
}

Percurso ** GetTabelaElements(Tabela * tabela) {

    return tabela->elems;
}

void SetTabelaPercurso(Tabela * tabela, Percurso * elemento, int pos) {

    tabela->elems[pos] = elemento;
}