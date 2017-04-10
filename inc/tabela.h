//
// Created by Valdir Jr on 06/04/2017.
//
#ifndef TABELA_H
#define TABELA_H

// Data Structure for the informantion about the enconding of each byte.
typedef struct ElementoTabela ElementoTabela;

// Data Structure for the Conversion Table.
typedef struct Tabela Tabela;

// Data Structure to manage Encoding Codes.
typedef struct Linha Linha;

// Creates an empty Conversion Table.
Tabela * CreateTabela();

//Creates an empty "ElementoTabela".
ElementoTabela * CreateElementoTabela();

// Creates a "Linha" given an char containing '0' or '1'.
Linha * CreateLinha(char i);

// Adds a '0' or '1' to a given "ElementoTabela" representing the enconding of a byte.
void Enqueue(ElementoTabela * elem, char i);

// Removes the last bit of a given enconding. Returns the deleted bit.
char Dequeue(ElementoTabela * elem);

// Creates a copy of a given enconding to a new "ElementoTabela".
ElementoTabela * CreateElementCopy(Linha * head);

Linha * PopFrontElementoTabela(ElementoTabela * elem);

//Prints the entire "Linha".
void PrintLinha(Linha * linha);

//Gets and Sets for the Struct "Linha".
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


//Gets and Sets from the Struct "Tabela".
ElementoTabela ** GetTabelaElements(Tabela * tabela);
void SetTabelaElemento(Tabela * tabela, ElementoTabela* elemento, int pos);
ElementoTabela * GetTabelaElement(Tabela * tabela, int pos);


#endif
