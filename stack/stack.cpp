#include<iostream>
#include<new>
using namespace std;

// STACK BEGINS

// Class forward declaration
template<typename T> class Stack;

// Declarations for friend functions
template<typename T> ostream& operator <<( ostream& out, const Stack<T>& myStack );

// Class definition begins
template<typename T> class Stack
{
	// Definition of a "node" of the stack
	struct StackNode
	{
		T data;
		StackNode* next;
		StackNode( const T& _data, StackNode* _next = nullptr ): data( _data ), next( _next ) {}
	};

	// Class data members
	size_t stackSize;
	StackNode* stackTop;

	// Utility functions
	// Swap function used in the assignment operator ( Copy-and-Swap Idiom )
	void swap( Stack& first, Stack& second );
	// Helper for the copy constructor
	StackNode* DeepCopy( const StackNode* head );

	// Friend function declaration
	friend ostream& operator << <> ( ostream&, const Stack& );

public:

	Stack();
	Stack( const Stack& other );
	~Stack();

	Stack& operator = ( Stack other );

	// Stack-specific routines
	void Push( const T& val );
	void Pop();
	size_t Size() const;
	bool Empty() const;
	T& Top();
	const T& Top() const;
};

// Utility function definitions
template<typename T>
void Stack<T>::swap( Stack<T>& first, Stack<T>& second )
{
	swap( first.stackSize, second.stackSize );
	swap( first.stackTop, second.stackTop );
}

template<typename T>
typename Stack<T>::StackNode* Stack<T>::DeepCopy( const StackNode* head )
{
	if ( head == nullptr )
	{
		return nullptr;
	}

	StackNode* newHead = new StackNode( head->data );

	StackNode* newHeadIt = newHead;
	const StackNode* headIt = head;

	while ( headIt->next != nullptr )
	{
		newHeadIt->next = new StackNode( headIt->next->data );

		newHeadIt = newHeadIt->next;
		headIt = headIt->next;
	}

	return newHead;
}


template<typename T>
Stack<T>::Stack()
{
	stackSize = 0;
	stackTop = nullptr;
}

template<typename T>
Stack<T>::Stack( const Stack& other )
{
	stackSize = other.stackSize;
	stackTop = DeepCopy( other.stackTop );
}

template<typename T>
Stack<T>::~Stack()
{
	StackNode* it = stackTop;

	while ( it != nullptr )
	{
		it = it->next;
		delete stackTop;
		stackTop = it;
	}

	stackSize = 0;
}


template<typename T>
Stack<T>& Stack<T>::operator = ( Stack<T> other )
{
	swap( *this, other );
	return *this;
}


template<typename T>
void Stack<T>::Push( const T& val )
{
	stackTop = new StackNode( val, stackTop );
	stackSize++;
}

template<typename T>
void Stack<T>::Pop()
{
	if ( stackTop != nullptr )
	{
		StackNode* stackTopBak = stackTop;
		stackTop = stackTop->next;
		stackSize--;
		delete stackTopBak;
	}
}

template<typename T>
size_t Stack<T>::Size() const
{
	return stackSize;
}

template<typename T>
bool Stack<T>::Empty() const
{
	return Size() == 0;
}

template<typename T>
T& Stack<T>::Top()
{
	// Deliberately left out-of-bound exception checking
	return stackTop->data;
}

template<typename T>
const T& Stack<T>::Top() const
{
	return stackTop->data;
}


template<typename T1>
ostream& operator <<( ostream& out, const Stack<T1>& object )
{
	Stack<T1> object_copy( object );
	const char* separator = "";

	out << "[";
	while ( !object_copy.Empty() )
	{
		out << separator;
		out << object_copy.Top();
		object_copy.Pop();
		separator = ", ";
	}
	out << "]";

	return out;
}

// STACK ENDS


// Usage
int main()
{
	Stack<int> myStack;

	for ( size_t i = 1; i <= 10; i++ )
	{
		myStack.Push( i );
	}

	myStack.Pop();

	cout << myStack << endl;
}
