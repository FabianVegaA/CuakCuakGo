#include "bonus.h"

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

    float probability = ProbabilityKnapsack(G, GetNode(G, argv[2]), GetNode(G, argv[3]), 0);
    if (warning_recursions > 0) // When an operation arrives the maximum among the recursions
    {                           // this delivery a warning
        printf("\nWARNING: Maximum recursions have been reached");
        printf("\n\tThe probability only will be an approximation\n");
    }
    printf("\nLa probabilidad de visitar %s, iniciando la navegación en %s, es igual a %.2f%%\n", argv[3], argv[2], 100 * probability);
    FreeGraph(G);
    FreeHashTable();
    return 0;
}

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest, int recursions)
{
    dummyItem = (DataItem *)malloc(sizeof(DataItem)); // Request the momery for dummyItem
    dummyItem->data = -1;                             // This is saved with values uniques
    dummyItem->key1 = -1;                             // for these nodes
    dummyItem->key1 = -1;                             // in the hash table

    if (node_src == NULL || node_dest == NULL) // This verifies if two nodes are of the same
    {
        printf("ERROR: There is a node NULL\n");
        exit(1);
    }

    if (node_src->id == node_dest->id)
    {
        return 1.0;
    }

    char *visited = malloc(G->num_nodes * sizeof(char)); // Request memory for the list visited
    for (int i = 0; i < G->num_nodes; i++)               // and initializes the values
    {                                                    // with zeros
        visited[i] = 0;
    }

    visited[node_src->id] = 1;

    float prob = 0.0, probability;

    for (int i = 0; i < G->num_nodes; i++)
    {
        if (G->AdjMatrix[node_src->id][i] > 0) // This filter the neighbour nodes
        {
            if (visited[i] == 0)
            {

                if (isInHashTable(i, node_dest->id) != 0) // If the value of these two nodes is in the hash
                {                                         // table it does not calculate them again
                    probability = search(i, node_dest->id)->data;
                }
                else
                {
                    if (recursions >= MAX_RECURSIONS_BONUS)                                                 // When arriving at the MAX_RECURSIONS_BONUS
                    {                                                                                       // is stopped the process
                        warning_recursions = 1;                                                             // activate this value for it show after a warning
                        prob = prob + node_src->prob * G->AdjMatrix[node_src->id][i] * CONST_OF_CORRECTION; // and calculate the value  without call again the function
                        insert(i, node_dest->id, probability);                                              // save the value
                        return prob;                                                                        // and return this probability
                    }
                    else
                    {
                        probability = ProbabilityKnapsack(G, &G->AdjList[i], node_dest, ++recursions);
                        insert(i, node_dest->id, probability);
                    }
                }

                prob = prob + node_src->prob * G->AdjMatrix[node_src->id][i] * probability;
            }
        }
    }

    visited[node_src->id] = 0;
    free(visited);
    return prob;
}

int hashCode(int key1, int key2)                      // This hash funtion is manage
{                                                     // of give a position in the hash table
    return (int)(pow(key1, 3) / pow(key2, 2)) % SIZE; // for this in this is calculate a value
} // with a non-commutative operation

DataItem *search(int key1, int key2)
{
    int hashIndex = hashCode(key1, key2);

    while (hashArray[hashIndex] != NULL)
    {
        if (hashArray[hashIndex]->key1 == key1 && hashArray[hashIndex]->key2 == key2)
        {
            return hashArray[hashIndex];
        }

        ++hashIndex;

        hashIndex %= SIZE;
    }
    return NULL;
}

char isInHashTable(int key1, int key2)
{
    int hashIndex = hashCode(key1, key2);

    while (hashArray[hashIndex] != NULL)
    {
        if (hashArray[hashIndex]->key1 == key1 && hashArray[hashIndex]->key2 == key2)
        {
            return 1;
        }

        ++hashIndex;

        hashIndex %= SIZE;
    }
    return 0;
}

void insert(int key1, int key2, int data)
{
    if (search(key1, key2) == NULL) // Only if this Item is not in the hash table is saved
    {
        DataItem *item = (DataItem *)malloc(sizeof(DataItem));
        item->data = data;
        item->key1 = key1;
        item->key2 = key2;

        int hashIndex = hashCode(key1, key2);

        while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key1 != -1 && hashArray[hashIndex]->key2 != -1) // Check if the memory is ocupate
        {                                                                                                            // if so, move a position

            ++hashIndex;

            hashIndex %= SIZE;
        }

        hashArray[hashIndex] = item; // When found a position save the Item
    }
}

void FreeHashTable()
{
    free(dummyItem);
    for (int i = 0; i < SIZE; i++)
    {
        free(hashArray[i]);
    }
}
