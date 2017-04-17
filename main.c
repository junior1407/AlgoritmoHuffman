#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inc/tabela.h"
#include "inc/huff.h"
#include "inc/binary.h"
#define FRENTE 1
#define TRAS 0
#define BUFFER_SIZE 500
#define STRING_FILE_SIZE 100000

typedef unsigned char byte;

byte * ReadFile(FILE * file, int numBytes);
unsigned char * GetNBits(byte b,  int frente, int n);
void GetFrequency(FILE * file, unsigned int * frequencias);
unsigned char * ConcatString(unsigned char * str1, unsigned char * str2, int new_str_size);
void PrintHeader(unsigned int * frequencias, Huff * tree, Tabela * tabela_conversao, FILE * new_file);
int TotalFrequency(unsigned int * frequencias);
void Convert(FILE * initial_file, FILE * final_file, Tabela * tabela_conversao, unsigned int * frequencias);
void Compress(char * file_to_compress, char * file_created);
void Decompress(char * file_to_decompress, char * decompressed_file);

int main() {

    int comp_descomp;
    do {
        printf("Digite 1 para COMPRIMIR ou 0 para DESCOMPRIMIR.\n");
        scanf("%d", &comp_descomp);
        getchar();
        if(comp_descomp != 1 && comp_descomp != 0) {
            printf("Comando invalido!\n");
        }
    }while(comp_descomp != 1 && comp_descomp != 0);
    if(comp_descomp) {
        char file_to_compress[100];
        char file_created[100];
        printf("Digite o caminho do arquivo que sera comprimido:\n");
        gets(file_to_compress);
        printf("Digite o caminho do novo arquivo comprimido que sera criado:\n");
        gets(file_created);
        Compress(file_to_compress, file_created);
    } else {
        char file_to_decompress[100];
        char decompressed_file[100];
        printf("Digite o caminho do arquivo que sera descomprimido:\n");
        gets(file_to_decompress);
        printf("Digite o caminho do novo arquivo descomprimido que sera criado:\n");
        gets(decompressed_file);
        Decompress(file_to_decompress, decompressed_file);
    }
    return 0;
}

byte * ReadFile(FILE * file, int numBytes) {

    byte * array = (byte *)malloc(sizeof(byte)*(numBytes+1));
    int i;
    for(i = 0; i < numBytes; i++) {
        fread((&(array[i])), 1, 1, file);
    }
    array[numBytes]='\0';
    return  array;
}

unsigned char * GetNBits(byte b,  int frente, int n) {

    unsigned char * array = (unsigned char *)malloc(sizeof(unsigned char)*(n+1));
    if(frente){
        b = b >> (8-n);
        b = b << (8-n);
    } else {
        b = b << (8 - n);
    }
    int i,j;
    for(i = 7, j = 0; i >= 0; i--, j++) {
        if (is_bit_i_set(b,i) == 0) {
            array[j] = '0';
        } else {
            array[j] = '1';
        }
    }
    array[n] = '\0';
    return array;
}

void GetFrequency(FILE * file, unsigned int * frequencias) {

    byte atual[100000];
    int read_size;
    int i;
    while((read_size = fread(&atual, 1, 100000, file)) >= 1) {
        for(i = 0; i < read_size; ++i) {
            frequencias[atual[i]]++;
        }
    }
    rewind(file);
}

unsigned char * ConcatString(unsigned char * str1, unsigned char * str2, int new_str_size) {

    unsigned char * new_str = (unsigned char *)malloc(sizeof(unsigned char)*(new_str_size+1));
    int i, str_position = 0;
    for(i = 0; str1[i] != '\0' && str_position < new_str_size; ++i) {
        new_str[str_position] = str1[i];
        str_position++;
    }
    for(i = 0; str2[i] != '\0' && str_position < new_str_size; ++i) {
        new_str[str_position] = str2[i];
        str_position++;
    }
    new_str[new_str_size] = '\0';
    return new_str;
}

void PrintHeader(unsigned int * frequencias, Huff * tree, Tabela * tabela_conversao, FILE * new_file) {

    unsigned char * trash = TrashBinary(frequencias, tabela_conversao);
    unsigned char * tree_size = TreeSizeBinary(tree);
    unsigned char * first_16bits = ConcatString(trash, tree_size, 16);
    PrintBinaryToCharacter(first_16bits, new_file);
    PrintPreOrder(GetHuffHead(tree), new_file);
}

int TotalFrequency(unsigned int * frequencias) {

    int i;
    int total_frenquency = 0;
    for(i = 0; i < 256; ++i) {
        if(frequencias[i] > 0) {
            total_frenquency += frequencias[i];
        }
    }
    return total_frenquency;
}

void Convert(FILE * initial_file, FILE * final_file, Tabela * tabela_conversao, unsigned int * frequencias) {

    byte file_char[100000];
    int read_size;
    int read_position = 0;
    unsigned char * string_file = (unsigned char *)malloc(sizeof(unsigned char)*(STRING_FILE_SIZE+1));
    string_file[STRING_FILE_SIZE] = '\0';
    int string_file_position = 0;
    int total_frequency = TotalFrequency(frequencias);
    ElementoTabela * binary_route;
    unsigned char * converted_binary;
    int current_route_size;
    int max_route = MaxRoute(tabela_conversao);
    unsigned char * bits_to_add = (unsigned char *)malloc(sizeof(char)*max_route);
    int bits_to_add_position = 0;
    int i;
    while((read_size = fread(&file_char, 1, 100000, initial_file)) >= 1) {
        while(read_size) {
            total_frequency--;
            binary_route = GetTabelaElement(tabela_conversao, (int)file_char[read_position]);
            converted_binary = GetConvertedBits(binary_route);
            current_route_size = GetElementoTabelaSize(binary_route);
            for(i = 0; current_route_size; ++i, current_route_size--) {
                bits_to_add[i] = converted_binary[i];
            }
            while(converted_binary[bits_to_add_position] != '\0') {
                if(string_file_position == STRING_FILE_SIZE) {
                    string_file_position = 0;
                    PrintBinaryToCharacter(string_file, final_file);
                }
                string_file[string_file_position] = bits_to_add[bits_to_add_position];
                bits_to_add_position++;
                string_file_position++;
            }
            bits_to_add_position = 0;
            if(string_file_position == STRING_FILE_SIZE) {
                string_file_position = 0;
                PrintBinaryToCharacter(string_file, final_file);
            }
            if(!total_frequency) {
                if(string_file_position != 0) {
                    string_file[string_file_position] = '\0';
                    PrintBinaryToCharacter(string_file, final_file);
                }
            }
            read_size--;
            read_position++;
        }
        read_position = 0;
    }
}

void Compress(char * file_to_compress, char * file_created) {

    FILE * file = fopen(file_to_compress, "rb");
    FILE * new_file = fopen(file_created, "wb");
    unsigned int frequencias[256] = {0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao, &percurso);
    rewind(file);
    PrintHeader(frequencias, tree, tabelaConversao, new_file);
    Convert(file, new_file, tabelaConversao, frequencias);
    fclose(file);
    fclose(new_file);
}

void Decompress(char * file_to_decompress, char * decompressed_file) {

    FILE * file = fopen(file_to_decompress, "rb");
    FILE * saida = fopen(decompressed_file, "wb");
    byte * b = (ReadFile(file, 2));
    unsigned char * bits_lixo = GetNBits(b[0], FRENTE, 3);
    int lixo = BinaryToInteger(bits_lixo);
    unsigned char * tamanho_1_tree = GetNBits(b[0],TRAS,5);
    unsigned char * tamanho_2_tree = GetNBits(b[1],FRENTE,8);
    unsigned char * tamanho_tree = ConcatString(tamanho_1_tree, tamanho_2_tree, 13);
    int sizeTree = BinaryToInteger(tamanho_tree);
    int i;
    byte * preorder = ReadFile(file, sizeTree);
    Huff * tree = MakeTreeFromPreOrder(preorder, sizeTree);
    PrintPreOrder(GetHuffHead(tree), NULL);
    byte out;
    Node * atual = GetHuffHead(tree);
    unsigned char buffer[BUFFER_SIZE];
    int tamBuffer;
    while((tamBuffer = fread(buffer, 1, BUFFER_SIZE, file)) >= 1) {
        for(i = 0; i < tamBuffer; i++) {
            int limiterepet = 0;
            if((tamBuffer != BUFFER_SIZE) && ((i+1) == tamBuffer)) {
                limiterepet = lixo;
            }
            int j;
            for(j = 7; j >= limiterepet; j--) {
                atual = NavigateTree(atual, is_bit_i_set(buffer[i], j) == 0 ? 0 : 1);
                if(IsLeaf(atual)) {
                    out = GetNodeC(atual);
                    atual = GetHuffHead(tree);
                    fwrite(&out, 1, sizeof(unsigned char), saida);
                }
            }
        }
    }
    fclose(file);
    fclose(saida);
}