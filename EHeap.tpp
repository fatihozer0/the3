#pragma once

template<typename T>
class EHeap
{
private:
    class HandleData
    {
        friend EHeap;
    private:
    };
    /* Private fields & methods to be completed by you. */
    const unsigned mCapacity;
    unsigned mSize;
    T *mHeap;
public:
    typedef HandleData * Handle;
    // Constructs an empty e-heap with a fixed capacity.
    EHeap(unsigned capacity) : mCapacity(capacity), mSize(0), mHeap(new T[capacity + 1])
    {
    }

    unsigned size() const {
      return mSize;
    }

    Handle push(T t) {

      if(mSize == mCapacity) return nullptr;
      mSize++;
      unsigned i = mSize;
      mHeap[mSize] = t;
      while(i > 1 and mHeap[i/2] > mHeap[i]){
        std::swap(mHeap[i/2], mHeap[i]);
        i = i/2;
      }
      return Handle(i);
    }

    T pop()
    {
      if (mSize == 0)
      {
        return 0;
      }
      unsigned i = 1;
      T popped = mHeap[1];
      std::swap(mHeap[1], mHeap[mSize]);
      mSize--;

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
          std::swap(mHeap[minChild], mHeap[i]);
          i = minChild;
        }
        else
        {
          break;
        }
      }

      return popped;

    }

    T erase(Handle handle) {
      if (mSize == 0)
      {
        return 0;
      }

      unsigned i=0;
      for(unsigned j = 1; j<= mSize ; j++){
        if(Handle(j) == handle) {
          i = j;
          break;
        }
      }

      std::swap(mHeap[i] , mHeap[mSize]);
      mSize--;

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
          std::swap(mHeap[minChild], mHeap[i]);
          i = minChild;
        }
        else
        {
          break;
        }
      }
      return mHeap[mSize];
    }

    ~EHeap() {
      delete [] mHeap;
    }
};
