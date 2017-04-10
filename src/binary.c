//
// Created by Pedro on 06/04/2017.
//
#include "../inc/binary.h"

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

char * IntegerToBinary(int integer, int string_size) {

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
        } else if(!flag) {
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
    binary_number[string_size] = '\0';
    return binary_number;
}

int BinaryToInteger(char* binary_number) {

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

char * TrashBinary(unsigned int * frequencias, Tabela * tabela_conversao) {

    int total_bits = 0;
    int bits;
    char* trash;
    int i;
    for(i = 0; i < 256; ++i) {
        if(frequencias[i] > 0) {
            bits = GetElementoTabelaSize(GetTabelaElement(tabela_conversao, i));
            total_bits += (frequencias[i] * bits);
        }
    }
    trash = IntegerToBinary(8-(total_bits%8), 3);
    return trash;
}

char * TreeSizeBinary(Huff * tree) {

    int tree_size = HowManyNodes(GetHuffHead(tree));
    char * binary_tree_size = IntegerToBinary(tree_size, 13);
    return binary_tree_size;
}

void PrintBinaryToCharacter(char * string, FILE * new_file) {

    char* str_8bits = (char*)malloc(sizeof(char)*9);
    str_8bits[8] = '\0';
    int string_size = strlen(string);
    int rest_flag = (string_size - (string_size%8));
    int bit_position = 0, str_position = 0;
    while(str_position < rest_flag) {
        str_8bits[bit_position] = string[str_position];
        bit_position++;
        str_position++;
        if(bit_position == 8) {
            bit_position = 0;
            fprintf(new_file, "%c", BinaryToInteger(str_8bits));
        }
    }
    if(string_size - rest_flag) {
        int rest_bits = string_size - rest_flag;
        int i;
        for(i = 0; i < 8; ++i) {
            if(rest_bits) {
                str_8bits[i] = string[str_position];
                str_position++;
                rest_bits--;
            } else {
                str_8bits[i] = '0';
            }
        }
        fprintf(new_file, "%c", BinaryToInteger(str_8bits));
    }
}