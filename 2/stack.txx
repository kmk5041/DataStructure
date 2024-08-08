//
// Assignment 2 : Simple calculator using Stack
//
// Array-based stack data structure
//
// COSE213 Fall 2021
//

template<class type>
Stack<type>::~Stack()
{
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	if(IsEmpty()){
	throw "Error: Stack is Empty";
	}
	else
		return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
	if(top<capacity-1){
		top++;
		array[top]=item;
		}
	else {
		type* array_=new type[capacity*2];
		for (int i=0; i<=top; i++) {
			array_[i]=array[i];
		}
	array_[top+1]=item;
	top++;
	capacity*=2;
	delete[] array;
	array=new type[capacity];
	for(int i=0; i<=top; i++)
	{
		array[i]=array_[i];
	}
	delete[] array_;
	}
}

template<class type>
void Stack<type>::Pop()
{
	if(IsEmpty())
		throw "Error: Stack is empty";
	else{
		top--;
	}
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	if(top==-1)	
		return true;
	else
		return false;
}

