#pragma once
template <typename t1, typename t2>
class NodePQ
{
private:
	t1 item; // A data item
	t2 pri;
	NodePQ<t1, t2>* next; // Pointer to next node
public:
	NodePQ()
	{
		next = nullptr;
	}
	NodePQ(const t1& r_Item, const t2& newpri)
	{
		item = r_Item;
		pri = newpri;
		next = nullptr;

	}
	/*Node(const t1& r_Item, Node<t1>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}*/
	NodePQ(const t1& newItem, const t2& newpri, NodePQ<t1, t2>* nextNodePtr)
	{
		item = newItem;
		pri = newpri;
		next = nextNodePtr;
	}

	void setItem(const t1& r_Item)
	{
		item = r_Item;
	}
	void setNext(NodePQ<t1, t2>* nextNodePtr)
	{
		next = nextNodePtr;
	}
	void setPri(const t2& newPri)
	{
		pri = newPri;
	}
	t1 getItem() const
	{
		return item;
	}
	NodePQ<t1, t2>* getNext() const
	{
		return next;
	}
	t2 getPri() const
	{
		return pri;
	}
}; 


