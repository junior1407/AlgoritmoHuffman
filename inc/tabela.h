//
// Created by Valdir Jr on 06/04/2017.
//
#ifndef TABELA_H
#define TABELA_H

typedef struct ElementoTabela ElementoTabela;
typedef struct Tabela Tabela;
typedef struct Linha Linha;

Tabela * CreateTabela();
ElementoTabela * CreateElementoTabela();
Linha * CreateLinha(char i);
void Enqueue(ElementoTabela * elem, char i);
char Dequeue(ElementoTabela * elem);
ElementoTabela * CreateCopiaElemento(Linha * head);
void PrintLinha(Linha * linha);

#endif
