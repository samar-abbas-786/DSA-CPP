#include <iostream>

using namespace std;

class maxheap
{
private:
    int *heap;
    int capacity;
    int size;

    void heapifyUp(int index)
    {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index] > heap[parent])
        {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;
        if (leftChild < size && heap[leftChild] > heap[largest])
        {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest])
        {
            largest = rightChild;
        }
        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    maxheap(int capacity) : capacity(capacity), size(0)
    {
        heap = new int[capacity];
    }

    ~maxheap()
    {
        delete[] heap;
    }

    void insert(int value)
    {
        if (size == capacity)
        {
            cout << "Heap is Full!" << endl;
            return;
        }
        heap[size] = value;
        size++;
        heapifyUp(size - 1);
    }

    int extractMax()
    {
        if (size == 0)
        {
            cout << "Heap is Empty" << endl;
            return -1;
        }
        int max = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return max;
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    maxheap h(7);

    h.insert(5);
    h.insert(2);
    h.insert(8);
    h.insert(9);
    h.insert(1);
    h.insert(23);

    h.display();

    int maxElement = h.extractMax();
    cout << "Maximum Element : " << maxElement << endl;

    h.display();
}