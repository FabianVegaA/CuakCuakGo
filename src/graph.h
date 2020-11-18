#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_WEB 100

typedef struct
{
    int id;
    char name[MAX_NAME];
    char web[MAX_WEB];
    float prob;
} Node;

typedef struct
{
    int num_nodes;
    Node *AdjList;
    float **AdjMatrix;
} Graph;

Graph *CreateGraph(int num_nodes);

void PrintGraPh(Graph *G);

float Probability(Graph *G, Node *node_src, Node *node_dest);

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest);

float knapsack(Graph *G, Node *node_src, Node *node_dest);

Node *GetNode(Graph *G, char *name_node);

char equal_name(char *C1, char *C2);

#endif