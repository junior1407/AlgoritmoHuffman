//
// Created by Valdir Jr on 06/04/2017.
//
#include "../inc/tabela.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void PrintLinha(Linha * linha)
{
    if (linha!=NULL)
    {
        printf("%c ", linha->i);
        PrintLinha(linha->next);
    }


}


ElementoTabela * CreateElementoTabela()
{
    ElementoTabela * novo = (ElementoTabela*)malloc(sizeof(ElementoTabela));
    novo->size=0;
    novo->front=NULL;
    return  novo;

}
Tabela * CreateTabela()
{
    Tabela * novo = (Tabela *)malloc(sizeof(Tabela));
    novo->elems = (ElementoTabela **)malloc(256* sizeof(ElementoTabela));
    int i;
    for (i=0; i<256;i++)
    {
        (novo->elems)[i] = CreateElementoTabela();
    }
    return novo;
}


Linha * CreateLinha(char i)
{
    Linha * novo = (Linha*) malloc(sizeof(Linha));
    novo->i=i;
    novo->next=NULL;
    return novo;
}

void Enqueue(ElementoTabela *tabela, char i)
{
    Linha * novo = CreateLinha(i);
    if (tabela->size==0)
    {
        tabela->front = novo;
        tabela->rear = novo;
    }
    else
    {
        tabela->rear->next = novo;
        tabela->rear = tabela->rear->next;
    }

    (tabela->size)++;
}

Linha * CreateCopiaLinha(Linha * head)
{


}

char Dequeue(ElementoTabela * elem)
{
    if (elem->size !=0)
    {
        if (elem->size == 1)
        {
            Linha * aux = elem->front;
            elem->front=NULL;
            elem->rear= NULL;
            elem->size =0;
            return aux->i;
        }
        else
        {
            Linha * aux = elem->front;
            char c = elem->rear->i;
            while(aux->next != elem->rear)
            {
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


//void Push(ElementoTabela * elem, char i);
//char Pop(ElementoTabela * elem);