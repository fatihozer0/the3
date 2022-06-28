#pragma once

template < typename T >
class EHeap
{
private :
    class HandleData
    {
        friend EHeap ;
    private :
        unsigned index;
        T value;


/* Private fields & methods to be completed by you . */
    };

    unsigned mCapacity;
    unsigned mSize;
    HandleData **mHeap;
    HandleData *mHandle;

/* Private fields & methods to be completed by you . */
public :
    typedef HandleData * Handle ;
// Constructs an empty e- heap with a fixed capacity .
    EHeap ( unsigned capacity ) : mCapacity(capacity),
                                  mSize(0),
                                  mHeap(new Handle[capacity+1]),
                                  mHandle(new HandleData[capacity+1])
    {  }
// Returns the number of elements in the e- heap .
    unsigned size () const { return mSize; }
// Pushes a value into the e- heap . A new handle
// representing the pushed value is returned .
    Handle push ( T val )
    {
        if(mSize == mCapacity) return nullptr;

        mSize++;

        mHandle[mSize].index = mSize;
        mHandle[mSize].value = val;
        mHeap[mSize] = &(mHandle[mSize]);

        unsigned i = mSize;
        while (i >1 && mHeap[i/2]->value > mHeap[i]->value)
        {
//            std::swap(mHeap[i/2], mHeap[i]);
            Handle temp = mHeap[i/2];
            mHeap[i/2] = mHeap[i];
            mHeap[i] = temp;
            i=i/2;
        }
        return mHeap[i];
    }
// Pops the minimum value (or one of the minimum ) from the e- heap .
    T pop () {

    }
// Erases the value whose handle is given . Returns the value back .
    T erase ( Handle handle ) { /* To be completed by you. */ }
// Destructor . All associated memory is to be freed .
    ~ EHeap ()
    {
        delete [] mHeap;
        delete [] mHandle;
    }
};