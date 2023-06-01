#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapify(int index, int size) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapify(largest, size);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);

        int index = heap.size() - 1;
        int parent = (index - 1) / 2;

        while (index > 0 && heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }


    void buildHeap() {
        int size = heap.size();

        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapify(i, size);
        }
    }

    void heapSort() {
        int size = heap.size();

        buildHeap();

        for (int i = size - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heapify(0, i);
        }
    }

    void display() {
        for (int value : heap) {
            cout << value << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap heap;

    // Insert elements into the heap
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(5);

    cout << "Heap: ";
    heap.display();

    // Perform Heap sort
    heap.heapSort();

    cout << "Sorted Array: ";
    heap.display();

    return 0;
}
