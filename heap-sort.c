#include <stdio.h>

#define SIZE 20

typedef struct {
    int node[SIZE+1];
    int currSize;
} minHeap;

void swap(minHeap *heap, int a, int b);
int parent(int i);
int left_child(int i);
void init(minHeap *heap);
void bubble_up(minHeap *heap, int i);
void bubble_down(minHeap * heap, int i);
void insert(minHeap *heap, int x);
int extract_min(minHeap *heap);
void heapify(minHeap *heap, int arr[], int n);
void printArray(int arr[], int n);



void heapsort(int arr[], int n)
{
    minHeap heap;

    heapify(&heap, arr, n);

    for(int i = 0; i < n; i++)
    {
        arr[i] = extract_min(&heap);
    }
}

int main()
{
    int arr[] = {6, 4, 2, 10, 22, 0, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, n);
    heapsort(arr, n);
    printArray(arr, n);
}


void swap(minHeap *heap, int a, int b)
{
    int temp = heap->node[a];
    heap->node[a] = heap->node[b];
    heap->node[b] = temp;
}

int parent(int i)
{
    if(i==1)
    {
        return -1;
    }

    return ((int) i/2);
}

int left_child(int i)
{
    return 2*i;
}

void init(minHeap *heap)
{
    heap->currSize = 0;
}

void bubble_up(minHeap *heap, int i)
{
    if(parent(i) == -1)
    {
        return;
    }
    if(heap->node[parent(i)] > heap->node[i])
    {
        swap(heap, i, parent(i));
        bubble_up(heap, parent(i));
    }
}

void bubble_down(minHeap *heap, int i)
{
    int c; //Child index
    int min_index; //Index of the lightest child

    c = left_child(i);
    min_index = i;

    for(int i = 0; i <= 1; i++)
    {
        if((c+i) <= heap->currSize)
        {
            if(heap->node[min_index] > heap->node[c+i])
            {
                min_index = c+i;
            }
        }
    }

    if(min_index != i)
    {
        swap(heap, i, min_index);
        bubble_down(heap, min_index);
    }
}

void insert(minHeap *heap, int x)
{
    if(heap->currSize >= SIZE)
    {
        printf("Warning: Priority Queue Overflow\n");
    }
    else
    {
        heap->currSize = (heap->currSize)+1;
        heap->node[heap->currSize] = x;
        bubble_up(heap, heap->currSize);
    }
}

int extract_min(minHeap *heap)
{
    int min = -1;

    if(heap->currSize <= 0)
    {
        printf("Warning: Empty Priority Queue\n");
    }
    else
    {
        min = heap->node[1];
        heap->node[1] = heap->node[heap->currSize];
        heap->currSize = heap->currSize - 1;
        bubble_down(heap, 1);
    }
    return min;
}

void heapify(minHeap *heap, int arr[], int n)
{
    init(heap);

    for(int i = 0; i < n; i++)
    {
        insert(heap, arr[i]);
    }
}

void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}
