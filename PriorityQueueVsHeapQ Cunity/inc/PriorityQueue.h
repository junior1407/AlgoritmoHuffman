//
// Created by Valdir Jr on 03/05/2017.
//

#ifndef PRIORITYQUEUEVSHEAPQ_PRIORITYQUEUE_H
#define PRIORITYQUEUEVSHEAPQ_PRIORITYQUEUE_H

#include <stdlib.h>
#include <stdio.h>
typedef struct PriorityQueue PQueue;

/*
 * Data Structure for Priority Queue
 */
typedef struct Node Node;

/*
 * Creates an empty Huffman Tree.
 */
PQueue * NewPQueue();
int Dequeue(PQueue * pq);
Node * NewNode(int data, int priority);
int Enqueue(PQueue * pq , int data, int priority);
int GetPQueueSize(PQueue* pq);

void CleanPQueue(PQueue * pq);

#endif //PRIORITYQUEUEVSHEAPQ_PRIORITYQUEUE_H
