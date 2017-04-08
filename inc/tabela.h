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
/*
 * Have a ElementoTabela type, 'elemento_tabela', as a parameter;
 * Returns a pointer to Linha type of the 'elemento_tabela->front'.
 */
Linha * getElementoTabelaFront(ElementoTabela * elemento_tabela);
/*
 * Have a ElementoTabela type, 'elemento_tabela', as a parameter;
 * Returns a int with the 'elemento_tablea->size'.
 */
int getElementoTabelaSize(ElementoTabela * elemento_tabela);
/*
 * Have a ElementoTabela type, 'elemento_tabela', and a int, 'value', as a parameters;
 * Set the 'elemento_tablea->size' with the 'value' value.
 */
void setElementoTabelaSize(ElementoTabela * elemento_tabela, int value);
/*
 * Have a Tabela type, 'tabela', and a int, 'index', as a parameters;
 * Returns a ElementoTabela type of the respective index from the 'tabela'.
 */
ElementoTabela * getTabelaElem(Tabela * tabela, int index);

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
