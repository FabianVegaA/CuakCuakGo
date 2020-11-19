#ifndef KNAPSACK_H
#define KNAPSACK_H
#define SIZE 20

#include "graph.h"
#include "display.h"
#include<math.h>


typedef struct
{
    float data;
    int key1, key2;
} DataItem;

DataItem *hashArray[SIZE];
DataItem *dummyItem;
DataItem *item;

int hashCode(int key1, int key2);

DataItem *search(int key1, int key2);

void insert(int key1, int key2, int data);

void display();

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest);

float knapsack(Graph *G, Node *node_src, Node *node_dest);

#endif