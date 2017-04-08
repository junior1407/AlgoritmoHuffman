#include <stdio.h>
#include "inc/huff.h"
#include "inc/tabela.h"
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

int Compress(){
    FILE  * file = fopen("C:\\Users\\Valdir Jr\\Desktop\\a.txt","rb");
    int unsigned frequencias[256]={0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    ElementoTabela * percurso = CreateElementoTabela();
    CreatesConversionTable(GetHuffHead(tree), &tabelaConversao,&percurso);
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