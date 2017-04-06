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
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    PrintPreOrder(tree->head);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso= CreateElementoTabela();
    GeraTabelaConversao(tree->head, &tabelaConversao,&percurso);
    printf("\nSize:");
    printf("%d",tabelaConversao->elems['E']->size);
    printf("\n");
    PrintLinha( tabelaConversao->elems['E']->front);
    // Cabecalho: 3 bits : Lixo. 13bits - nº Nos da Arvore.

    // Calcula número de bits necessários. Todos(Freq * Nº Bits). % 8
    // Deduz quantidade de lixo. IMprime no arquvio.


    // Conta nº de nós.
    // Imprime no arquivo

    //Imprime-PreOrder No arquivo

    //Fazer conversão segundo tabela lendo novamento do arquivo.



    fclose(file);
    return 0;

}

int main()
{
    Compress();
    return 0;
}