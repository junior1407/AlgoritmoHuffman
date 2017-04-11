#include <stdlib.h>
#include <stdio.h>

#include "inc/tabela.h"
#include "inc/huff.h"
#include "inc/binary.h"
typedef unsigned char byte;

byte * ReadFile(FILE * file, int numBytes)
{
    byte * array = (byte *) malloc(sizeof(byte)*(numBytes+1));
    int i;
    for (i=0; i<numBytes; i++)
    {
        fread((&(array[i]) ) ,1,1,file);
    }
    array[numBytes]='\0';
    return  array;
}


unsigned char * GetNBits(byte b,  int frente, int n){ // Sempre joga para os n primeiros
    unsigned char * array = (unsigned char *) malloc(sizeof(unsigned char)*(n+1));
    if (frente){
        b = b>>(8-n);
        b= b<<(8-n);}
    else
        b=b<<(8-n);

    int i,j;
    for(i=7,j=0; i>=0;i--,j++)
    {
        if (is_bit_i_set(b,i)==0)
            array[j]='0';
        else
            array[j]='1';
    }
    array[n] = '\0';
    return array;

}

void GetFrequency(FILE * file, unsigned  int * frequencias){
    byte atual;
    while (fread(&atual, 1, 1, file) >= 1)
    {
        frequencias[atual]++;
    }
    rewind(file);
    return;
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

    byte file_char;
    unsigned char * string_file = (unsigned char *)malloc(sizeof(unsigned char)*65);
    string_file[64] = '\0';
    int string_file_position = 0;
    int total_frequency = TotalFrequency(frequencias);
    ElementoTabela * binary_route;
    unsigned char * converted_binary;
    int current_route_size;
    int max_route = MaxRoute(tabela_conversao);
    unsigned char * bits_to_add = (unsigned char *)malloc(sizeof(char)*max_route);
    int bits_to_add_position = 0;
    int i;
    while(fread(&file_char, 1, 1, initial_file) >= 1) {
        total_frequency--;
        binary_route = GetTabelaElement(tabela_conversao, (int)file_char);
        converted_binary = GetConvertedBits(binary_route);
        current_route_size = GetElementoTabelaSize(binary_route);
        for(i = 0; current_route_size; ++i, current_route_size--) {
            bits_to_add[i] = converted_binary[i];
        }
        while(converted_binary[bits_to_add_position] != '\0') {
            if(string_file_position == 64) {
                string_file_position = 0;
                PrintBinaryToCharacter(string_file, final_file);
            }
            string_file[string_file_position] = bits_to_add[bits_to_add_position];
            bits_to_add_position++;
            string_file_position++;
        }
        bits_to_add_position = 0;
        if(string_file_position == 64) {
            string_file_position = 0;
            PrintBinaryToCharacter(string_file, final_file);
        }
        if(!total_frequency) {
            if(string_file_position != 0) {
                string_file[string_file_position] = '\0';
                PrintBinaryToCharacter(string_file, final_file);
            }
        }
    }
}

int Compress(){
    FILE  * file = fopen("C:\\Users\\Pedro\\Desktop\\teste.txt","rb");
    FILE * new_file = fopen("C:\\Git\\AlgoritmoHuffman\\comp_files\\new_file", "w");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao,&percurso);
    rewind(file);
    PrintHeader(frequencias, tree, tabelaConversao, new_file);
    Convert(file, new_file, tabelaConversao, frequencias);
    fclose(file);
    fclose(new_file);
    return 0;
}
void Decompress()
{
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    byte * b = (ReadFile(file,2));
    int lixo = BinaryToInteger(GetNBits(b[0],1,3));
    unsigned char * tamanho_1 = GetNBits(b[0],0,5);
    unsigned char * tamanho_2 = GetNBits(b[1],1,8);
    printf("tamanho 1: %s e tamanho 2 %s\n",tamanho_1,tamanho_2);
    printf("Lixo %d",lixo)  ;
    fclose(file);

    // Ler Cabecalho.
    // MakeTree a partir da Preorder.
    //
    //
    //
    //

}

int main()
{
    Compress();
    //Decompress();
    return 0;
}