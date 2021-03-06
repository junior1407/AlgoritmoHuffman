//
// Created by Pedro on 06/04/2017.
//
#include "../inc/binary.h"

int is_bit_i_set(unsigned char c, int i) {

    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char * IntegerToBinary(int integer, int string_size) {

    unsigned char * binary_number = (unsigned char *)malloc(sizeof(unsigned char)*(string_size+1));
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

int BinaryToInteger(unsigned char * binary_number) {

    int number = 0;
    int string_size = strlen((char *)binary_number);
    int i, j;
    for(i = string_size-1, j = 0; i >= 0; --i, ++j) {
        if(binary_number[i] == '1') {
            number += pow(2,j);
        }
    }
    return number;
}

unsigned char * TrashBinary(long long int * frequencias, Tabela * tabela_conversao) {

    long long int total_bits = 0;
    int tamanho_caminho;
    unsigned char * trash;
    int i;
    for(i = 0; i < 256; ++i) {
        if(frequencias[i] > 0) {
            tamanho_caminho = GetPercursoSize(GetTabelaElement(tabela_conversao, i));
            total_bits += (frequencias[i]*tamanho_caminho);
        }
    }
    trash = IntegerToBinary(8-(total_bits%8), 3);
    return trash;
}

unsigned char * TreeSizeBinary(Huff * tree) {

    int tree_size = HowManyNodes(GetHuffHead(tree));
    unsigned char * binary_tree_size = IntegerToBinary(tree_size, 13);
    return binary_tree_size;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;

}
void PrintBinaryToCharacter(unsigned char * string, FILE * new_file) {

    unsigned char * str_8bits = (unsigned char *)malloc(sizeof(unsigned char)*9);
    str_8bits[8] = '\0';
    int string_size = strlen((char *)string);
    int rest_flag = (string_size - (string_size%8));
    int bit_position = 0, str_position = 0;
    while(str_position < rest_flag) {
        str_8bits[bit_position] = string[str_position];
        bit_position++;
        str_position++;
        if(bit_position == 8) {
            bit_position = 0;
            fprintf(new_file, "%c", (unsigned char)BinaryToInteger(str_8bits));
        }
    }
    if(string_size - rest_flag) { // Bits quebradinhos
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
        fprintf(new_file, "%c", (unsigned char)BinaryToInteger(str_8bits));
    }
}