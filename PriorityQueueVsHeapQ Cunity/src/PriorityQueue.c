//
// Created by Valdir Jr on 03/05/2017.
//

#include "../inc/PriorityQueue.h"
#include <limits.h>

struct PriorityQueue {

    int size;
    struct Node * head;
};
struct Node{
    int data;
    int priority;
    Node * next;
};
PQueue * NewPQueue()
{
    PQueue * newPQueue= (PQueue*)malloc(sizeof(PQueue));
    newPQueue->size=0;
    newPQueue->head=NULL;
}
Node * NewNode(int data, int priority)
{
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    newNode->priority= priority;
}

int Dequeue(PQueue * pq)
{
    if (pq->size==0)
    {
        return INT_MIN;
    }
    int data = pq->head->data;
    pq->head = pq->head->next;
    (pq->size)--;
    return data;
}
int Enqueue(PQueue * pq , int data, int priority)
{
    int comparacoes=0;
    Node * new = NewNode(data,priority);
    if (pq->size==0)
    {
        pq->head = new;
        (pq->size)++;
        return comparacoes;
    }
    comparacoes++;
    if (pq->head->priority < priority)
    {
        new->next=pq->head;
        pq->head=new;
        (pq->size)++;
        return comparacoes;
    }
    else
    {
        Node * atual = pq->head;
        while(atual!=NULL)
        {
            comparacoes++;
            if (atual->next==NULL){comparacoes--;}
            if ((atual->next==NULL) || ( atual->next->priority  <  priority))
            {
                new->next= atual->next;
                atual->next= new;
                (pq->size)++;
                return  comparacoes;
            }
            atual=atual->next;
        }
    }

}

int GetPQueueSize(PQueue * pq)
{
    return pq->size;
}
void CleanPQueue(PQueue * pq)
{
    while(pq->size!=0)
    {
        Dequeue(pq);
    }
}