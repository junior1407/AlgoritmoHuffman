#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "inc/tabela.h"
#include "inc/huff.h"
#include "inc/binary.h"
#define FRENTE 1
#define TRAS 0
#define BUFFER_SIZE 2
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


    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    FILE * new_file = fopen("C:\\Users\\Valdir Jr\\Desktop\\saida.txt", "wb");9
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
    FILE * saida = fopen("C:\\Users\\Valdir Jr\\Desktop\\out.txt","wb");
    byte * b = (ReadFile(file,2));  // Array de 2 bytes.
    char * bits_lixo = GetNBits(b[0],FRENTE,8);
    printf("Lixo: %s\n",bits_lixo);
    int lixo = BinaryToInteger(bits_lixo);
    printf("Lixo %d\n",lixo)  ;
    char * tamanho_1_tree = GetNBits(b[0],TRAS,5); // Array de zeros e 1s
    char * tamanho_2_tree = GetNBits(b[1],FRENTE,8); // Array de zeros e 1s
    char * tamanho_tree = ConcatString(tamanho_1_tree,tamanho_2_tree, 13);
    printf("Tamanho tree %s\n", tamanho_tree);
    int sizeTree = BinaryToInteger(tamanho_tree);
    printf("Tamanho tree %d\n", sizeTree);

    // Leitura de Preorder.
    int i;
 //   byte vazio = (byte) 0;
    byte * preorder = ReadFile(file, sizeTree);

    //Huff * tree = MakeTreeFromPreOrder(preorder,sizeTree);
    Huff * tree = NULL;
    byte in; // Byte com seus bits zero.

    byte out = (byte)0;
    byte curr; // Byte A ser Impresso.
    int estado_bit= 7;
    Node * atual = GetHuffHead(tree);
   // while (fread(&in, 1, 1, file) >= 1)
    int x=0;
    rewind(file);
   // Node * atual = GetHuffHead(tree);
    printf("oi\n");
    unsigned char  buffer [BUFFER_SIZE];
    int tamBuffer=-1;
    while (( tamBuffer = fread(buffer, 1, BUFFER_SIZE, file)) >=1)
    {
            printf("Uma leitura %d \n",tamBuffer);
            for (i=0; i< tamBuffer; i++)
            {
                 if ((tamBuffer!=BUFFER_SIZE) && ((i+1) == tamBuffer))
                 {
                   //Estou no last byte.
                     int j;
                     for (j=7; j>=lixo; j--)
                     {

                     }
                 }
                else{

                  /*   do {
                         if (IsLeaf(atual))
                         {
                             out = GetNodeC(atual);
                             atual= GetHuffHead(tree);
                             fwrite(&out , 1 , sizeof(unsigned char) , saida );

                         }
                         atual = NavigateTree(atual, is_bit_i_set(buffer[i], estado_bit) == 0 ? 0 : 1);
                         estado_bit--;
                     }while(estado_bit!=-1);
                     estado_bit=7;*/
                 }



            }


    }
/*
    while (fread(&in, 1, 1, file) == 1)

    {
        if (estado_bit==-1)
        {
            estado_bit=7;
        }
        do {
            if (IsLeaf(atual))
            {
                curr = GetNodeC(atual);
                fwrite(&curr , 1 , sizeof(unsigned char) , saida );
                atual = GetHuffHead(tree);
            }
            atual = NavigateTree(atual, is_bit_i_set(in, estado_bit) == 0 ? 0 : 1);
            estado_bit--;
        }
        while(estado_bit>=0);

    }*/

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