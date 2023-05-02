#include "vectorGen.h"/*function signatures relating to vectorGen*/
#include <stdlib.h> /*malloc and realloc*/

#define CONSTANT_NUM 2

struct Vector
{
	void** m_items;
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size;/* actual allocated space for items*/
	size_t m_nItems;/* actual number of items */
	size_t m_blockSize;/* the chunk size to be allocated when no space*/
};

static VectorResult IncreaseVec(Vector* _vector);

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector *vec; 
	
	if(_initialCapacity==0 && _blockSize==0)
	{
		return NULL;
	}

	if ((vec = (Vector*)malloc(sizeof(Vector))) == NULL)
	{
		return NULL;
	}

	if ((vec->m_items= (void**)malloc(_initialCapacity * sizeof(void*))) == NULL)
	{
		free(vec);
		return NULL;
	}
	
	vec->m_originalSize = _initialCapacity;
	vec->m_size = _initialCapacity;
	vec->m_blockSize = _blockSize;
	vec->m_nItems = 0;
	return vec;
}

void VectorDestroy(Vector** _vector, ElementDestroy _element)
{
	size_t i;
	
	if(_vector != NULL && *_vector != NULL)
	{
		if(_element != NULL)
		{	
			for(i=0; i < (*_vector)->m_nItems; ++i)
			{
				(*_element)((*_vector)->m_items[i]);
			}
		}
		free((*_vector)->m_items);
		free(*_vector);
		*_vector = NULL;
	}
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
	VectorResult result;
	
	if(_vector == NULL || _item == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector->m_nItems == _vector->m_size)
	{
		if((result = IncreaseVec(_vector) != VECTOR_SUCCESS))
		{
			return result;
		}	
	}
	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems++;
	return VECTOR_SUCCESS;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	size_t newSize;
	void** temp;
	
	if(_vector==NULL || _pValue==NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	if(_vector->m_nItems==0)
	{
		return VECTOR_UNDERFLOW_ERROR;
	}
	
	*_pValue = _vector-> m_items[_vector->m_nItems-1];
	_vector->m_nItems--;
	if((_vector->m_size - _vector->m_nItems >= CONSTANT_NUM * _vector->m_blockSize) && 
	      (_vector->m_size - _vector->m_blockSize >= _vector->m_originalSize))
	{
		newSize = _vector->m_size - _vector->m_blockSize;
		temp = realloc(_vector->m_items,newSize*sizeof(void*));
		if(temp!=NULL)
		{
			_vector->m_items = temp;
			_vector->m_size = newSize;
		}
	}
	
	return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	if(_vector==NULL || _pValue==NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	if(_vector->m_nItems == 0)
	{
		return VECTOR_UNDERFLOW_ERROR;
	}
	
	if(_index > _vector->m_nItems-1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	*_pValue = _vector->m_items[_index];
	return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void* _value)
{
	if(_vector == NULL || _value == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}

	if(_vector->m_nItems == 0)
	{
		return VECTOR_UNDERFLOW_ERROR;
	}
	
	if(_index > _vector->m_nItems-1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector->m_items[_index] = _value;
	return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector)
{
	if(_vector==NULL)
	{
		return 0;
	}

	return _vector->m_nItems;
}

size_t VectorCapacity(const Vector* _vector)
{
	if(_vector == NULL)
	{
		return 0;
	}

	return _vector->m_size;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	size_t i;
	if (_vector != NULL && _action!=NULL)
	{
		for(i = 0; i < _vector->m_nItems; ++i)
		{
             if(_action(_vector->m_items[i], i, _context) == 0)
             {
 					break;	
 			 }
     	}
 		return i;
	}
}

static VectorResult IncreaseVec(Vector* _vector)
{
	void** temp;
	size_t newSize;
	
	if(_vector->m_blockSize==0)
	{
		return VECTOR_OVERFLOW_ERROR;
	}
	
	newSize = _vector->m_size + _vector->m_blockSize;
	if((temp = realloc(_vector->m_items,newSize*sizeof(void*))) == NULL)
	{
		return VECTOR_REALLOCATION_ERROR;
	}
	_vector->m_items = temp;
	_vector->m_size = newSize;
	return VECTOR_SUCCESS;
}
