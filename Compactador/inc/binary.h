//
// Created by Pedro on 06/04/2017.
//
#ifndef BINARY_H
#define BINARY_H

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tabela.h"
#include "huff.h"

/*
 * Returns 0 if the bit 'i' isn't setted or returns a number different than 0, if 'i' is setted.
 */
int is_bit_i_set(unsigned char c, int i);
unsigned char set_bit(unsigned char c, int i);
/*
 * It receives as parameter an int, 'integer', and an int, 'string_size', corresponding to the number of bits of the desired binary number;
 * Returns a string with the binary number of 'integer'.
 */
unsigned  char * IntegerToBinary(int integer, int string_size);

/*
 * It receives as parameter an string, 'binary_number', of the binary number.
 * Returns a integer of the converted binary number.
 */
int BinaryToInteger(unsigned char * binary_number);

/*
 * It receives as parameter an unsigned int *, 'frequencias', and an Tabela *, 'tabela_conversao';
 * Calculate and return in a string the amount of trash in binary number;
 */
unsigned char * TrashBinary(long long int * frequencias, Tabela * tabela_conversao);

/*
 * It receives as parameter an Huff *, 'tree'.
 * Calculate and return in a string the tree's size in binary number;
 */
unsigned char * TreeSizeBinary(Huff * tree);

/*
 * It receives as parameters an string(char *), 'string',of a binary number, and a FILE * 'new_file.txt';
 * Convert in bytes and print in the 'new_file.txt' the corresponding characters.
 */
void PrintBinaryToCharacter(unsigned char * string, FILE * new_file);

#endif
