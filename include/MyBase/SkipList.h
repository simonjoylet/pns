#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "MyBase/Common.h"
#include "MyBase/Random.h"

namespace pns
{ 

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
	uint32_t Size() const { return m_count; }

private:
	Node * FindGE(Key k, Node ** prev) const;
	uint32_t RandomHeight();

private:
	enum { kMaxHeight = 32 };
	Node * m_head;
	uint32_t m_height;
	uint32_t m_count;
	Random m_random;

	DISALLOW_COPYING(SkipList);
};


/************** 下面是具体实现 ***************/

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
	: m_height(kMaxHeight)
	, m_count(0)
	, m_random(0xdeadbeef)
{
	m_head = new Node(kMaxHeight, Key());
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
	//uint32_t height = m_random.Next() % (kMaxHeight-1) + 1;
	uint32_t height = RandomHeight();
	Node * new_node = new Node(height, k);
	for (size_t i = 0; i < height; ++i)
	{
		new_node->SetNext(i, prev[i]->Next(i));
		prev[i]->SetNext(i, new_node);
	}
	++m_count;
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
	--m_count;

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
	m_count = 0;
	return true;
}

template<typename Key>
typename SkipList<Key>::Node * SkipList<Key>::FindGE(Key k, Node ** prev) const
{
	int32_t level = kMaxHeight;
	Node * cur = m_head;
	while (--level >= 0)
	{
		// 当前高度如果next->key都比 k 要小，则cur要一直往后跳。
		Node * next = cur->Next(level);
		while (next && next->key < k)
		{
			cur = next;
			next = cur->Next(level);
		}
		// 当前高度next->key >= k
		if (prev != NULL)
		{
			prev[level] = cur;
		}
	}

	return cur->Next(0); // 最底层的链表的下一个
}

template<typename Key>
uint32_t SkipList<Key>::RandomHeight()
{
	// 	// 我自己设计的基于查表的方法，只需要一次随机数运算 
	// 	static uint32_t section[kMaxHeight] = { 0 };
	// 	static bool init_flag = false;
	// 	if (!init_flag)
	// 	{
	// 		for (size_t i = 0; i < kMaxHeight; ++i)
	// 		{
	// 			section[i] = 1 << i;
	// 		}
	// 		init_flag = true;
	// 	}
	// 	
	// 	uint32_t rand_num = m_random.Next();
	// 	for (uint32_t i = 2; i < kMaxHeight - 1; ++i)
	// 	{
	// 		if (rand_num > section[kMaxHeight - i])
	// 		{
	// 			return i;
	// 		}
	// 	}
	// 	return 1;

	// 参照谷歌的高度随机算法，期望上需要2次随机数运算
	static const uint32_t kBranching = 2; // 模拟二叉树，log2(N)
	int height = 1;
	while (height < kMaxHeight && ((m_random.Next() % kBranching) == 0))
	{
		height++;
	}
	assert(height > 0);
	assert(height <= kMaxHeight);
	return height;
}
} // namespace pns

#endif//SKIPLIST_H
