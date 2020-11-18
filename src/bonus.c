#include "graph.h"
#include "bonus.h"

float ProbabilityKnapsack(Graph *G, Node *node_src, Node *node_dest)
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

    float prob = 0.0, probability;

    for (int i = 0; i < G->num_nodes; i++)
    {
        if (G->AdjMatrix[node_src->id][i] > 0)
        {
            if (visited[i] == 0)
            {
                probability = Probability(G, &G->AdjList[i], node_dest);
                prob = prob + node_src->prob * G->AdjMatrix[node_src->id][i] * probability;
            }
        }
    }

    visited[node_src->id];

    return prob;
}

int hashCode(int key)
{
    return key % SIZE;
}

DataItem *search(int key)
{
    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != NULL)
    {
        if (hashArray[hashIndex]->key == key)
        {
            return hashArray[hashIndex];
        }

        ++hashIndex;

        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(int key, int data)
{

    DataItem *item = (DataItem *)malloc(sizeof(DataItem));
    item->data = data;
    item->key = key;

    //get the hash
    int hashIndex = hashCode(key);

    //move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
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
            printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
        else
            printf(" ~~ ");
    }

    printf("\n");
}

int main()
{
    dummyItem = (DataItem *)malloc(sizeof(DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(4, 25);

    display();
    printf("%i", search(42)->data);
    return 0;
}