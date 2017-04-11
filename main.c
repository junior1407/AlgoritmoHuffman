#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


char * GetNBits(byte b,  int frente, int n){ // Sempre joga para os n primeiros
    char * array = (char *) malloc(sizeof(char)*(n+1));
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
    FILE  * file = fopen("C:\\Users\\HP\\Desktop\\Trabson\\AlgoritmoHuffman\\comp_files\\teste.txt","rb");
    //FILE * new_file = fopen("C:\\Users\\HP\\Desktop\\Trabson\\AlgoritmoHuffman\\comp_files\\new_file.txt", "wb");
    unsigned char new_file[500] = "";
    unsigned char has[500] = "";
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao,&percurso);
    rewind(file);
    PrintPreOrder(GetHuffHead(tree), new_file);
    printf("%s", new_file);
    printf("\n");
    Huff * huff = MakeTreeFromPreOrder(new_file, 5);
    PrintPreOrder(GetHuffHead(huff), has);
    printf("%s", has);

    //PrintHeader(frequencias, tree, tabelaConversao, new_file);
    //Impressão dos Dados:
    // Fazer Conversando segundo tabela, e imprimindo diretamente no arquivo
    fclose(file);
    return 0;
}
void Decompress()
{
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    byte * b = (ReadFile(file,2));
    int lixo = BinaryToInteger(GetNBits(b[0],1,3));
    char * tamanho_1 = GetNBits(b[0],0,5);
    char * tamanho_2 = GetNBits(b[1],1,8);
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