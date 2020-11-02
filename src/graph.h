#ifdef GRAPH_H
#define GRAPH_H

typedef struct
{
    int id;     // Number identify, unique for each node
    float prob; // Probability of that a user does not finish on this node
} Node;

typedef struct
{
    int num_nodes;
    Node *nodes;
} Graph;

Graph *init_graph();

float Probability(Graph *G, char *nodo_1, char *nodo_2);

#endif /* GRAPH_H */