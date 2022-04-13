#include <iostream>
using namespace std;
#include <limits.h>
#include <chrono>
using namespace std::chrono;

#define V 9

// function to find the minimum distance value from vertices not yet included in shortest path
int minDistance(int dist[], bool isReached[])
{

	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (isReached[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printSolution(int dist[])
{
	cout << "Vertex \t Distance from Source" << endl;
	for (int i = 0; i < V; i++)
		cout << i << " \t\t" << dist[i] << endl;
}

// adjacency matrix representation: O(V^2)
void dijkstra(int graph[V][V], int src)
{
	// stores the distance value of vertex from source
	int dist[V];
	// true if the i-th vertex's distance has been finalised as shortest path
	bool isReached[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, isReached[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{
		// min distance not yet reached, u is that vertex
		int u = minDistance(dist, isReached);

		// the vertex is now reached
		isReached[u] = true;

		// change the distance value.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in isReached, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!isReached[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	printSolution(dist);
}

int main()
{

	int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
					   {4, 0, 8, 0, 0, 0, 0, 11, 0},
					   {0, 8, 0, 7, 0, 4, 0, 0, 2},
					   {0, 0, 7, 0, 9, 14, 0, 0, 0},
					   {0, 0, 0, 9, 0, 10, 0, 0, 0},
					   {0, 0, 4, 14, 10, 0, 2, 0, 0},
					   {0, 0, 0, 0, 0, 2, 0, 1, 6},
					   {8, 11, 0, 0, 0, 0, 1, 0, 7},
					   {0, 0, 2, 0, 0, 0, 6, 7, 0}};

	auto start = high_resolution_clock::now();
	dijkstra(graph, 0);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start).count();

	cout << "\n\nTime taken by function: " << duration << " microseconds" << endl;

	return 0;
}

