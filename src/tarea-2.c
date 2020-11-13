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

    char name[50], web[100], last_name[50];
    float prob, weight_edge;
    int amount_neighbour, id_node;
    for (int i = 0; 1; i++)
    {

        fscanf(fin, "%s %s %f %d", name, web, &prob, &amount_neighbour);

        if (equal_name(name, last_name) != 1)
        {
            G->AdjList[i].id = i;
            strcpy(G->AdjList[i].name, name);
            strcpy(G->AdjList[i].web, web);
            G->AdjList[i].prob = prob;
            printf("<<%s,%s", G->AdjList[i].name, name);

            for (int j = 0; j < amount_neighbour; j++)
            {
                fscanf(fin, "%d %f", &id_node, &weight_edge);
                G->AdjMatrix[G->AdjList[i].id][id_node] = weight_edge;
            }
        }
        else
        {
            break;
        }

        for (int i = 0; i < 50; i++)
        {
            last_name[i] = name[i];
        }
    }
    PrintInterfaceConsole(G);

    Node *node_src = GetNode(G, argv[2]);
    Node *node_des = GetNode(G, argv[3]);
    printf("\nLa probabilidad de visitar %s, iniciando la navegación en %s, es igual a %.2f%%", argv[3], argv[2], (100 * Probability(G, node_src, node_des)));
    return 0;
}
