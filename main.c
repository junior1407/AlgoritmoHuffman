#include <stdio.h>
#include "inc/huff.h"
#include "inc/tabela.h"
typedef unsigned char byte;

int is_bit_i_set(byte c, int i)
{
    byte mask = 1 << i;
    return mask & c;
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
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\v2.jpg","rb");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);

    Huff * tree = MakeTree(frequencias);


   PrintPreOrder(getTreeHead(tree));
    Tabela * tabelaConversao = CreateTabela();


    ElementoTabela * percurso = CreateElementoTabela();
    GeraTabelaConversao(getTreeHead(tree), &tabelaConversao,&percurso);
    /*int i;
    int maior = 0;
    int soma=0;
    int somaTotal=0;

    for (i=0; i< 256;i++)
    {
       soma +=  frequencias[i] * tabelaConversao->elems[i]->size;
       somaTotal +=  frequencias[i] *8;
    }
    printf("\nSoma Total: %dbits %dbytes\nSoma normal:%dbits %dbytes",somaTotal,somaTotal/8,soma,soma/8);
    printf("\nForam economizados %dbits %dbytes",somaTotal-soma,(somaTotal-soma)/8);
   // printf("\nFrequencias de MAIOR: %d\n Codigo: ",frequencias[maior]);*/
   // PrintLinha(tabelaConversao->elems[maior]->front);
   // printf("\nFrequencia a %d", tabelaConversao->elems[66]->size);
    /*
    printf("\nSize:");
    printf("%d",tabelaConversao->elems['E']->size);
    printf("\n");
    PrintLinha( tabelaConversao->elems['E']->front);*/


    //Criação do Cabeçalho:
    //1º Cálculo LIxo. 401 bits % 8 = 1 bits,  8 -1 = 7 bits de lixo.  (IMPRIMIR NO ARQUIVO)
    //2º Converte Inteiro para Binário. retorna char [3]
    //3º Função Percorre Arvore contando nós. Converter para binário em 13 bits
    // IMPRIME PREOREDER


    //Impressão dos Dados:
    // Fazer Conversando segundo tabela, e imprimindo diretamente no arquivo.


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