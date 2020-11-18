#include "tarea-2.h"
#include "graph.h"

void PrintList(Graph *G)
{
    for (int i = 0; i < G->num_nodes; i++)
    {
        printf(" (%i, %s, %s, %p) \n", G->AdjList[i].id, G->AdjList[i].name, G->AdjList[i].web, &G->AdjList[i]);
    }
    printf("\n");
}

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

int main(int arg, char *argv[])
{
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("ERROR: File no found");
        exit(1);
    }

    int size;
    fscanf(fin, "%d", &size);
    Graph *G = CreateGraph(size);

    char name[MAX_NAME], web[MAX_WEB], last_name[MAX_NAME];
    float prob, weight_edge;
    int amount_neighbor, id_node;
    for (int i = 0;; i++)
    {
        fscanf(fin, "%s %s %f %d", name, web, &prob, &amount_neighbor);

        if (!strcmp(name, last_name))
        {
            break;
        }

        G->AdjList[i].id = i;
        G->AdjList[i].prob = prob;
        strcpy(G->AdjList[i].name, name);
        strcpy(G->AdjList[i].web, web);
        

        for (int j = 0; j < amount_neighbor; j++)
        {
            fscanf(fin, "%d %f", &id_node, &weight_edge);
            G->AdjMatrix[G->AdjList[i].id][id_node] = weight_edge;
        }

        strcpy(last_name, name);

    }
    PrintInterfaceConsole(G);

    float probability = Probability(G, GetNode(G, argv[2]), GetNode(G, argv[3]));
    printf("\nLa probabilidad de visitar %s, iniciando la navegación en %s, es igual a %.2f%%", argv[3], argv[2], 100 * probability);
    return 0;
}
