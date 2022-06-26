//
// Middle East Technical University
// Dept. of Computer Engineering
//
// CENG 213 - Data Structures
// Dr. Hakan YILDIZ
// hakan@ceng.metu.edu.tr
//
// Not to be reshared without permission.
//

// *******************************************
// *** AN EXAMPLE MIN-HEAP WITH FIXED CAPACITY
// *******************************************

#include <algorithm>
using std::swap;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <stdexcept>
using std::exception;

#include <string>
using std::string;

// Thrown when a pop is attempted on an empty heap.
class HeapEmptyException : public exception {};

// Thrown when a push is attempted on a heap at full capacity, or when a heap
// is constructed on array larger than the given capacity.
class HeapOutOfCapacityException : public exception {};

// Represents a min-heap with fixed capacity.
template<typename T>
class Heap
{
private:
    const unsigned mCapacity;
    unsigned mSize;
    T *mHeap;

private:
    // Repeatedly pushes the item at the i-th node up, locally restoring the violated heap orders.
    // The push stops when there is no local violation of the heap order.
    void percolateUp(unsigned i)
    {
      while (i > 1 and mHeap[i / 2] > mHeap[i])
      {
        swap(mHeap[i / 2], mHeap[i]);
        i = i / 2;
      }
    }

    // Repeatedly pushes the item at the i-th node down, locally restoring the violated heap orders.
    // The push stops when there is no local violation of the heap order.
    void percolateDown(unsigned i)
    {
      while (2 * i <= mSize)
      {
        unsigned minChild;

        if (2 * i + 1 <= mSize and mHeap[2 * i + 1] < mHeap[2 * i])
        {
          minChild = 2 * i + 1;
        }
        else
        {
          minChild = 2 * i;
        }

        if (mHeap[minChild] < mHeap[i])
        {
          swap(mHeap[minChild], mHeap[i]);
          i = minChild;
        }
        else
        {
          break;
        }
      }
    }

public:
    // Constructs an empty heap.
    Heap(unsigned capacity) : mCapacity(capacity),
                              mSize(0),
                              mHeap(new T[capacity + 1])
    {}

    // Constructs a heap from the given items, in linear time.
    Heap(unsigned capacity, T items[],  unsigned size) : mCapacity(capacity),
                                                         mSize(size),
                                                         mHeap(nullptr)
    {
      if (capacity < size)
      {
        throw HeapOutOfCapacityException();
      }

      // We can only allocate this after making sure that we do not throw an exception.
      mHeap = new T[capacity + 1];

      for (unsigned i = mSize; i >= 1; i--)
      {
        mHeap[i] = items[i - 1];
        percolateDown(i);
      }
    }

    // Pushes a new element into the heap.
    void push(T t)
    {
      if (mSize == mCapacity)
      {
        throw HeapOutOfCapacityException();
      }

      mSize++;
      mHeap[mSize] = t;

      percolateUp(mSize);
    }

    // Pops the smallest element from the heap.
    T pop()
    {
      if (mSize == 0)
      {
        throw HeapEmptyException();
      }

      T popped = mHeap[1];
      swap(mHeap[1], mHeap[mSize]);
      mSize--;

      percolateDown(1);

      return popped;
    }

    // Destroys the heap.
    ~Heap()
    {
      delete [] mHeap;
    }
};

int main()
{
  int a[] = {9, 4, 2, 7, 1, 5, 3, 6, 8};
  int n = sizeof(a) / sizeof(a[0]);

  Heap<int> h(n);

  for (auto v : a)
  {
    h.push(v);
  }

  // or Heap<int> h(n, a, n) as a faster alternative.

  for (int i = 0; i < n; i++)
  {
    cout << h.pop() << " ";
  }

  cout << endl;

  return 0;
}