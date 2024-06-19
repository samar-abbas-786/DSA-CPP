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

    void remove(int value)
    {
        int index = -1;
        for (int i = 0; i < size; ++i)
        {
            if (heap[i] == value)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Element not found in the heap" << endl;
            return;
        }

        // Replace the element to be removed with the last element
        heap[index] = heap[size - 1];
        size--;

        // Perform heapifyUp or heapifyDown as needed
        if (index > 0 && heap[index] > heap[(index - 1) / 2])
        {
            heapifyUp(index);
        }
        else
        {
            heapifyDown(index);
        }
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
    int capacity;
    cout << "Enter the capacity of the heap: ";
    cin >> capacity;

    maxheap h(capacity);

    int choice, value, maxElement;

    do
    {
        cout << "\n1. Insert\n2. Extract Max\n3. Remove\n4. Display\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            h.insert(value);
            break;
        case 2:
            maxElement = h.extractMax();
            cout << "Maximum Element : " << maxElement << endl;
            break;
        case 3:
            cout << "Enter value to remove: ";
            cin >> value;
            h.remove(value);
            break;
        case 4:
            h.display();
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
