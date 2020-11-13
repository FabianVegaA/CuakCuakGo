#include "graph.h"

Graph *CreateGraph(int num_nodes)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));

    G->num_nodes = num_nodes;

    G->AdjList = (Node *)malloc(num_nodes * sizeof(Node));

    G->AdjMatrix = (float **)malloc(num_nodes * sizeof(float *));
    for (int i = 0; i < num_nodes; i++)
    {
        G->AdjMatrix[i] = (float *)malloc(num_nodes * sizeof(float));
    }
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            G->AdjMatrix[i][j] = 0.0;
        }
    }

    return G;
}

void PrintGraPh(Graph *G)
{
    for (int i = 0; i < G->num_nodes; i++)
    {
        for (int j = 0; j < G->num_nodes; j++)
        {
            printf("%f ", G->AdjMatrix[i][j]);
        }
        printf("\n");
    }
}

float Probability(Graph *G, Node *node_src, Node *node_dest)
{
    if (node_src == NULL || node_dest == NULL)
    {
        printf("ERROR: There is a node NULL\n");
        exit(1);
    }

    if (node_src->id == node_dest->id)
    {
        return 1.0;
    }

    char *visited = malloc(G->num_nodes * sizeof(char));
    for (int i = 0; i < G->num_nodes; i++)
    {
        visited[i] = 0;
    }

    visited[node_src->id] = 1;

    float prob = 0.0;

    for (int i = 0; i < G->num_nodes; i++)
    {
        if (G->AdjMatrix[node_src->id][i] > 0)
        {
            if (visited[i] == 0)
            {
                prob = prob + node_src->prob * G->AdjMatrix[node_src->id][i] * Probability(G, &G->AdjList[i], node_dest);
            }
        }
    }

    visited[node_src->id];

    return prob;
}

char equal_name(char *C1, char *C2)
{
    for (int i = 0; i < strlen(C1) || i < strlen(C2); i++)
    {
        if (C1[i] != C2[i])
        {
            return 0;
        }
    }
    return 1;
}

Node *GetNode(Graph *G, char *name_node)
{

    for (int i = 0; i < G->num_nodes; i++)
    {
        if (equal_name(G->AdjList[i].name, name_node) == 1)
        {
            return &G->AdjList[i];
        }
    }
    printf("ERROR: The node %s there is not in the graph\n", name_node);
    return NULL;
}