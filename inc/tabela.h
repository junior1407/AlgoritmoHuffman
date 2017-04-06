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
struct Tabela {
    ElementoTabela **elems;
};
struct ElementoTabela {

    int size;
    Linha * front;
    Linha * rear;
};
struct Linha{ //Estrutura de Stack, sendo adicionado sempre ao topo.
    char i;
    Linha * next;
};



#endif //TABELAH
