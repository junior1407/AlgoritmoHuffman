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
ElementoTabela * CreateElementCopy(Linha * head);
void PrintLinha(Linha * linha);

////Gets and Sets for the Struct "Linha".
char GetLinhaI(Linha * l);
void SetLinhaI(Linha * l, char i);
Linha * GetLinhaNext(Linha * l);
void SetLinhaNext(Linha * l, Linha * next);

//Gets and Sets for the Struct "ElementoTabela".
int GetElementoTabelaSize(ElementoTabela * elem);
void SetElementoTabelaSize(ElementoTabela * elem, int size);
Linha * GetElementoTabelaFront(ElementoTabela * elem);
void SetElementoTabelaFront(ElementoTabela * elem, Linha * front );
Linha * GetElementoTabelaRear(ElementoTabela * elem);
void SetElementoTabelaRear(ElementoTabela * elem, Linha * rear );

//Gets and Sets from the Struct "Tabela"
ElementoTabela ** GetTabelaElements(Tabela * tabela);
void SetTabelaElemento(Tabela * tabela, ElementoTabela* elemento, int pos);
#endif
