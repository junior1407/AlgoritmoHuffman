//
// Created by Valdir Jr on 06/04/2017.
//
#ifndef TABELA_H
#define TABELA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Data Structure for the informantion about the enconding of each byte.
 */
typedef struct Percurso Percurso;

/*
 * Data Structure for the Conversion Table.
 */
typedef struct Tabela Tabela;

/*
 * Data Structure to manage Encoding Codes.
 */
typedef struct Linha Linha;

/*
 * Creates an empty Conversion Table.
 */
Tabela * CreateTabela();

/*
 * Creates an empty "Percurso".
 */
Percurso * CreatePercurso();

/*
 * Creates a "Linha" given an unsigned char containing '0' or '1'.
 */
Linha * CreateLinha(unsigned char i);

/*
 * Adds a '0' or '1' to a given "Percurso" representing the enconding of a byte.
 */
void Enqueue(Percurso * elem, unsigned char i);

/*
 * Removes the last bit of a given enconding. Returns the deleted bit.
 */
unsigned char Dequeue(Percurso * elem);

/*
 * Creates a copy of a given enconding to a new "Percurso".
 */
Percurso * CreatePercursoCopy(Linha * head);

/*
 * It receives an Percurso *, 'requested_route', and returns a string with the respective binary route (Linha->char).
 */
unsigned char * TransformaCaminhoString(Percurso * requested_route);

/*
 * Returns the size of the largest route in conversion table.
 */
int MaxRoute(Tabela * tabela_conversao);

/*
 * Gets and Sets for the Struct "Linha".
 */
unsigned char GetLinhaI(Linha * l);
void SetLinhaI(Linha * l, unsigned char i);
Linha * GetLinhaNext(Linha * l);
void SetLinhaNext(Linha * l, Linha * next);

/*
 * Gets and Sets for the Struct "Percurso".
 */
int GetPercursoSize(Percurso * elem);
void SetPercursoSize(Percurso * elem, int size);
Linha * GetPercursoFront(Percurso * elem);
void SetPercursoFront(Percurso * elem, Linha * front );
Linha * GetPercursoRear(Percurso * elem);
void SetPercursoRear(Percurso * elem, Linha * rear );

/*
 * Gets and Sets from the Struct "Tabela".
 */
Percurso * GetTabelaElement(Tabela * tabela, int index);
Percurso ** GetTabelaElements(Tabela * tabela);
void SetTabelaPercurso(Tabela * tabela, Percurso * elemento, int pos);


#endif