#ifndef MYSTACK_INCLUDED
#define MYSTACK_INCLUDED

// Class Forward Declaration
template<typename T> class mystack;

// Output Operator Declaration
template<typename T>ostream& operator <<(ostream& out,const mystack<T> &a);

// Class Definition Begin...
template<typename T> class  mystack
{
    //  Definition of a "node" of the stack...
    struct mystack_node
    {
        T data;
        mystack_node* next;
        mystack_node(const T& d,mystack_node* n=NULL):data(d),next(n) {} //  Default Constructor of a node ...
    };

    //  Class Data Memebers...
    size_t stack_size;       // A variable keeping the record of number of nodes present in the stack
    mystack_node* stack_top;       //  A pointer pointing to the top of the stack


    void mystack_swap(mystack &a,mystack &b)  //  Swap function used in the assignment operator ( Copy-and-Swap Idiom )
    {
        swap(a.stack_size,b.stack_size);
        swap(a.stack_top,b.stack_top);
    }

    mystack_node* recurse_copy(const mystack_node* head)  //  Helper for Copy Constructor
    {
        if(head==NULL)
            return NULL;
        mystack_node* n=new mystack_node(head->data);
        n->next=recurse_copy(head->next);
        return n;
    }
public:
    mystack():stack_size(0),stack_top(NULL) {}                   //  Default Constructor

    mystack(const mystack& other):stack_size(other.stack_size),stack_top(NULL)  //  Copy constructor
    {
        stack_top=recurse_copy(other.stack_top);
    }

    ~mystack()  //  Destructor
    {
        mystack_node* temp=stack_top;
        while(temp!=NULL)
        {
            temp=temp->next;
            delete stack_top;
            stack_top=temp;
        }
    }

    mystack& operator = (mystack other)  // Assignment operator
    {
        mystack_swap(*this,other);
        return *this;
    }


    void push(const T &val)              // Add a new node to the stack
    {
        stack_top=new mystack_node(val,stack_top);
        stack_size++;
    }

    void pop()                           //  Remove the "top" node from the stack
    {
        if(stack_top!=NULL)              //  Don't do anything if the stack is already empty
        {
            mystack_node* temp=stack_top;
            stack_top=stack_top->next;
            stack_size--;
            delete temp;
        }
    }

    size_t size() const                // Returns the number of nodes in the stack
    {
        return stack_size;
    }

    bool empty() const                          // Returns whether if the stack is empty or not
    {
        return stack_size==0;
    }

    T& top ()                     // Returns the "top" node from the stack
    {
        return stack_top->data;         // Deliberately left Out-of-Bound exception checking...
    }

    const T& top() const
    {
        return stack_top->data;
    }

    //  Friend function Declaration
    friend ostream& operator << <> (ostream&,const mystack<T>&);
};

// Output Operator Definition...
template<typename T>ostream& operator <<(ostream& out,const mystack<T> &a)
{
    typename mystack<T>::mystack_node* temp=a.stack_top;
    while(temp!=NULL)
    {
        out<<temp->data<<" ";
        temp=temp->next;
    }
    return out;
}

#endif // MYSTACK_INCLUDED
