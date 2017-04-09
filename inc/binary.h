//
// Created by Pedro on 06/04/2017.
//
#ifndef BINARY_H
#define BINARY_H

int is_bit_i_set(unsigned char c, int i);

/*
 * It receives as parameter an integer, 'integer', and the size, 'string_size', corresponding to the number of bits of the desired binary number;
 * Returns a string with the binary number.
 */
unsigned  char * IntegerToBinary(int integer, int string_size);

/*
 * It receives as parameter an string, 'binary_number', of the binary number.
 * Returns a integer of the converted binary number.
 */
int BinaryToInteger(unsigned char* binary_number);

#endif
