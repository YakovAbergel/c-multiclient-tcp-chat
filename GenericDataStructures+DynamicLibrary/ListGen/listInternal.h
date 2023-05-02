#ifndef __LISTINTERNAL_H__
#define __LISTINTERNAL_H__

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
};

void Remove(Node* _node);
void Insert(Node* _node, Node* _newNode);

#endif /* __LISTINTERNAL_H__ */
