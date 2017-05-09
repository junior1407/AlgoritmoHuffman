//
// Created by Valdir Jr on 06/05/2017.
//

#ifndef PRIORITYQUEUEVSHEAPQ_HEAP_H
#define PRIORITYQUEUEVSHEAPQ_HEAP_H

typedef struct Heap Heap;
void swap(int * a, int * b);
Heap * CreateHeap();
int HEnqueue(Heap * heap, int item);
void PrintHeap(Heap * heap);
void MaxHeapify(Heap *heap, int i);

// Remove o primeiro valor da Heap
int HDequeue(Heap * heap);

// Cria a Heap e retorna os dados necessários para o gráfico
void MakeHeap(Heap * heap);

int GetHeapSize(Heap * heap);
#endif //PRIORITYQUEUEVSHEAPQ_HEAP_H
