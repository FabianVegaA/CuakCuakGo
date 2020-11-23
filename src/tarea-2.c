#include "graph.h"
#include "display.h"
#include <string.h>

int main(int arg, char *argv[])
{
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("ERROR: File no found");
        exit(1);
    }

    int size;                     // The First is create a variable that save
    fscanf(fin, "%d", &size);     // the size of graph
    Graph *G = CreateGraph(size); // This for iniciality the Graph

    // These values save the information of the file
    char name[MAX_NAME], web[MAX_WEB], last_name[MAX_NAME];
    float prob, weight_edge;
    int amount_neighbor, id_node;
    for (int i = 0;; i++)
    {
        fscanf(fin, "%s %s %f %d", name, web, &prob, &amount_neighbor); // This save the information of the file in the varibles

        if (!strcmp(name, last_name)) // To know when already finish the file is saved the name of the last name
        {                             // and only then finish the process when these names
            break;                    // are equals
        }

        // Save the information in the nodes from the Graph
        G->AdjList[i].id = i;
        G->AdjList[i].prob = prob;
        strcpy(G->AdjList[i].name, name);
        strcpy(G->AdjList[i].web, web);

        for (int j = 0; j < amount_neighbor; j++)                  // This iterates the next nodes in the file saving
        {                                                          // the information in an adjacency matrix
            fscanf(fin, "%d %f", &id_node, &weight_edge);          // where if the value is major a 0
            G->AdjMatrix[G->AdjList[i].id][id_node] = weight_edge; // this value represents an edge to this node
        }                                                          // and this value is the correspondent weight

        strcpy(last_name, name); // Copy the value of the last_name for after compare
    }
    PrintInterfaceConsole(G); // This display of Interface console with the information of the graph

    float probability = Probability(G, GetNode(G, argv[2]), GetNode(G, argv[3]), 0);                                                    // Here is calculating the value of probability
    printf("\nLa probabilidad de visitar %s, iniciando la navegación en %s, es igual a %.2f%%\n", argv[3], argv[2], 100 * probability); // is diplay the information

    FreeGraph(G); // This free the memory
    return 0;
}
