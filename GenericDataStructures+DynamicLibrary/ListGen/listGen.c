#include <stdlib.h> /* malloc, size t */
#include "listGen.h"
#include "listInternal.h" 

List* ListCreate()
{
	List* list = NULL; 
	
	if ((list = (List*)malloc(sizeof(List))) == NULL)
	{
		return NULL;
	}
	
	list->m_head.m_next = &(list->m_tail);
	list->m_head.m_prev = &(list->m_head);
	list->m_tail.m_next = &(list->m_tail);
	list->m_tail.m_prev = &(list->m_head);
	
	return list;
}

void ListDestroy(List** _pList, ElementDestroy1 _item)
{
	Node* current = NULL;
  	Node* next = NULL;
  	
  	if(_pList != NULL && *_pList != NULL)
	{	
		current = (*_pList)->m_head.m_next;
		while(current != &((*_pList)->m_tail)) 
  		{
  			if(_item != NULL)
			{
    			(*_item)(current->m_data);
  			}
  			next = current->m_next;
			free(current);
  			current = next;
		}
		free(*_pList);
		*(_pList) = NULL;
	}
}

ListResult ListPushHead(List* _list, void* _item)
{
	Node* newNode = NULL;
	
    if(_list == NULL)
    {
    	return LIST_UNINITIALIZED_ERROR;
    }
    
    if(_item == NULL)
    {
    	return LIST_NULL_ELEMENT_ERROR;
    }
    
    if((newNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}

    newNode->m_data = _item;
    
	Insert(_list->m_head.m_next, newNode);
	
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list,  void* _item)
{
	Node* newNode = NULL;
	
	if(_list == NULL)
    {
    	return LIST_UNINITIALIZED_ERROR;
    }
    
    if(_item == NULL)
    {
    	return LIST_NULL_ELEMENT_ERROR;
    }
    
    if((newNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}

    newNode->m_data = _item;
    
	Insert(_list->m_tail.m_prev->m_next ,newNode);
	
	return LIST_SUCCESS;
}

ListResult ListPopHead(List* _list, void** _pItem)
{
	if(_list==NULL || _pItem == NULL)
    {
    	return LIST_UNINITIALIZED_ERROR;
    }

	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
    _pItem = _list->m_head.m_next->m_data;
    Remove(_list->m_head.m_next);
    
    return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem)
{
	if(_list==NULL || _pItem == NULL)
    {
    	return LIST_UNINITIALIZED_ERROR;
    }
	
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_UNDERFLOW_ERROR;
	}
	
    _pItem = _list->m_tail.m_prev->m_data;
    Remove(_list->m_tail.m_prev);
    
    return LIST_SUCCESS;
}	

size_t ListSize(const List* _list)
{
	Node* temp = NULL;
	size_t count = 0;
	
	if(_list==NULL)
	{
		return count; 
	}
	
	temp = _list->m_head.m_next;
	while(temp != &_list->m_tail)
	{
		++count;
		temp = temp->m_next;
	}
	
	return count;
}

void Remove(Node* _node)
{
	_node->m_next->m_prev = _node->m_prev;
	_node->m_prev->m_next = _node->m_next;
}

void Insert(Node* _node, Node* _newNode)
{
	_newNode->m_prev = _node->m_prev;
	_newNode->m_next = _node;
	_node->m_prev->m_next = _newNode;
	_node->m_prev = _newNode;
}
