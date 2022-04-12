#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
#include "fibonacciHeaps.h"
using namespace std;


void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(struct Graph *graph, int src)
{

    // Get the number of vertices in graph
    int V = graph->V;

    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];
    node *nodes[V];
    // minHeap represents set E
   

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] =INT_MAX;
        if(v==src){
            dist[v] =0;
        }
        nodes[v]=insertion(v, dist[v]);
    }
no_of_nodes=8;
    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (no_of_nodes!=0)
    {
            
        // Extract the vertex with
        // minimum distance value
        struct node *minHeapNode =mini;
            Extract_min();
    
        // Store the extracted vertex number
        int u = minHeapNode->key;
       
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        struct AdjListNode *pCrawl =
            graph->array[u].head;
            
        while (pCrawl != NULL)
        { 
            int v = pCrawl->dest;
           
            // cout<<v<<" "<<isInMinHeap(v,dist)<<endl;
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance

            if (
                dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v])
            {   
                // cout<<"hello"<<endl;

                Find(nodes[v], dist[v], dist[u] + pCrawl->weight);
                dist[v] = dist[u] + pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    // print the calculated shortest distances
    printArr(dist, V);
    // cout<<"Raghav";
}



// Driver code
int main()
{
	int V = 9;
    struct Graph *graph = createGraph(V);
    capacity=9,no_of_nodes=0;
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
    dijkstra(graph, 0);
	return 0;
}
