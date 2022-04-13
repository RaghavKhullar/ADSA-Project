#include <bits/stdc++.h>
#include "fibonacciHeaps.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
int NUM;

// calculating shortest path from src to all the vertices.
// Time complexity: O(E + V*logV)
void dijkstra(struct Graph *graph, int src)
{

    // number of vertices in graph
    int V = graph->V;
    // it stores the distance values
    int dist[V];
    // represents the nodes in the heap
    node *nodes[V];

    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        if (v == src)
        {
            dist[v] = 0;
        }
        nodes[v] = insertion(v, dist[v]); // insertion of nodes in fibonacci heap
    }

    no_of_nodes = NUM - 1;
    // heap contains all those nodes whose distance is not yet finalised,
    // after every iteration the min element is removed
    while (no_of_nodes != 0)
    {

        // extract the vertex with minimum distance
        struct node *minHeapNode = mini;
        Extract_min();
        // Store the extracted vertex number
        int u = minHeapNode->key;

        // traverse all the connected vertices with u and update the distances if needed
        struct AdjListNode *pCrawl =
            graph->array[u].head;
       
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
         

            // if shortest path till u is finalised and the path till v is greater than from src to u and u to v, then we update the distance

            if (
                dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v])
            {
                

                // findAndDecreaseNode if the node is there in the heap and then decrease the node's distance
                findAndDecreaseNode(nodes[v], dist[v], dist[u] + pCrawl->weight);
                dist[v] = dist[u] + pCrawl->weight;
            }
            pCrawl = pCrawl->next;
        }
    }

    printArr(dist, V);
}

// Driver code
int main()
{
    
    


        int V = 9;
        NUM=9;
        struct Graph *graph = createGraph(V);
           addEdge(graph,0,1,4);
    addEdge(graph,0,7,8);
    addEdge(graph,1,7,11);
    addEdge(graph,1,2,8);
    addEdge(graph,7,6,1);
    addEdge(graph,7,8,7);
    addEdge(graph,2,8,2);
    addEdge(graph,8,6,6);
    addEdge(graph,2,3,7);
    addEdge(graph,6,5,2);
    addEdge(graph,2,5,4);
    addEdge(graph,3,5,14);
    addEdge(graph,3,4,9);
    addEdge(graph,5,4,10);
     auto start = high_resolution_clock::now();
        dijkstra(graph, 0);
       auto stop = high_resolution_clock::now();
    	auto duration = duration_cast<microseconds>(stop - start).count();

    	cout << "\n\nTime taken by function: "<< duration << " microseconds" << endl;
    return 0;
}
