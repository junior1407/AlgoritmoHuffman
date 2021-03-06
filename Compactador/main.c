#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inc/tabela.h"
#include "inc/huff.h"
#include "inc/binary.h"
#define FRENTE 1
#define TRAS 0
#define BUFFER_SIZE 1024

typedef unsigned char byte;

byte * ReadFile(FILE * file, int numBytes);
unsigned char * GetNBits(byte b,  int frente, int n);
void GetFrequency(FILE * file, long long int * frequencias);
unsigned char * ConcatString(unsigned char * str1, unsigned char * str2, int new_str_size);
void PrintHeader(long long int * frequencias, Huff * tree, Tabela * tabela_conversao, FILE * new_file);
void Convert(FILE * initial_file, FILE * final_file, Tabela * tabela_conversao, long long int * frequencias);
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

    unsigned char * array = (unsigned char *)malloc(sizeof(unsigned char)*(9));
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

void GetFrequency(FILE * file, long long int * frequencias) {

    byte atual[BUFFER_SIZE];
    int read_size;
    int i;
    while((read_size = fread(&atual, 1, BUFFER_SIZE, file)) >= 1) {
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

void PrintHeader(long long int * frequencias, Huff * tree, Tabela * tabela_conversao, FILE * new_file) {
    unsigned char * trash = TrashBinary(frequencias, tabela_conversao);
    unsigned char * tree_size = TreeSizeBinary(tree);
    unsigned char * first_16bits = ConcatString(trash, tree_size, 16);
    byte out='\0';
    int i;
    int pos_bit = 7;
    for (i=0; i< 17; i++)
    {
        if (pos_bit == -1) {
            fwrite(&out, 1, sizeof(unsigned char),new_file);
            pos_bit = 7;
            out = '\0';
        }
        if ((first_16bits[i] - '0') == 1) {
            out = set_bit(out, pos_bit);
        }
        pos_bit--;
    }
    PrintPreOrder(GetHuffHead(tree), new_file);
}

void Convert(FILE * initial_file, FILE * final_file, Tabela * tabela_conversao, long long int * frequencias) {
    byte out ='\0';
    int i;
    unsigned char buffer[BUFFER_SIZE];
    int tamBuffer;
    int posicao_bit = 7;
    while((tamBuffer = fread(buffer, 1, BUFFER_SIZE, initial_file)) >= 1) {
        for (i = 0; i < tamBuffer; i++) {
            Percurso *path = GetTabelaElement(tabela_conversao, buffer[i]);
            Linha *iterador = GetPercursoFront(path);
            while (iterador != NULL) {  // Itera a codificação do byte atual.
                if (posicao_bit == -1) {   // Se já tiver preenchido bit full, escreva, resete a posicao dos bits.
                    fwrite(&out, 1, sizeof(unsigned char), final_file);
                    posicao_bit = 7;
                    out = '\0';
                }
                if ((GetLinhaI(iterador) - '0') == 1) {  // Se pos_percurso atual == 1, sete o bit pra 1.
                    out = set_bit(out, posicao_bit);
                }
                posicao_bit--;
                iterador = GetLinhaNext(iterador);
            }
        }
    }
        if (posicao_bit!=7)
        {
            fwrite(&out, 1, sizeof(unsigned char), final_file);
        }
    }




void Compress(char * file_to_compress, char * file_created) {

    FILE * file = fopen(file_to_compress, "rb");
    FILE * new_file = fopen(file_created, "wb");
    long long int frequencias[256] = {0};
    GetFrequency(file, frequencias);
    Huff * tree = MakeTree(frequencias);
    Tabela * tabelaConversao = CreateTabela();
    Percurso * percurso = CreatePercurso();
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
    printf("%s-%s",tamanho_1_tree,tamanho_2_tree);
    unsigned char * tamanho_tree = ConcatString(tamanho_1_tree, tamanho_2_tree, 13);
    int sizeTree = BinaryToInteger(tamanho_tree);
    int i;
    byte * preorder = ReadFile(file, sizeTree);
    Huff * tree = MakeTreeFromPreOrder(preorder, sizeTree);
    byte out;
    Node * atual = GetHuffHead(tree);
    unsigned char buffer[BUFFER_SIZE];
    int tamBuffer;
    while((tamBuffer = fread(buffer, 1, BUFFER_SIZE, file)) >= 1) {
        for(i = 0; i < tamBuffer; i++) { // Itera entre bytes.
            int limiterepet = 0;
            if((tamBuffer != BUFFER_SIZE) && ((i+1) == tamBuffer)) { // Ultimo byte da leitura incompleta.
                limiterepet = lixo;
            }
            int j;
            for(j = 7; j >= limiterepet; j--) { // Itera bits
                atual = NavigateTree(atual, is_bit_i_set(buffer[i], j) == 0 ? 0 : 1);
                if(IsLeaf(atual)) {
                    out = GetNodeC(atual);
                    fwrite(&out, 1, sizeof(unsigned char), saida);
                    atual = GetHuffHead(tree);
                }
            }
        }
    }
    fclose(file);
    fclose(saida);
}