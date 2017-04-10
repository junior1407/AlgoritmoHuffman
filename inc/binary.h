//
// Created by Pedro on 06/04/2017.
//
#ifndef BINARY_H
#define BINARY_H

#include "tabela.h"
#include "huff.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

int is_bit_i_set(unsigned char c, int i);

/*
 * It receives as parameter an int, 'integer', and an int, 'string_size', corresponding to the number of bits of the desired binary number;
 * Returns a string with the binary number of 'integer'.
 */
char * IntegerToBinary(int integer, int string_size);

/*
 * It receives as parameter an string, 'binary_number', of the binary number.
 * Returns a integer of the converted binary number.
 */
int BinaryToInteger(char* binary_number);

/*
 * It receives as parameter an unsigned int *, 'frequencias', and an Tabela *, 'tabela_conversao';
 * Calculate and return in a string the amount of trash in binary number;
 */
char * TrashBinary(unsigned int * frequencias, Tabela * tabela_conversao);

/*
 * It receives as parameter an Huff *, 'tree'.
 * Calculate and return in a string the tree's size in binary number;
 */
char * TreeSizeBinary(Huff * tree);

/*
 * It receives as parameter an string of a binary number;
 * Convert in bytes and print the corresponding characters.
 */
void PrintBinaryToCharacter(char * string);

#endif
