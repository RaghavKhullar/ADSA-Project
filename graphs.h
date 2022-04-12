#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>
using namespace std;

//node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode *next;
};

//list gives all the nodes connected to a particular vertex
struct AdjList
{
    struct AdjListNode *head;
};


//geaph is an array of all adjacency lists, size =no of vertices
struct Graph
{
    int V;
    struct AdjList *array;
};

//create new adjacency list node
struct AdjListNode *newAdjListNode(
    int dest, int weight)
{
    struct AdjListNode *newNode =
        (struct AdjListNode *)
            malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//create a graph
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)
        malloc(sizeof(struct Graph));
    graph->V = V;

   //creating array, each element will represent an Adjacency List
    graph->array = (struct AdjList *)
        malloc(V * sizeof(struct AdjList));

    //initially all list empty
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

//adding edge to undirected graphs
void addEdge(struct Graph *graph, int src,
             int dest, int weight)
{
    //for adding an edge from src to dest, add a node in src with dest(weight of edge given) at the beginning
    struct AdjListNode *newNode =
        newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    //undirected graph, so similarly one from dest to src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}