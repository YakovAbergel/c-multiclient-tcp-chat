#include <stdlib.h>/*malloc*/
#include "listItr.h" 
#include "../ListGen/listGen.h"
#include "../ListGen/listInternal.h"

#define TRUE 1
#define FALSE 0
#define ERR_NULL -1
#define SWAP(x,y,t)\
		{          \
			t temp;\
			temp = x;\
			x = y; \
			y = temp; \
		}
		
ListItr ListItrBegin(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	
	return _list->m_head.m_next;
}

ListItr ListItrEnd(const List* _list)
{
	if(_list == NULL)
	{
		return NULL;
	}
	
	return (void*)&_list->m_tail;
}

int ListItrEquals(const ListItr _firstNode, const ListItr _secNode)
{
	return _firstNode == _secNode;
}

ListItr ListItrNext(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}	
	
	return (void*)(((Node*)_itr)->m_next);
}

ListItr ListItrPrev(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	
	if(((Node*)_itr)->m_prev->m_prev == ((Node*)_itr)->m_prev)
	{
		return _itr;
	}
	return ((Node*)_itr)->m_prev;
}

void* ListItrGet(ListItr _itr)
{
	if(_itr == NULL)
	{
		return NULL;
	}
	
	if(((Node*)_itr)->m_next == _itr)
	{
		return NULL;
	}			
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void* temp = NULL;
	
	if(_itr == NULL || _element == NULL || ((Node*)_itr)->m_next == _itr)
	{
		return NULL;
	}	
	temp = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return temp;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node* newNode = NULL;
	
	if(_itr == NULL || _element == NULL)
	{
		return NULL;
	}

	if((newNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return NULL;
	}
	
	newNode->m_data = _element;
	Insert((Node*)_itr, newNode);
	return newNode;
}

void* ListItrRemove(ListItr _itr)
{
	void* item = NULL;
	
	if(_itr == NULL || ((Node*)_itr)->m_next == _itr)
	{
		return NULL;
	}
	item = ((Node*)_itr)->m_data;
	Remove((Node*)_itr);
	free(_itr);
	return item;
}
