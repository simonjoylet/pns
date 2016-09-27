#ifndef LIST_H
#define LIST_H

#include "MyBase/Common.h"

namespace pns
{

template<typename Key>
class List
{
private:
	struct Node;
public:
	List() :m_count(0), m_head(NULL) {}
	~List() { Clear(); }
	bool Insert(Key k);
	bool Contain(Key k) const;
	bool Delete(Key k);
	bool Clear();
	uint32_t Size() const { return m_count; }

private:
	Node * m_head;
	uint32_t m_count;
};

/************** 下面是具体实现 ***************/

template<typename Key>
struct List<Key>::Node
{
	Key key;
	Node * next;
	explicit Node(const Key & k) :key(k), next(NULL) {}
};

template<typename Key>
bool List<Key>::Insert(Key k)
{
	if (m_head == NULL)
	{
		m_head = new Node(k);
		++m_count;
		return true;
	}

	if (m_head->key == k)
	{
		return false;
	}

	Node * cur = m_head;
	while (cur->next && cur->next->key < k)
	{
		cur = cur->next;
	}

	if (cur->next == NULL)
	{
		cur->next = new Node(k);
		++m_count;
		return true;
	}
	else
	{
		if (cur->next->key == k)
		{
			return false;
		}
		else
		{
			Node * new_node = new Node(k);
			new_node->next = cur->next;
			cur->next = new_node;
			++m_count;
			return true;
		}

	}

}

template<typename Key>
bool List<Key>::Contain(Key k) const
{
	Node * cur = m_head;
	while (cur)
	{
		if (cur->key == k)
		{
			return true;
		}
		cur = cur->next;
	}
	return false;
}

template<typename Key>
bool List<Key>::Delete(Key k)
{
	if (m_head == NULL)
	{
		return false;
	}

	if (m_head == k)
	{
		Node * tmp = m_head;
		m_head = m_head->next;
		delete tmp;
		--m_count;
		return true;
	}

	Node * cur = m_head;
	while (cur->next && cur->next->key != k)
	{
		cur = cur->next;
	}
	if (cur->next == NULL)
	{
		return false;
	}
	else
	{
		Node * tmp = cur->next;
		cur->next = cur->next->next;
		delete tmp;
		--m_count;
		return true;
	}
}

template<typename Key>
bool List<Key>::Clear()
{
	Node * cur = m_head;
	while (cur)
	{
		Node * tmp = cur;
		cur = cur->next;
		delete tmp;
	}
	m_head = NULL;
	m_count = 0;
	return false;
}

} // namespace pns
#endif//LIST_H


