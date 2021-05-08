#pragma once
#include "NodePQ.h" 
template <typename t1, typename t2>
class PriorityQueue
{
private:

	//NodePQ<t1, t2>* backPtr;
	NodePQ<t1, t2>* frontPtr;
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
	bool enqueue(const t1& newEntry, const t2& newPri)
	{
		NodePQ<t1, t2>* newNodePtr = new NodePQ<t1, t2>(newEntry, newPri);
		// Insert the new node
		if (isEmpty())
		{
			frontPtr = newNodePtr; // The queue is empty
		}

		else if (newPri > frontPtr->getPri() || isEmpty())
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else
		{
			NodePQ<t1, t2>* ptr;
			ptr = frontPtr;
			while (ptr->getNext() != nullptr && ptr->getNext()->getPri() >= newPri)
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
			NodePQ<t1, t2>* nodeToDeletePtr = frontPtr;
			frntEntry = frontPtr->getItem();
			frontPtr = frontPtr->getNext();
			delete nodeToDeletePtr;
		}

		return true;
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
		NodePQ<t1, t2>* p = frontPtr;
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
