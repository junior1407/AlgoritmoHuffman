#include <stdio.h>
#include <stdlib.h>
#include "inc/huff.h"
#include "inc/tabela.h"
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




int Compress(){
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao,&percurso);
    rewind(file);
    FILE * novo = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.huff","w+b");
    unsigned char in;
    unsigned char out;
    //int lixo;
    Linha * atual;
    int estado_bit=7;
    while (fread(&in, 1, 1, file) >= 1)
    {
        ElementoTabela * codificacao = GetTabelaElement(tabelaConversao, in);
        while (GetElementoTabelaSize(codificacao)>=1)
        {
            atual = PopFrontElementoTabela(codificacao);
            set_bit(out, estado_bit);
            estado_bit--;
            if (estado_bit==-1)
            {
                fwrite(out,1,1,novo);

            }
            //Condição recriar bit.

        }

    }





    //Criação do Cabeçalho:
    //1º Cálculo LIxo. 401 bits % 8 = 1 bits,  8 -1 = 7 bits de lixo.  (IMPRIMIR NO ARQUIVO)
    //2º Converte Inteiro para Binário. retorna char [3]
    //3º Função Percorre Arvore contando nós. Converter para binário em 13 bits
    // IMPRIME PREOREDER
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
    //Compress();
    //Decompress();
    return 0;
}