#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include"graphs.h"
using namespace std;
//A structure so that we can represent a node in a heap, which holds the vertex number(v) and distance from source
struct MinHeapNode
{
    int v;
    int dist;
};

// Structure for representing the minHeap
struct MinHeap
{

    //current nodes in heap
    int size;
    //max number of elements in the heap
    int capacity;
    
    //pos[i] holds the current location of a particular vertex in the heap, basically whenever we change decrease
    //a node value, we can get the changed position of vertex in pos
    int *pos;
    //contains all the nodes of the heap
     MinHeapNode **array;
};

//creates a new min-heap node
 MinHeapNode *newMinHeapNode(int v, int dist)
{
     MinHeapNode *minHeapNode =
        ( MinHeapNode *)
            malloc(sizeof( MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

//creates a min-heap
 MinHeap *createMinHeap(int capacity)
{
     MinHeap *minHeap =
        ( MinHeap *)
            malloc(sizeof( MinHeap));
    minHeap->pos = (int *)malloc(
        capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        ( MinHeapNode **)
            malloc(capacity *
                   sizeof( MinHeapNode *));
    return minHeap;
}


void swap( MinHeapNode **a,
                      MinHeapNode **b)
{
     MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

//min-heapify function
// this function is also updating the position of nodes if they are swapped
void minHeapify( MinHeap *minHeap,
                int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
            minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
            minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        // smallest node is the new parent node
        MinHeapNode *smallestNode =
            minHeap->array[smallest];
        // idx node is the index node which was the earlier parent
        MinHeapNode *idxNode =
            minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swap(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}



//extracting minimum in heap
 MinHeapNode *extractMin( MinHeap *
                                   minHeap)
{
    if (minHeap->size == 0)
        return NULL;

    // root node is the minimum element
     MinHeapNode *root =
        minHeap->array[0];

    // change the new root as the right most element in leaf nodes
     MinHeapNode *lastNode =
        minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // change the position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // heapify the heap after the extraction
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

//decrease key basically decreases the value of the distance of a vertex v from the source vertex
//this is done if we find a path to vertex v from src which is smaller than the earlier path
void decreaseKey( MinHeap *minHeap,
                 int v, int dist)
{
    // i represents the index of the vertex v in the heap
    int i = minHeap->pos[v];

    // update the distance value
    minHeap->array[i]->dist = dist;

   // heapify the current vertex v according to the updated distance of the node
    while (i && minHeap->array[i]->dist <
                    minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap the node with parent if smaller distance and then update the position
        minHeap->pos[minHeap->array[i]->v] =
            (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swap(&minHeap->array[i],
                        &minHeap->array[(i - 1) / 2]);

        // update the index i to the parent's index after swapping
        i = (i - 1) / 2;
    }
}

//for an element to be present in min-heap the current position of the element should be less than the current size of the heap
bool isInMinHeap( MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
