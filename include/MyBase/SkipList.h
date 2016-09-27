#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "MyBase/Common.h"

template<typename Key>
class SkipList
{
private:
	struct Node;
public:
	SkipList();
	~SkipList();
	bool Insert(Key k);
	bool Contain(Key k) const;
	bool Delete(Key k);
	bool Clear();

private:
	Node * FindGE(Key k, Node ** prev) const;

private:
	enum { kMaxHeight = 3 };
	Node * m_head;
	uint32_t m_height;
};

template<typename Key>
struct SkipList<Key>::Node
{
	Key key;

	explicit Node(uint32_t h, const Key & k)
		:height(0), forwards(NULL) 
	{
		assert(h > 0); // 最低层数为1
		height = h;
		key = k;
		forwards = new Node *[height];
		memset(forwards, 0, height * sizeof(Node *));
	}
	~Node()
	{
		if (forwards)
		{
			delete[] forwards;
			forwards = NULL;
		}
		height = 0;
	}
	void SetNext(uint32_t level, Node * node)
	{
		assert(level < height);
		forwards[level] = node;
	}
	Node * Next(uint32_t level) const
	{
		assert(level < height);
		return forwards[level];
	}
	uint32_t Height() const
	{
		return height;
	}

private:
	uint32_t height;
	Node ** forwards;

	DISALLOW_COPYING(Node);
};


template<typename Key>
SkipList<Key>::SkipList()
{
	m_head = new Node(kMaxHeight, Key());
	m_height = kMaxHeight;
}

template<typename Key>
SkipList<Key>::~SkipList()
{
	Clear();
	delete m_head;
	m_head = NULL;
	m_height = 0;
}

template<typename Key>
bool SkipList<Key>::Insert(Key k)
{
	Node * prev[kMaxHeight] = {};
	Node * found = FindGE(k, prev);
	if (found != NULL && found->key == k) 
	{
		// 已经存在
		return false;
	}
	uint32_t height = abs(rand()) % (kMaxHeight-1) + 1;
	Node * new_node = new Node(height, k);
	for (size_t i = 0; i < height; ++i)
	{
		new_node->SetNext(i, prev[i]->Next(i));
		prev[i]->SetNext(i, new_node);
	}
	return true;
}

template<typename Key>
bool SkipList<Key>::Contain(Key k) const
{
	Node * found = FindGE(k, NULL);
	if (found == NULL)
	{
		return false;
	}

	if (found->key == k)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename Key>
bool SkipList<Key>::Delete(Key k)
{
	Node * prev[kMaxHeight] = {};
	Node * found = FindGE(k, prev);
	if (found == NULL)
	{
		// 没找到
		return false;
	}

	for (size_t i = 0; i < found->Height(); ++i)
	{
		prev[i]->SetNext(i, found->Next(i));
	}

	delete found;

	return true;
}

template<typename Key>
bool SkipList<Key>::Clear()
{
	Node * cur = m_head->Next(0);
	while (cur)
	{
		Node * tmp = cur;
		cur = cur->Next(0);
		delete tmp;
	}
	for (size_t i = 0; i < m_head->Height(); ++i)
	{
		m_head->SetNext(i, NULL);
	}
	return true;
}

template<typename Key>
typename SkipList<Key>::Node * SkipList<Key>::FindGE(Key k, Node ** prev) const
{
	int32_t level = kMaxHeight;
	Node * cur = m_head;
	while (--level >= 0)
	{
		while (cur->Next(level) && cur->Next(level)->key < k)
		{
			cur = cur->Next(level);
		}
		if (prev != NULL)
		{
			prev[level] = cur;
		}
	}

	return cur->Next(0);
}

#endif//SKIPLIST_H
