#pragma once
#include "Generic_DS/Node.h"
template<typename T>
class Stack
{
private:
	Node<T>* top;

public:
	Stack();
	bool isEmpty() const;
	bool push(const T& newEntry);
	bool pop(T & out);
	bool peek(T& TopEntry);
	void print();
	const T* toArray(int& count);
};

template<typename T>
Stack<T>::Stack()
{
	top = nullptr;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	if (top == nullptr)
		return true;
	else
		return false;
}

template<typename T>
bool Stack<T>::push(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	if (isEmpty())
	{
		top = newNodePtr;
		newNodePtr->setNext(nullptr);
	}
	else
	{
		newNodePtr->setNext(top);
		top = newNodePtr;
	}
	return true;
}

template<typename T>
bool Stack<T>::pop(T& out )
{
	if (isEmpty())
	{
		return false;
	}
	else
	{
		Node<T>* ptr;
		ptr = top;
		top = top->getNext();
		out = ptr;
		
	}
	return true;
}

template<typename T>
bool Stack<T>::peek(T& TopEntry)
{
	if (isEmpty())
	{
		return false;
	}
	else
	{
		TopEntry = top->getItem();
	}
	return true;
}

template<typename T>
void Stack<T>::print()
{
	if (isEmpty())
	{
		cout << "stack is empty";
	}
	else
	{
		Node<T>* ptr;
		ptr = top;
		while (ptr != nullptr)
		{
			cout << ptr->getItem() << endl;
			ptr = ptr->getNext();

		}
	}
}
template <typename T>
const T* Stack<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count = 0;

	if (!top)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = top;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = top;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;

}
