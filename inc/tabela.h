//
// Created by Valdir Jr on 06/04/2017.
//

#ifndef TABELAH
#define TABELAH

typedef struct ElementoTabela ElementoTabela;
typedef struct Tabela Tabela;
typedef struct Linha Linha;
Tabela * CreateTabela();
ElementoTabela * CreateElementoTabela();
Linha * CreateLinha(char i);
void Enqueue(ElementoTabela * elem, char i);
char Dequeue(ElementoTabela * elem);
ElementoTabela * CreateCopiaElemento(Linha * head);
void PrintLinha(Linha * linha);

/*
Tabela:

AABB  =  00100110 10------
Freq * Nº Bits + ... +... =  num % 8 = x - 8 =  lixos.
2 * 3 + 2*2 = 10 % 8 =  2  - 8 =  6 lixos
Elementos 98  (2) -> 1 -> 0
Elementos[97] (3) -> 0 -> 0 -> 1
Elementos[0] -> (Linha)
Elementos[1]  ->  (Linha)
Elementos[2] -> (Linha)
Elementos[3]  -> (linha)
...
Elementos[255] ->Linha
*/
struct Tabela {
    ElementoTabela **elems;  // Array de 256 Posições.
};
struct ElementoTabela {

    int size;
    Linha * front;
    Linha * rear;
};
struct Linha{
    char i;
    Linha * next;
};



#endif //TABELAH
