#include<bits/stdc++.h>
using namespace std;

// Utility Functions...
inline size_t nearest_power_of_2(const size_t &n)  // Return the nearest( and strictly greater than ) number to "n" which is a power of 2..
{
    return 1ULL<<(static_cast<size_t>(log2(n))+1);
}

// Class Forward Declaration
template<typename T> class myvector;

// Declarations For Friend Functions...
template<typename T> void swap(myvector<T> &a,myvector<T> &b);

template<typename T>
class myvector
{
    // Data Members...
    T* vector_pointer;  //  A pointer pointing to the start of the dynamic array...
    size_t vector_size,vector_capacity;  // Analogous to STL::Vector...

    // Friend Functions...
    friend void swap <>(myvector &a,myvector &b);  // Copy and Swap Idiom ...

public:

    // Constructors/Destructors...
    myvector():vector_pointer(NULL),vector_size(0),vector_capacity(0) {}  // Default Constructor
    myvector(const myvector& other):vector_pointer(NULL),vector_size(0),vector_capacity(0)  // Copy Constructor
    {
        vector_pointer=new T[other.capacity()];
        std::copy(&other[0],&other[0]+other.size(),vector_pointer);
        vector_size=other.vector_size;
        vector_capacity=other.vector_capacity;
    }
    ~myvector()  // Destructor...
    {
        delete[] vector_pointer;
    }

    // Assignment Operator...
    myvector& operator =(myvector other);

    // Vector-Specific Routines...
    void resize(const size_t &newsize);  // Change the size of the vector exactly to "newsize"...
    void reserve(size_t newcapacity);  // Change the capacity of the vector to be at least equal to "newcapacity"
    void push_back(const T &val);  // Add a new element of value "val" at the end of the vector...
    void pop_back();  // Remove the last element of the vector...
    size_t size() const;  // Returns vector_size...
    size_t capacity() const;  // Returns vector_capacity...
    T& operator [](const size_t &pos);  // Returns vector[pos]...
    const T& operator [](const size_t &pos) const;  // Returns vector[pos] as const...
    bool empty() const;  // Checks whether vector is empty or not...
    T& at(const size_t& pos);  // Same as the "[]" operator, but this one checks for out-of-bound exceptions..
    const T& at(const size_t& pos) const;
    void erase(const size_t& pos);  // Erase the element at "pos"..
    void erase(const size_t& pos1,const size_t& pos2);  // Erase the elements in range [pos1,pos2)..
    void insert(const size_t& pos,const T& val);  // Insert 1 element of value "val" at "pos"..
    void insert(const size_t& pos,const size_t& n,const T& val);  // Insert "n" elements of value "val", beginning from "pos"..
    void clear();  // Remove all the elements of the vector...
};


template<typename T>
myvector<T>& myvector<T>::operator =(myvector<T> other)
{
    std::swap(*this,other);
    return *this;
}


// Vector-Specific Routine Definitions...
template<typename T>
void myvector<T>::resize(const size_t &newsize)
{
    if(newsize<vector_size)
    {
        for(size_t i=newsize; i<vector_size; i++)
        {
            vector_pointer[i].~T();
        }
    }
    else if(newsize>vector_capacity)
    {
        reserve(newsize);
    }
    vector_size=newsize;
}

template<typename T>
void myvector<T>::reserve(size_t newcapacity)
{
    newcapacity=nearest_power_of_2(newcapacity);  // Keep the capacity of the vector as a power of 2 to avoid space wastage..
    if(newcapacity>vector_capacity)
    {
        T* temp=new T[newcapacity];
        std::copy(vector_pointer,vector_pointer+vector_capacity,temp);
        delete[] vector_pointer;
        vector_pointer=temp;
        vector_capacity=newcapacity;
    }
}

template<typename T>
void myvector<T>::push_back(const T &val)
{
    if(vector_capacity<=vector_size)
        reserve(vector_capacity);
    vector_pointer[vector_size++]=val;
}

template<typename T>
void myvector<T>::pop_back()
{
    if(vector_size)
    {
        vector_pointer[vector_size-1].~T();
        --vector_size;
    }
}

template<typename T>
size_t myvector<T>::size() const
{
    return vector_size;
}

template<typename T>
size_t myvector<T>::capacity() const
{
    return vector_capacity;
}

template<typename T>
T& myvector<T>::operator [](const size_t &pos)
{
    return vector_pointer[pos];
}

template<typename T>
const T& myvector<T>::operator [](const size_t &pos) const
{
    return vector_pointer[pos];
}

template<typename T>
bool myvector<T>::empty() const
{
    return vector_size==0;
}

template<typename T>
T& myvector<T>::at(const size_t& pos)
{
    if(pos>=vector_size)
        throw std::out_of_range("");
    else
        return vector_pointer[pos];
}

template<typename T>
const T& myvector<T>::at(const size_t& pos) const
{
    if(pos>=vector_size)
        throw std::out_of_range("");
    else
        return vector_pointer[pos];
}

template<typename T>
void myvector<T>::erase(const size_t& pos)
{
    vector_pointer[pos].~T();
    for(size_t i=pos; i<vector_size-1; i++)
    {
        vector_pointer[i]=vector_pointer[i+1];   //  Shift all the elements one step left, beginning from "pos+1"
    }
    --vector_size;
}

template<typename T>
void myvector<T>::erase(const size_t& pos1,const size_t& pos2)
{
    for(size_t i=pos1; i<pos2; i++)
    {
        vector_pointer[i].~T();
    }
    for(size_t i=pos1; i<vector_size-(pos2-pos1); i++)
    {
        vector_pointer[i]=vector_pointer[i+pos2-pos1];  // Shift all the elements (pos2-pos1) steps left, beginning from "pos2"
    }
    vector_size-=pos2-pos1;
}

template<typename T>
void myvector<T>::insert(const size_t& pos,const T& val)
{
    if(vector_capacity<=vector_size)  // Create some space if it doesn't have enough to take another element..
        reserve(vector_size);
    vector_size++;
    for(size_t i=vector_size-1; i>pos; i--)  //  Shift all the elements one step towards right, beginning from "pos"+1..
    {
        vector_pointer[i]=vector_pointer[i-1];
    }
    vector_pointer[pos]=val;
}

template<typename T>
void myvector<T>::insert(const size_t& pos,const size_t& n,const T& val)
{
    if(vector_size<n+vector_capacity)
        reserve(vector_size+n);       //  Create space for atleast "n" elements...
    vector_size+=n;
    for(size_t i=vector_size-1; i>=pos+n; i--)   //  Shift all the elements "n" step towards right, beginning from "pos"+1..
    {
        vector_pointer[i]=vector_pointer[i-n];
    }
    for(size_t i=pos; i<pos+n; i++)  // Change all the elements in [pos,pos+n) to "val"..
    {
        vector_pointer[i]=val;
    }
}

template<typename T>
void myvector<T>::clear()
{
    for(size_t i=0; i<vector_size; i++)
    {
        vector_pointer[i].~T();
    }
    vector_size=0;
}


// Friend Function Definitions...
template<typename T>
void swap(myvector<T> &a,myvector<T> &b)  // Copy and Swap Idiom ...
{
    using std::swap;
    swap(a.vector_size,b.vector_size);
    swap(a.vector_capacity,b.vector_capacity);
    swap(a.vector_pointer,b.vector_pointer);
}


// Output Operator Definition...
template<typename T>
std::ostream& operator <<(std::ostream& out,const myvector<T> &a)  // Overloaded output operator to display the contents of a vector..
{
    std::copy(&a[0], &a[0]+a.size(), std::ostream_iterator<T>(out, " "));
    return out;
}


// Usage...
int main()
{
    myvector<int> a;
}
