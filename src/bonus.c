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

    float probability = ProbabilityKnapsack(G, GetNode(G, argv[2]), GetNode(G, argv[3]));
    printf("\nLa probabilidad de visitar %s, iniciando la navegación en %s, es igual a %.2f%%\n", argv[3], argv[2], 100 * probability);

    display();
    

    return 0;
}

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest)
{
    dummyItem = (DataItem *)malloc(sizeof(DataItem));
    dummyItem->data = -1;
    dummyItem->key1 = -1;
    dummyItem->key1 = -1;


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

    float prob = 0.0, probability;

    for (int i = 0; i < G->num_nodes; i++)
    {
        if (G->AdjMatrix[node_src->id][i] > 0)
        {
            if (visited[i] == 0)
            {
                if (search(i, node_dest->id) != NULL)
                {
                    probability = search(i, node_dest->id)->data;
                }
                else
                {
                    probability = Probability(G, &G->AdjList[i], node_dest);
                    insert(i, node_dest->id, probability);
                }

                probability = Probability(G, &G->AdjList[i], node_dest);
                prob = prob + node_src->prob * G->AdjMatrix[node_src->id][i] * probability;
            }
        }
    }

    visited[node_src->id] = 0;

    return prob;
}

int hashCode(int key1, int key2)
{
    return (int)(pow(key1,4) + pow(key2,4)) % SIZE;
}

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

void insert(int key1, int key2, int data)
{

    DataItem *item = (DataItem *)malloc(sizeof(DataItem));
    item->data = data;
    item->key1 = key1;
    item->key2 = key2;

    //get the hash
    int hashIndex = hashCode(key1,key2);
    

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key1 != -1 && hashArray[hashIndex]->key2 != -1)
    {
        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

void display()
{
    int i = 0;

    for (i = 0; i < SIZE; i++)
    {

        if (hashArray[i] != NULL)
            printf(" ((%d,%d),%f)", hashArray[i]->key1, hashArray[i]->key2, hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}
