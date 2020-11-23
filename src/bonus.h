#ifndef KNAPSACK_H
#define KNAPSACK_H

#define SIZE 20
#define MAX_RECURSIONS_BONUS 100

#include "graph.h"
#include "display.h"
#include <math.h>

char warning_recursions = 0;

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

char isInHashTable(int key1, int key2);

void insert(int key1, int key2, int data);

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest, int recursions);

void FreeHashTable();

#endif