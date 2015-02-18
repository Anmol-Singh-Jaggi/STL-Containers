#include<bits/stdc++.h>
using namespace std;


// MYSTACK BEGINS...


// Class Forward Declaration
template<typename T> class mystack;

// Declarations For Friend Functions...
template<typename T> ostream& operator <<( ostream& out, const mystack<T> &a );

// Class Definition Begin...
template<typename T> class  mystack
{
	//  Definition of a "node" of the stack...
	struct mystack_node
	{
		T data;
		mystack_node* next;
		mystack_node( const T& d, mystack_node* n = nullptr ): data( d ), next( n ) {} //  Default Constructor of a node ...
	};

	//  Class Data Memebers...
	size_t stack_size;       // A variable keeping the record of number of nodes present in the stack
	mystack_node* stack_top;       //  A pointer pointing to the top of the stack

	// Utility Fcuntions...
	void mystack_swap( mystack &a, mystack &b ); //  Swap function used in the assignment operator ( Copy-and-Swap Idiom )
	mystack_node* recurse_copy( const mystack_node* head ); //  Helper for Copy Constructor

	//  Friend function Declaration
	friend ostream& operator << <> ( ostream&, const mystack& );

public:

	// Constructors/Destructors...
	mystack();// Constructor...
	mystack( const mystack& other ); // Copy Constructor...
	~mystack();  // Destructor

	// Assignment operator...
	mystack& operator = ( mystack other );

	// Stack-Specific routines...
	void push( const T &val ); // Add a new node to the stack...
	void pop();  // Remove the "top" node from the stack...
	size_t size() const;  // Returns the number of nodes in the stack...
	bool empty() const;   // Returns whether if the stack is empty or not...
	T& top();    // Returns the "top" node from the stack...
	const T& top() const;
};

// Utility Function Definitions...
template<typename T>
void mystack<T>::mystack_swap( mystack<T> &a, mystack<T> &b )
{
	swap( a.stack_size, b.stack_size );
	swap( a.stack_top, b.stack_top );
}

template<typename T>
typename mystack<T>::mystack_node* mystack<T>::recurse_copy( const mystack_node* head )
{
	if ( head == nullptr )
	{
		return nullptr;
	}
	mystack_node* n = new mystack_node( head->data );
	n->next = recurse_copy( head->next );
	return n;
}


// Constructors/Destructors...
template<typename T>
mystack<T>::mystack()
{
	stack_size = 0;
	stack_top = nullptr;
}

template<typename T>
mystack<T>::mystack( const mystack& other )
{
	stack_size = other.stack_size;
	stack_top = recurse_copy( other.stack_top );
}

template<typename T>
mystack<T>::~mystack()
{
	mystack_node* temp = stack_top;
	while ( temp != nullptr )
	{
		temp = temp->next;
		delete stack_top;
		stack_top = temp;
	}
}


// Assignment Operator Definition...
template<typename T>
mystack<T>& mystack<T>::operator = ( mystack<T> other )
{
	mystack_swap( *this, other );
	return *this;
}


// Stack-specific Routine Implementations...
template<typename T>
void mystack<T>::push( const T &val )
{
	stack_top = new mystack_node( val, stack_top );
	stack_size++;
}

template<typename T>
void mystack<T>::pop()
{
	if ( stack_top != nullptr )
	{
		mystack_node* temp = stack_top;
		stack_top = stack_top->next;
		stack_size--;
		delete temp;
	}
}

template<typename T>
size_t mystack<T>::size() const
{
	return stack_size;
}

template<typename T>
bool mystack<T>::empty() const
{
	return size() == 0;
}

template<typename T>
T& mystack<T>::top()
{
	return stack_top->data;  // Deliberately left Out-of-Bound exception checking...
}

template<typename T>
const T& mystack<T>::top() const
{
	return stack_top->data;
}


// Output Operator Definition...
template<typename T>
ostream& operator <<( ostream& out, const mystack<T>& obj )
{
	out << "[";
	mystack<T> temp( obj );
	while ( !temp.empty() )
	{
		out << temp.top() << ", ";
		temp.pop();
	}
	if ( obj.size() )
	{
		out << "\b\b";
	}
	out << "]";
	return out;
}


// MYSTACK ENDS...

// Usage...
int main()
{
	mystack<int> a;
	a.push( 1 );
	a.push( 2 );
	a.push( 3 );
	cout << a << a;
}
