#pragma once
#include "Node.h" 
#include "Queue.h"
template <typename t1>
class PriorityQueue
{
private:

	
	Node<t1>* frontPtr;
public:
	PriorityQueue()
	{
		//backPtr = nullptr;
		frontPtr = nullptr;
	}
	bool isEmpty() const
	{
		if (frontPtr == nullptr)
			return true;
		else
			return false;
	}
	bool enqueue(const t1& newEntry)
	{
		Node<t1>* newNodePtr = new Node<t1>(newEntry);
		// Insert the new node
		if (isEmpty())
		{
			frontPtr = newNodePtr; // The queue is empty
		}

		else if (newEntry > frontPtr->getItem() || isEmpty())
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else
		{
			Node<t1>* ptr;
			ptr = frontPtr;
			while (ptr->getNext() != nullptr && ptr->getNext()->getItem() >= newEntry)
			{
				ptr = ptr->getNext();
			}
			newNodePtr -> setNext(ptr->getNext());
			ptr->setNext(newNodePtr);

		}
		return true;
	}
	bool dequeue(t1& frntEntry)
	{
		if (isEmpty())
			return false;
		else
		{
			Node<t1>* nodeToDeletePtr = frontPtr;
			frntEntry = frontPtr->getItem();
			frontPtr = frontPtr->getNext();
			delete nodeToDeletePtr;
		}

		return true;
	}
	bool RefreshThenDequeue(t1& out)   // when the values of the objects are changed after insertion
	{
		Queue<t1> tmp;
		t1 temp;
		while (dequeue(temp))
		{
			tmp.enqueue(temp);
			
		}
		while (tmp.dequeue(temp))
		{
			enqueue(temp);
		}
		return dequeue(out);
	}
	bool peekFront(t1& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}
	void print()
	{
		if (isEmpty())
		{
			cout << "PQ is empty";
		}
		else
		{
			NodePQ<t1, t2>* ptr;
			ptr = frontPtr;
			while (ptr != nullptr)
			{
				cout << ptr->getItem() << endl;
				ptr = ptr->getNext();

			}
		}
	}

	const t1* toArray(int& count)
	{
		count = 0;

		if (!frontPtr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<t1>* p = frontPtr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		t1* Arr = new t1[count];
		p = frontPtr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}


	~PriorityQueue()
	{

	}
};
