#include<iostream>
#include<new>
#include<cassert>
#include<stdexcept>
using namespace std;

// VECTOR BEGINS

// Utility functions
// Returns the smallest integer >= num which is a power of 2
size_t NearestPowerOfTwo( size_t num )
{
	size_t ans = 0;

	// If num is a power of 2
	if ( ( num & ( num - 1 ) ) == 0 )
	{
		// Return itself
		return num;
	}

	// Calculate Ceil(log2(num))
	while ( num )
	{
		num >>= 1;
		ans++;
	}

	return ( size_t )1 << ans;
}

// Class forward declaration
template<typename T> class Vector;

// Declarations for friend functions
template<typename T> void swap( Vector<T>& first, Vector<T>& second );

template<typename T>
class Vector
{
	// Data Members
	// A pointer pointing to the start of the dynamic array
	T* vectorPointer;
	// Analogous to std::vector
	size_t vectorSize, vectorCapacity;

	// Friend functions
	// Copy-and-Swap Idiom
	friend void swap <>( Vector& first, Vector& second );

public:

	Vector( const size_t& initSize = 0, const T& val = T() );
	Vector( const Vector& other );
	~Vector();

	Vector& operator =( Vector other );

	void Resize( const size_t& newSize, const T& val = T() );
	void Reserve( size_t newCapacity );
	void Push_back( const T& val );
	void Pop_back();
	size_t Size() const;
	size_t Capacity() const;
	T& operator []( const size_t& pos );
	const T& operator []( const size_t& pos ) const;
	bool Empty() const;
	T& At( const size_t& pos );
	const T& At( const size_t& pos ) const;
	T& Back();
	const T& Back() const;
	T& Front();
	const T& Front() const;
	void Erase( const size_t& pos );
	void Erase( const size_t& pos1, const size_t& pos2 );
	void Insert( const size_t& pos, const T& val );
	void Insert( const size_t& pos, const size_t& num, const T& val );
	void Clear();
};


template<typename T>
Vector<T>::Vector( const size_t& initSize, const T& val )
{
	vectorPointer = nullptr;
	vectorSize = 0;
	vectorCapacity = 0;
	Resize( initSize, val );
}

template<typename T>
Vector<T>::Vector( const Vector& other )
{
	vectorPointer = new T[other.capacity()];
	std::copy( &other[0], &other[0] + other.Size(), vectorPointer );
	vectorSize = other.vectorSize;
	vectorCapacity = other.vectorCapacity;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] vectorPointer;
}


template<typename T>
Vector<T>& Vector<T>::operator =( Vector<T> other )
{
	std::swap( *this, other );
	return *this;
}


template<typename T>
void Vector<T>::Resize( const size_t& newSize, const T& val )
{
	if ( newSize < Size() )
	{
		for ( size_t i = newSize; i < Size(); i++ )
		{
			vectorPointer[i].~T();
		}
	}
	else if ( newSize > Capacity() )
	{
		Reserve( newSize );
	}

	// All the necessary allocations/deallocations have been done
	for ( size_t i = Size(); i < newSize; i++ )
	{
		vectorPointer[i] = val;
	}
	vectorSize = newSize;
}

template<typename T>
void Vector<T>::Reserve( size_t newCapacity )
{
	newCapacity = NearestPowerOfTwo( newCapacity );

	if ( newCapacity > Capacity() )
	{
		T* temp = new T[newCapacity];

		if ( !this->Empty() )
		{
			std::copy( vectorPointer, vectorPointer + Capacity(), temp );
		}

		delete[] vectorPointer;
		vectorPointer = temp;
		vectorCapacity = newCapacity;
	}
}

template<typename T>
void Vector<T>::Push_back( const T& val )
{
	if ( Capacity() == Size() )
	{
		Reserve( Size() + 1 );
	}

	vectorPointer[vectorSize++] = val;
}

template<typename T>
void Vector<T>::Pop_back()
{
	assert( Size() );
	vectorPointer[Size() - 1].~T();
	--vectorSize;
}

template<typename T>
size_t Vector<T>::Size() const
{
	return vectorSize;
}

template<typename T>
size_t Vector<T>::Capacity() const
{
	return vectorCapacity;
}

template<typename T>
T& Vector<T>::operator []( const size_t& pos )
{
	return vectorPointer[pos];
}

template<typename T>
const T& Vector<T>::operator []( const size_t& pos ) const
{
	return vectorPointer[pos];
}

template<typename T>
bool Vector<T>::Empty() const
{
	return Size() == 0;
}

template<typename T>
T& Vector<T>::At( const size_t& pos )
{
	if ( pos >= Size() )
	{
		throw std::out_of_range( "" );
	}
	else
	{
		return vectorPointer[pos];
	}
}

template<typename T>
const T& Vector<T>::At( const size_t& pos ) const
{
	if ( pos >= Size() )
	{
		throw std::out_of_range( "" );
	}
	else
	{
		return vectorPointer[pos];
	}
}

template<typename T>
T& Vector<T>::Back()
{
	assert( Size() );
	return vectorPointer[Size() - 1];
}

template<typename T>
const T& Vector<T>::Back() const
{
	assert( Size() );
	return vectorPointer[Size() - 1];
}

template<typename T>
T& Vector<T>::Front()
{
	assert( Size() );
	return vectorPointer[0];
}

template<typename T>
const T& Vector<T>::Front() const
{
	assert( Size() );
	return vectorPointer[0];
}

template<typename T>
void Vector<T>::Erase( const size_t& pos )
{
	assert( pos <= Size() );

	vectorPointer[pos].~T();
	for ( size_t i = pos; i < Size() - 1; i++ )
	{
		//  Shift all the elements one step left, beginning from "pos+1"
		vectorPointer[i] = vectorPointer[i + 1];
	}

	--vectorSize;
}

template<typename T>
void Vector<T>::Erase( const size_t& pos1, const size_t& pos2 )
{
	assert( pos1 <= Size() && pos2 <= Size() && pos1 <= pos2 );

	for ( size_t i = pos1; i < pos2; i++ )
	{
		vectorPointer[i].~T();
	}

	for ( size_t i = pos1; i < Size() - ( pos2 - pos1 ); i++ )
	{
		// Shift all the elements (pos2-pos1) steps left, beginning from "pos2"
		vectorPointer[i] = vectorPointer[i + pos2 - pos1];
	}

	vectorSize -= pos2 - pos1;
}

template<typename T>
void Vector<T>::Insert( const size_t& pos, const T& val )
{
	assert( pos <= Size() );

	if ( Capacity() == Size() )
	{
		Reserve( Size() + 1 );
	}

	// Shift all the elements one step towards right, beginning from (pos + 1)
	for ( size_t i = Size(); i > pos; i-- )
	{
		vectorPointer[i] = vectorPointer[i - 1];
	}
	vectorPointer[pos] = val;

	vectorSize++;
}

template<typename T>
void Vector<T>::Insert( const size_t& pos, const size_t& num, const T& val )
{
	assert( pos <= Size() );

	const size_t newSize = Size() + num;
	if ( newSize > Capacity() )
	{
		Reserve( newSize );
	}

	// Shift all the elements "num" step towards right, beginning from (pos + 1)
	for ( size_t i = Size() + num - 1; i >= pos + num; i-- )
	{
		vectorPointer[i] = vectorPointer[i - num];
	}

	// Change all the elements in [pos, pos + num) to "val"
	for ( size_t i = pos; i < pos + num; i++ )
	{
		vectorPointer[i] = val;
	}

	vectorSize += num;
}

template<typename T>
void Vector<T>::Clear()
{
	for ( size_t i = 0; i < Size(); i++ )
	{
		vectorPointer[i].~T();
	}

	vectorSize = 0;
}


// Copy-and-Swap Idiom
template<typename T>
void swap( Vector<T>& first, Vector<T>& second )
{
	using std::swap;
	swap( first.vectorSize, second.vectorSize );
	swap( first.vectorCapacity, second.vectorCapacity );
	swap( first.vectorPointer, second.vectorPointer );
}


template<typename T1>
ostream& operator <<( ostream& out, const Vector<T1>& object )
{
	const char* separator = "";

	out << "[";
	for ( size_t i = 0; i < object.Size(); i++ )
	{
		out << separator;
		out << object[i];
		separator = ", ";
	}
	out << "]";

	return out;
}

// VECTOR ENDS


// Usage
int main()
{
	Vector<int> myVector;

	for ( size_t i = 1; i <= 10; i++ )
	{
		myVector.Push_back( i );
	}
	cout << myVector << endl;

	for ( size_t i = 1; i <= 5; i++ )
	{
		myVector.Pop_back();
	}
	cout << myVector << endl;

	cout << myVector.Capacity() << endl;
}
