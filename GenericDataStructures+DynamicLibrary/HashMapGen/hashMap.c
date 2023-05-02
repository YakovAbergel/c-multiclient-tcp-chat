#include <stdlib.h>/*calloc*/
#include <math.h>/*sqrt*/
#include "../ListFunc/listFunc.h"
#include "../ListItr/listItr.h"
#include "../ListGen/listGen.h"
#include "hashMap.h"

#define TRUE 1
#define FALSE 0

struct HashMap
{
	List** m_data;
	HashFunction m_hashFunction;
	EqualityFunction m_equalityFunction;
	size_t m_hashSize; /*original size given by the client*/
	size_t m_capacity; /*real hash size */
	size_t m_numOfItems; /*number of occupied places in the table*/
};

typedef struct Item
{
    void* m_key;
    void* m_value;
} Item;

typedef struct FindFirstInfo
{
    void* m_userContext;
    EqualityFunction m_userFunc;
}FindFirstInfo;

typedef struct Info
{
    void* m_userContext;
    KeyValueActionFunction m_userFunc;
    size_t m_counter;
}Info;


typedef struct DestroyFuncs
{
    KeyDestroy m_keydestroy;
    ValDestroy m_valDestroy;
}DestroyFuncs;

static Item* Create_Item(HashMap* _map, const void* _key, const void* _value);
static size_t FindSmallestForPrime(size_t _num);
static size_t IsPrime(size_t _num);
static int IsDuplicate(EqualityFunction _keysEqualFunc, List* _list, const void* _key, ListItr* _itr);
static int ForEachDestroy(void* _element, void* _info);
static int FindFirstAction (void* _element, void* _info);
static int ForEachAction (void* _element, void* _info);

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hash = NULL;
	size_t newSize;
	
	if(_capacity < MIN_CAPASITY || _hashFunc == NULL || _keysEqualFunc == NULL)
	{
		return NULL;
	}
	
	if((hash = (HashMap*)malloc(sizeof(HashMap))) == NULL)
	{
		return NULL;
	}
	
	newSize = _capacity + FindSmallestForPrime(_capacity);
	
	if((hash->m_data = (List**)calloc(newSize, sizeof(List*))) == NULL)
	{
		free(hash);
		return NULL;
	}
	
	hash->m_hashFunction = _hashFunc;
	hash->m_equalityFunction = _keysEqualFunc;
	hash->m_hashSize = _capacity;
	hash->m_capacity = newSize;
	hash->m_numOfItems = 0;
	
	return hash;
}

void HashMap_Destroy(HashMap **_map, KeyDestroy _keyDestroy, ValDestroy _valDestroy)
{
    size_t i;
    ListItr begin=NULL, end = NULL;
    DestroyFuncs destroyFuncs;
    
    if (_map ==NULL || *_map == NULL)
    {
        return; 
    }
    
    destroyFuncs.m_keydestroy = _keyDestroy;
    destroyFuncs.m_valDestroy = _valDestroy;
    for (i = 0; i < (*_map)->m_capacity; ++i)
    {
        if ((*_map)->m_data[i] != NULL)
        {
            begin = ListItrBegin((*_map)->m_data[i]);
            end = ListItrEnd((*_map)->m_data[i]);
            ListItrForEach(begin, end, ForEachDestroy, &destroyFuncs);
            ListDestroy(&(*_map)->m_data[i], NULL);
        }
    }
    free(*_map);
    *_map = NULL;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
	int index;
	Item* item = NULL;
	List* list = NULL;
	ListItr itr = NULL;
	
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	if((item = Create_Item(_map, _key, _value)) == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	index = ((*_map->m_hashFunction)((void*)_key)) % (_map->m_capacity);
	if((list = _map->m_data[index]) == NULL)
	{
		if((list = ListCreate()) == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
		_map->m_data[index] = list;
	}
	else if(IsDuplicate(_map->m_equalityFunction, _map->m_data[index], _key, &itr))
    {
        return MAP_KEY_DUPLICATE_ERROR;
    }

	if(ListPushHead(list, item) != LIST_SUCCESS)
	{
		return MAP_ALLOCATION_ERROR;
	}
	++_map->m_numOfItems;
	return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	int index;
	Item* item = NULL;
	List* list = NULL;
	ListItr itr = NULL;
	
	if(_map == NULL || _pKey == NULL || _pValue == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_searchKey == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = ((*_map->m_hashFunction)((void*)_searchKey)) % (_map->m_capacity);
	if((list = _map->m_data[index]) == NULL || !IsDuplicate(_map->m_equalityFunction, _map->m_data[index], _searchKey, &itr))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	item =(Item*)ListItrRemove(itr);
    *_pKey = item->m_key;
    *_pValue = item->m_value;
	--_map->m_numOfItems;
	return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
	int index;
	Item* item = NULL;
	List* list = NULL;
	ListItr itr = NULL;
	
	if(_map == NULL || _pValue == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_key == NULL )
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = ((*_map->m_hashFunction)((void*)_key)) % (_map->m_capacity);
	if((list = _map->m_data[index]) == NULL || !IsDuplicate(_map->m_equalityFunction, _map->m_data[index], _key, &itr))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
    *_pValue = ListItrGet (itr);
    *_pValue = ((Item*)*_pValue) -> m_value;
    	
	return MAP_SUCCESS;
}

size_t HashMap_Size(const HashMap* _map)
{
	if(_map == NULL)
	{
		return 0;
	}
	
	return _map->m_numOfItems;
}

size_t HashMap_ForEach(const HashMap *_map, KeyValueActionFunction _action, void *_context)
{
    size_t i = 0;
    ListItr begin = NULL, end = NULL, itr = NULL;
    Info info;
    
    if (_map == NULL || _action == NULL)
    {
        return 0;
    }
    
    info.m_counter = 0;
    info.m_userContext = _context;
    info.m_userFunc = _action;
    for (i = 0; i < _map->m_capacity; i++)
    {
        if(_map->m_data[i] != NULL)
        {
            begin = ListItrBegin(_map->m_data[i]);
            end = ListItrEnd(_map->m_data[i]);
            itr = ListItrForEach(begin, end, ForEachAction, &info);
            if (itr != end)
            {
                break;
            }
        }     
    }
    return info.m_counter;
}


static Item* Create_Item(HashMap* _map, const void* _key, const void* _value)
{
    Item* item;
    if((item = (Item*)malloc(sizeof(Item))) == NULL)
    {
    	return NULL;
    }
    
    item->m_key = (void*)_key;
    item->m_value = (void*)_value;
    return item;
}

static int ForEachDestroy(void* _element, void* _info)
{
    DestroyFuncs* destroyFuncs;
    Item* item;
    destroyFuncs = (DestroyFuncs*)_info;
    item = (Item*)_element;
    if (destroyFuncs->m_keydestroy != NULL)
    {
      (*destroyFuncs->m_keydestroy)(item->m_key);
    }
    if (destroyFuncs->m_valDestroy != NULL)
    {
      (*destroyFuncs->m_valDestroy)(item->m_value);
    }
    return 1;
}

static int IsDuplicate(EqualityFunction _keysEqualFunc, List* _list, const void* _key, ListItr* _itr)
{
    ListItr begin=NULL,  end=NULL, checkedItr=NULL;
    FindFirstInfo info;
    begin = ListItrBegin(_list);
    end = ListItrEnd(_list);
    if(ListItrEquals(begin, end))
    {
        *_itr = end;
        return FALSE;
    }
    info.m_userContext = (void*)_key;
    info.m_userFunc = _keysEqualFunc;
    checkedItr = ListItrFindFirst(begin, end, FindFirstAction, &info);
    if (ListItrEquals(checkedItr, end))
    {
        *_itr= end;
        return FALSE;
    }
    *_itr = checkedItr;
    return TRUE;
}

static int FindFirstAction (void* _element, void* _info)
{
    Item* item;
    FindFirstInfo* info;
    int result = 0;
    
    info = (FindFirstInfo*)_info;
    item = (Item*)_element;
    result = (info->m_userFunc)(item->m_key,info->m_userContext);
    
    return result;
}

static int ForEachAction (void* _element, void* _info)
{
    Item* item;
    Info* info;
    int result = 0;
    info = (Info*)_info;
    item = (Item*)_element;
    result = (info->m_userFunc)(item->m_key,item->m_value,info->m_userContext);
    info->m_counter += 1;
    return result;
}

static size_t FindSmallestForPrime(size_t _num)
{
	size_t prime = _num;
	
	while(!IsPrime(prime))
	{
		++prime;
	}
  
    return prime;
}

static size_t IsPrime(size_t _num)
{
	size_t i, sq; 
	sq = sqrt(_num); 

    if(_num % 2 == 0)
    {
        return FALSE;
    }

    for(i = 3; i < sq; i = i + 2)
    {
        if (_num % i == 0)
        {
            return FALSE;
  		}
  	}

    return TRUE;
}
