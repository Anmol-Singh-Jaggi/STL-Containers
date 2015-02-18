#include<bits/stdc++.h>
using namespace std;

// MYVECTOR BEGINS...


// Utility Functions...
inline size_t nearestPowerOf2( const size_t &n ) // Returns the nearest and least greater number to "n" which is a power of 2..
{
	size_t temp = n, ans = 0;
	if ( ( n & ( n - 1 ) ) == 0 ) // If n is a power of 2...
	{
		return n;  // Return n itself...
	}
	while ( temp )
	{
		temp >>= 1;
		ans++;
	}
	return ( size_t )1 << ans;
}

// Class Forward Declaration
template<typename T> class myvector;

// Declarations For Friend Functions...
template<typename T> void swap( myvector<T> &a, myvector<T> &b );

template<typename T>
class myvector
{
	// Data Members...
	T* vector_pointer;  //  A pointer pointing to the start of the dynamic array...
	size_t vector_size, vector_capacity; // Analogous to STL::Vector...

	// Friend Functions...
	friend void swap <>( myvector &a, myvector &b ); // Copy and Swap Idiom ...

public:

	// Constructors/Destructors...
	myvector( const size_t& init_size, const T& val ); // Constructor...
	myvector( const myvector& other ); // Copy Constructor...
	~myvector();  // Destructor...

	// Assignment Operator...
	myvector& operator =( myvector other );

	// Vector-Specific Routines...
	void resize( const size_t &new_size, const T& val ); // Change the size of the vector exactly to "new_size" [ The capacity might be different though ]
	void reserve( size_t new_capacity ); // Change the capacity of the vector to be at least equal to "new_capacity"...
	void push_back( const T &val ); // Add a new element of value "val" at the end of the vector...
	void pop_back();  // Remove the last element of the vector...
	size_t size() const;  // Returns vector_size...
	size_t capacity() const;  // Returns vector_capacity...
	T& operator []( const size_t &pos ); // Returns vector[pos]...
	const T& operator []( const size_t &pos ) const; // Returns vector[pos] as const...
	bool empty() const;  // Checks whether vector is empty or not...
	T& at( const size_t& pos ); // Same as the "[]" operator, but this one checks for out-of-bound exceptions..
	const T& at( const size_t& pos ) const;
	T& back();  // Returns a reference to the last element of the vector...
	const T& back() const;
	T& front();  // Returns a reference to the first element of the vector...
	const T& front() const;
	void erase( const size_t& pos ); // Erase the element at "pos"..
	void erase( const size_t& pos1, const size_t& pos2 ); // Erase the elements in range [pos1,pos2)..
	void insert( const size_t& pos, const T& val ); // Insert 1 element of value "val" at "pos"..
	void insert( const size_t& pos, const size_t& n, const T& val ); // Insert "n" elements of value "val", beginning from "pos"..
	void clear();  // Remove all the elements of the vector...
};


// Constructor/Destructor Definitions...
template<typename T>
myvector<T>::myvector( const size_t& init_size = 0, const T& val = T() ) //  Constructor...
{
	vector_pointer = nullptr;
	vector_size = 0;
	vector_capacity = 0;
	resize( init_size, val ); // Resize the vector...
}

template<typename T>
myvector<T>::myvector( const myvector& other ) // Copy Constructor...
{
	vector_pointer = new T[other.capacity()];
	std::copy( &other[0], &other[0] + other.size(), vector_pointer );
	vector_size = other.vector_size;
	vector_capacity = other.vector_capacity;
}

template<typename T>
myvector<T>::~myvector()  // Destructor...
{
	delete[] vector_pointer;
}


// Assignment Operator Definition...
template<typename T>
myvector<T>& myvector<T>::operator =( myvector<T> other )
{
	std::swap( *this, other );
	return *this;
}


// Vector-Specific Routine Definitions...
template<typename T>
void myvector<T>::resize( const size_t &new_size, const T& val = T() )
{
	if ( new_size < size() )
	{
		for ( size_t i = new_size; i < size(); i++ )
		{
			vector_pointer[i].~T();  // Call the destructor on the elements...
		}
	}
	else if ( new_size > capacity() )
	{
		reserve( new_size ); // Might change the capacity...
	}

	for ( size_t i = size(); i < new_size; i++ )
	{
		vector_pointer[i] = val; // Fill the new elements with value "val"...
	}
	vector_size = new_size; // Update size...
}

template<typename T>
void myvector<T>::reserve( size_t new_capacity )
{
	new_capacity = nearestPowerOf2( new_capacity ); // Keep the capacity of the vector as a power of 2 to avoid space wastage..
	if ( new_capacity > capacity() ) // Never decreases the capacity...
	{
		T* temp = new T[new_capacity];
		if ( vector_pointer ) // The vector is not empty...
		{
			std::copy( vector_pointer, vector_pointer + capacity(), temp );  // Copy contents of vector to temp...
		}
		delete[] vector_pointer;  // Delete original vector_pointer...
		vector_pointer = temp; // temp is the new vector_pointer...
		vector_capacity = new_capacity; // Update Capacity...
	}
}

template<typename T>
void myvector<T>::push_back( const T &val )
{
	if ( capacity() == size() ) // The Vector is Full...
	{
		reserve( size() + 1 );  // Reserve more space...
	}
	vector_pointer[vector_size++] = val;
}

template<typename T>
void myvector<T>::pop_back()
{
	assert( size() ); // The vector has atleast 1 element...
	vector_pointer[size() - 1].~T(); // Call the destructor on the deleted element...
	--vector_size;  // Update Vector Size..
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
T& myvector<T>::operator []( const size_t &pos )
{
	return vector_pointer[pos];
}

template<typename T>
const T& myvector<T>::operator []( const size_t &pos ) const
{
	return vector_pointer[pos];
}

template<typename T>
bool myvector<T>::empty() const
{
	return size() == 0;
}

template<typename T>
T& myvector<T>::at( const size_t& pos )
{
	if ( pos >= size() )
	{
		throw std::out_of_range( "" );
	}
	else
	{
		return vector_pointer[pos];
	}
}

template<typename T>
const T& myvector<T>::at( const size_t& pos ) const
{
	if ( pos >= size() )
	{
		throw std::out_of_range( "" );
	}
	else
	{
		return vector_pointer[pos];
	}
}

template<typename T>
T& myvector<T>::back()
{
	assert( size() ); // Ensure the vector has atleast 1 element...
	return vector_pointer[size() - 1];
}

template<typename T>
const T& myvector<T>::back() const
{
	assert( size() ); // Ensure the vector has atleast 1 element...
	return vector_pointer[size() - 1];
}

template<typename T>
T& myvector<T>::front()
{
	assert( size() ); // Ensure the vector has atleast 1 element...
	return vector_pointer[0];
}

template<typename T>
const T& myvector<T>::front() const
{
	assert( size() ); // Ensure the vector has atleast 1 element...
	return vector_pointer[0];
}

template<typename T>
void myvector<T>::erase( const size_t& pos )
{
	assert( pos <= size() );
	vector_pointer[pos].~T();
	for ( size_t i = pos; i < size() - 1; i++ )
	{
		vector_pointer[i] = vector_pointer[i + 1]; //  Shift all the elements one step left, beginning from "pos+1"
	}
	--vector_size;  // Update size...
}

template<typename T>
void myvector<T>::erase( const size_t& pos1, const size_t& pos2 )
{
	assert( pos1 <= size() && pos2 <= size() && pos1 <= pos2 );
	for ( size_t i = pos1; i < pos2; i++ )
	{
		vector_pointer[i].~T();  // Call destructors on elements to be deleted...
	}
	for ( size_t i = pos1; i < size() - ( pos2 - pos1 ); i++ )
	{
		vector_pointer[i] = vector_pointer[i + pos2 - pos1]; // Shift all the elements (pos2-pos1) steps left, beginning from "pos2"
	}
	vector_size -= pos2 - pos1; // Update size...
}

template<typename T>
void myvector<T>::insert( const size_t& pos, const T& val )
{
	assert( pos <= size() ); // Compliant with std::Vector...
	if ( capacity() == size() ) // Create some space if it doesn't have enough to take another element..
	{
		reserve( size() + 1 );
	}
	vector_size++;   // Update vector_size...
	for ( size_t i = size() - 1; i > pos; i-- ) //  Shift all the elements one step towards right, beginning from "pos"+1..
	{
		vector_pointer[i] = vector_pointer[i - 1];
	}
	vector_pointer[pos] = val;
}

template<typename T>
void myvector<T>::insert( const size_t& pos, const size_t& n, const T& val )
{
	assert( pos <= size() ); // Compliant with std::vector...
	if ( size() + n > capacity() ) // Not enough space...
	{
		reserve( size() + n );  //  Create space...
	}
	vector_size += n; // Update vector_size...
	for ( size_t i = size() - 1; i >= pos + n; i-- ) //  Shift all the elements "n" step towards right, beginning from "pos"+1..
	{
		vector_pointer[i] = vector_pointer[i - n];
	}
	for ( size_t i = pos; i < pos + n; i++ ) // Change all the elements in [pos,pos+n) to "val"..
	{
		vector_pointer[i] = val;
	}
}

template<typename T>
void myvector<T>::clear()
{
	for ( size_t i = 0; i < vector_size; i++ )
	{
		vector_pointer[i].~T();
	}
	vector_size = 0;
}


// Friend Function Definitions...
template<typename T>
void swap( myvector<T> &a, myvector<T> &b ) // Copy and Swap Idiom ...
{
	using std::swap;
	swap( a.vector_size, b.vector_size );
	swap( a.vector_capacity, b.vector_capacity );
	swap( a.vector_pointer, b.vector_pointer );
}


// Output Operator Definition...
template<typename T>
std::ostream& operator <<( std::ostream& out, const myvector<T> &a ) // Overloaded output operator to display the contents of a vector..
{
	out << "[";
	std::copy( &a[0], &a[0] + a.size(), std::ostream_iterator<T>( out, ", " ) );
	if ( a.size() )
	{
		out << "\b\b";
	}
	out << "]";
	return out;
}


// VECTOR ENDS...


// Usage...
int main()
{
	myvector<int> a;
	a.push_back( 1 );
	a.push_back( 2 );
	a.push_back( 3 );
	a.push_back( 4 );
	a.push_back( 5 );
	cout << a << "\n";
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	cout << a.capacity() << "\n" << a;
}
