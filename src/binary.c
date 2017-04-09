//
// Created by Pedro on 06/04/2017.
//
#include "../inc/binary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char * IntegerToBinary(int integer, int string_size) {

    char* binary_number = (char*)malloc(sizeof(char)*(string_size+1));
    int i, rest;
    int flag = 0;
    rest = integer%2;
    integer = integer/2;
    for(i = string_size-1; i >= 0; --i) {
        if(integer != 0) {
            if(rest) {
                binary_number[i] = '1';
            } else {
                binary_number[i] = '0';
            }
            rest = integer%2;
            integer = integer/2;
        } else if(integer == 0 && !flag) {
            if(rest) {
                binary_number[i] = '1';
            } else {
                binary_number[i] = '0';
            }
            flag = 1;
        } else {
            binary_number[i] = '0';
        }
    }
   // binary_number[string_size] = '\0';
    return binary_number;
}

int BinaryToInteger(unsigned char* binary_number) {

    int number = 0;
    int string_size = strlen(binary_number);
    int i, j;
    for(i = string_size-1, j = 0; i >= 0; --i, ++j) {
        if(binary_number[i] == '1') {
            number += pow(2,j);
        }
    }
    return number;
}