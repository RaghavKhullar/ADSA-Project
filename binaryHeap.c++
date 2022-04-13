#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include "binaryHeaps.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

void printArr(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

//calculating shortest path from src to all the vertices.
//Time complexity: O(E*logV + V*logV)
void dijkstra( Graph *graph, int src)
{

    //number of vertices in graph
    int V = graph->V;
    //it stores the distance values
    int dist[V];

    //heap is basically made on the basis of weights of edges
     MinHeap *minHeap = createMinHeap(V);

  
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                           dist[v]);
        minHeap->pos[v] = v;
    }

    //distance of src=0
    minHeap->array[src] =
        newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

   //heap contains all those nodes whose distance is not yet finalised,
   //after every iteration the min element is removed
    while (minHeap->size > 0)
    {
        //extract the vertex with minimum distance
        struct MinHeapNode *minHeapNode =
            extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

        //traverse all the connected vertices with u and update the distances if needed
        struct AdjListNode *pCrawl =
            graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            //if shortest path till u is finalised and the path till v is greater than from src to u and u to v, then we update the distance
            if (isInMinHeap(minHeap, v) &&
                dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                //update the value in minheap as well
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printArr(dist, V);
}


int main()
{
   auto start = high_resolution_clock::now();
    int V = 9;
    struct Graph *graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph,1,0,4);
    addEdge(graph,0,7,8);
    addEdge(graph,7,0,8);
    addEdge(graph,1,7,11);
    addEdge(graph,7,1,11);
    addEdge(graph,1,2,8);
    addEdge(graph,2,1,8);
    addEdge(graph,7,6,1);
    addEdge(graph,6,7,1);
    addEdge(graph,7,8,7);
    addEdge(graph,8,7,7);
    addEdge(graph,2,8,2);
    addEdge(graph,8,2,2);
    addEdge(graph,8,6,6);
    addEdge(graph,6,8,6);
    addEdge(graph,2,3,7);
    addEdge(graph,3,2,7);
    addEdge(graph,6,5,2);
    addEdge(graph,5,6,2);
    addEdge(graph,2,5,4);
    addEdge(graph,5,2,4);
    addEdge(graph,3,5,14);
    addEdge(graph,5,3,14);
    addEdge(graph,3,4,9);
    addEdge(graph,4,3,9);
    addEdge(graph,5,4,10);
    addEdge(graph,4,5,10);
    dijkstra(graph, 0);
    auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "\n\nTime taken by function: "<< duration.count() << " microseconds" << endl;
    return 0;
}
