#include <stdlib.h> /* malloc, size t */
#include "QueueGen.h" 

struct Queue
{
	void** m_que;
	size_t m_size;
	size_t m_head; /* index of head in m_que, from head we remove*/
	size_t m_tail; /* index of tail in m_que, from tail we insert */
	size_t m_nItems;
};

Queue* QueueCreate(size_t _size)
{
	Queue* qPtr = NULL;

	if(_size == 0 )
	{
		return NULL;
	}
	
	if((qPtr = (Queue*)malloc(sizeof(Queue))) == NULL) 
	{
		return NULL;
	}
	
	if ((qPtr->m_que= (void**)malloc(_size * sizeof(void*))) == NULL)
	{
		free(qPtr);
		return NULL;
	}

	qPtr->m_size = _size;
	qPtr->m_head = 0;
	qPtr->m_tail = 0;
	qPtr->m_nItems = 0;
	
	return qPtr;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t i;
	
	if(_queue != NULL && *_queue != NULL)
	{
		if(_itemDestroy != NULL)
		{	
			for(i=0; i < (*_queue)->m_nItems; ++i)
			{
				(*_itemDestroy)((*_queue)->m_que[i]);
			}
		}
		free((*_queue)->m_que);
		free(*_queue);
		*(_queue) = NULL;
	}
}

QueueResult QueueInsert(Queue* _queue, void* _item)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(_item == NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	
	if((_queue->m_tail == _queue->m_head) && (_queue->m_nItems != 0)) 
	{
		return QUEUE_OVERFLOW_ERROR;
	}

	_queue->m_que[_queue->m_tail] = _item;
	++_queue->m_nItems;
	_queue->m_tail = (_queue->m_tail+1) % (_queue->m_size);
	
	return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue,void** _item)
{
	if(_queue == NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(_item == NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	
	if(_queue->m_nItems == 0)
	{
		return QUEUE_UNDERFLOW_ERROR;
	}
	
	*_item = _queue->m_que[_queue->m_head];
	--_queue->m_nItems;
	_queue->m_head = (_queue->m_head+1) % (_queue->m_size);
	
	return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue)
{
	if(_queue == NULL || _queue->m_nItems == 0)
	{
		return 1;
	}
	return 0;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	size_t i;
	size_t head, size, nItem;
	
	if(_queue != NULL && _action!=NULL)
	{
		head = _queue->m_head;
		size =_queue->m_size;
		nItem = _queue->m_nItems;
		for(i = 0; i < nItem; ++i)
		{
           	if(_action(_queue->m_que[(i+head)%size], _context) == 0)
  			{
 				break;	
	 		}
		}
	}
	return i;
}
