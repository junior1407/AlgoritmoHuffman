#include <stdlib.h>
#include <stdio.h>
#include "inc/tabela.h"
#include "inc/huff.h"
#include "inc/binary.h"

typedef unsigned char byte;

void GetFrequency(FILE * file, unsigned  int * frequencias){
    byte atual;
    while (fread(&atual, 1, 1, file) >= 1)
    {
        frequencias[atual]++;
    }
    rewind(file);
    return;
}

char * ConcatString(char * str1, char * str2, int new_str_size) {

    char * new_str = (char *)malloc(sizeof(char)*(new_str_size+1));
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

    char * trash = TrashBinary(frequencias, tabela_conversao);
    char * tree_size = TreeSizeBinary(tree);
    char * first_16bits = ConcatString(trash, tree_size, 16);

    PrintBinaryToCharacter(first_16bits, new_file);
    PrintPreOrder(GetHuffHead(tree), new_file);
}

int Compress(){
    FILE  * file = fopen("C:\\Users\\Pedro\\Desktop\\teste.txt","r");
    FILE * new_file = fopen("C:\\Git\\AlgoritmoHuffman\\comp_files\\new_file", "w");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao,&percurso);

    PrintHeader(frequencias, tree, tabelaConversao, new_file);
    //Impressão dos Dados:
    // Fazer Conversando segundo tabela, e imprimindo diretamente no arquivo
    fclose(file);
    return 0;
}
void Decompress()
{
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
    return 0;
}