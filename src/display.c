#include "display.h"

void PrintInterfaceConsole(Graph *G)
{
    for (int i = 0; i < G->num_nodes; i++)
    {
        printf("\nname: %s\nweb: %s\n", G->AdjList[i].name, G->AdjList[i].web);
        for (int j = 0; j < G->num_nodes + 1; j++)
        {
            if (G->AdjMatrix[i][j] > 0)
            {
                printf("--> %s\n", G->AdjList[j].name);
            }
        }
    }
}