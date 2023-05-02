#include "heapGen.h" /*function signatures relating to heapGen*/
#include "../VectorGen/vectorGen.h" /*function signatures relating to vectorGen*/

#include <stdlib.h> /*malloc and free*/


#define PARENT(i) ((i)-1)/2
#define LEFT(i) (2*(i) + 1)
#define RIGHT(i) (2*(i) + 2)
#define LAST_PARENT(i) ((i-1)/2) 

struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	LessThanComparator m_pfLess;
};

static void HeapIncreaseKey(Heap* _heap, size_t _index, void* _key);
static void Heapify(Heap* _heap, size_t _index);
static void Swap(Heap* _heap, size_t _i, size_t _j, void* _f, void* _s);

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	Heap* heap = NULL;
	size_t size, i, j;
	
	if(_vector == NULL || _pfLess == NULL)
	{
		return NULL;
	}
	
	if ((heap = (Heap*)malloc(sizeof(Heap))) == NULL)
	{
		return NULL;
	}
	
	heap->m_heapSize = VectorSize(_vector);
	heap->m_vec = _vector;
	heap->m_pfLess = _pfLess;
	i = heap->m_heapSize-1;
	
	if(heap->m_heapSize > 1)
	{
		for(j = LAST_PARENT(i); j > 0; --j)
		{
			Heapify(heap, j);
		}
		Heapify(heap, 0);
	}
	
	return heap;
}

Vector* HeapDestroy(Heap** _heap)
{
	Vector* vec = NULL;
	if(_heap != NULL && *_heap != NULL)
	{
		vec = (*_heap)->m_vec;
		free(*_heap);
		*_heap = NULL;
	}
	return vec;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
	HeapResultCode res;
	
	if(_heap == NULL || _element == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	
	if(res = VectorAppend(_heap->m_vec, _element) != VECTOR_SUCCESS)
	{
		return HEAP_REALLOCATION_FAILED;
	}
	
	++_heap->m_heapSize;
	HeapIncreaseKey(_heap, _heap->m_heapSize-1, _element);
	
	return HEAP_SUCCESS;
}

const void* HeapPeek(const Heap* _heap)
{
	VectorResult res;
	const void* element;
	void* temp;
	
	if(_heap == NULL)
	{
		return NULL;
	}
	
	if((res = VectorGet(_heap->m_vec, 0, &temp) != VECTOR_SUCCESS))
	{
		return NULL;
	}
	element = temp;
	return element;
}

void* HeapExtract(Heap* _heap)
{
	VectorResult res;
	void* root;
	void* lastNum;
	
	if(_heap == NULL)
	{
		return NULL;
	}

	if((res = VectorGet(_heap->m_vec, 0, &root)) != VECTOR_SUCCESS)
	{
		return NULL;
	}
	
	if((res = VectorRemove(_heap->m_vec,&lastNum)) != VECTOR_SUCCESS)
	{
	 	return NULL;
	}
	
	--_heap->m_heapSize;
	VectorSet(_heap->m_vec, 0, (void*)lastNum);
	Heapify(_heap, 0);
	
	return root;
}

size_t HeapSize(const Heap* _heap)
{
	if(_heap == NULL)
	{
		return 0;
	}
	
	return VectorSize(_heap->m_vec);
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t i;
	void* elem;
	if (_heap != NULL && _act!=NULL)
	{
		for(i = 0; i < _heap->m_heapSize; ++i)
		{
			VectorGet(_heap->m_vec, i, &elem);
           	if(_act(elem,_context) == 0)
  			{
 				break;	
	 		}
		}
	}
	return i;
}

static void HeapIncreaseKey(Heap* _heap, size_t _index, void* _key)
{
	void* son;
	void* parent;
	
	VectorSet(_heap->m_vec, _index, _key);
	VectorGet(_heap->m_vec, PARENT(_index), (void**)&parent);
	VectorGet(_heap->m_vec, _index, &son);
	
	while(_index>0 && ((*(_heap->m_pfLess))(parent,son)) == FALSE)
	{
		Swap(_heap, _index, PARENT(_index), son, parent);
		_index = PARENT(_index);
		VectorGet(_heap->m_vec, PARENT(_index), &parent);
	}
}

static void Heapify(Heap* _heap, size_t _index)
{
	size_t largest, left = LEFT(_index), right = RIGHT(_index);
	void* leftSon;
	void* rightSon;
	void* parent;
	void* max;

	VectorGet(_heap->m_vec, left, (void**)&leftSon);
	VectorGet(_heap->m_vec, right, (void**)&rightSon);
	VectorGet(_heap->m_vec, _index, (void**)&parent);

	if(left < _heap->m_heapSize && ((*(_heap->m_pfLess))(leftSon,parent)) == TRUE)
	{
		largest = left;
		max = leftSon;
	}
	else
	{
		largest = _index;
		max = parent;
	}

	if(right < _heap->m_heapSize && ((*(_heap->m_pfLess))(rightSon,max)) == TRUE)
	{
		largest = right;
		max = rightSon;
	}

	if(largest != _index)
	{
		Swap(_heap, _index, largest, (void*)parent, (void*)max);
		Heapify(_heap, largest);
	}
}

static void Swap(Heap* _heap, size_t _i, size_t _j, void* _f, void* _s)
{
	VectorSet(_heap->m_vec,_i,_s);
	VectorSet(_heap->m_vec,_j,_f);
}
