#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NAME 50               // This is the
#define MAX_WEB 100               // length of names and web
#define MAX_RECURSIONS 20         // and this saves the maximum value of the number of recursions that the program can
#define CONST_OF_CORRECTION 0.723 // this value corrects the probability

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

float Probability(Graph *G, Node *node_src, Node *node_dest, int recursions);

Node *GetNode(Graph *G, char *name_node);

void FreeGraph(Graph *G);

#endif