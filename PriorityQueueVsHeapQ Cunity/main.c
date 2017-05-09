#include <stdio.h>
#include "inc/Heap.h"
#include "inc/PriorityQueue.h"

int main() {
    PQueue * pq = NewPQueue();
    Heap * heap = CreateHeap();
    FILE * output_heap = fopen("saidaheap.csv","w");
    FILE * output_pqueue= fopen("saidapqueue.csv","w");
    if (output_heap == NULL)
    {
        printf("Erro ao abrir arquivo heap\n");
    }
    if (output_pqueue == NULL)
    {
        printf("Erro ao abrir arquivo Pqueue\n");
    }
    int numero;
    fprintf(output_heap,"size,comparisons\n");
    fprintf(output_pqueue,"size,comparisons\n");
    int contador=0;
    int i;


    for (i=0; i< 501; i++)
    {
        numero = (4* (rand()%501) + 3* (rand()%501) + 2* (rand()%501)+ (rand()%501))/10;
        fprintf(output_heap, "%d,%d\n", contador,HEnqueue(heap,numero));
        fprintf(output_pqueue, "%d,%d\n", contador,Enqueue(pq,0,numero));
        contador++;
    }

    fclose(output_heap);
    fclose(output_pqueue);
    return 0;
}
