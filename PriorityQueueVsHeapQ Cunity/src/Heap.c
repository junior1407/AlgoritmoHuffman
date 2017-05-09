//
// Created by Valdir Jr on 06/05/2017.
//

#include "../inc/Heap.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 100001

struct Heap {
    int size;
    int data[MAXSIZE];
};

void swap(int * a, int * b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
Heap * CreateHeap() {
    Heap * newHeap = (Heap*)malloc(sizeof(Heap)) ;
    newHeap->size = 0;
    return newHeap;
}
int HEnqueue(Heap * heap, int priority) {
    int cont = 0;
    if (heap->size >= MAXSIZE) {
        printf("Heap Overflow");
        return 0;
    } else {
        heap->size++;
        heap->data[heap->size] = priority;
        int keyIndex = heap->size;
        int parentIndex = heap->size / 2;
        while ((parentIndex != 0) && (heap->data[parentIndex] < heap->data[keyIndex])) {
            cont++;
            swap(&heap->data[keyIndex], &heap->data[parentIndex]);
            keyIndex = parentIndex;
            parentIndex = keyIndex / 2;
        }
        return cont;
    }
}
void PrintHeap(Heap * heap)
{
        int i;
        for (i=1; i <= heap->size;i++)
        {
            printf("%d-",heap->data[i]);
        }

}

void MaxHeapify(Heap *heap, int i)
{
    int largest;
    int left_index = 2 * i;
    int right_index = 2 * i + 1;
    if (left_index <= heap->size && heap->data[left_index] > heap->data[i]) {
        largest = left_index;
    } else {
        largest = i;
    }
    if (right_index <= heap->size && heap->data[right_index] > heap->data[largest]) {
        largest = right_index;
    }
    if (heap->data[i] != heap->data[largest]) {
        swap(&heap->data[i], &heap->data[largest]);
        MaxHeapify(heap, largest);
    }
}

int HDequeue(Heap * heap) {
    if(heap->size <= 0) {
        printf("Heap Underflow");
        return -1;
    } else {
        int item = heap->data[1];
        heap->data[1] = heap->data[heap->size--];
        MaxHeapify(heap, 1);
        return item;
    }
}

void MakeHeap(Heap * heap) {
    int x;
    while(scanf("%d", &x) != EOF) {
        printf("%d;%d;HEAP\n", heap->size - 1, HEnqueue(heap, x));
    }
}

int GetHeapSize(Heap * heap)
{
    return heap->size;
}