#include <stdlib.h>
#include "listFunc.h"
#include "../ListItr/listItr.h"


#define TRUE 1

typedef int(*InnearFunc)(int _status, void* _count);

typedef struct ListFlag
{
	ListActionFunction m_userFunc;
	void* m_userContext;
	InnearFunc m_innearFunc;
	void* m_innerContext;
} ListFlag;

static ListItr All(ListFlag* _flag, ListItr _begin, ListItr _end);
static int Find(int _status, void* _innerContext);
static int Count(int _status, void* _innerContext);
static int ForEach(int _status, void* _innerContext);

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListFlag flag;
	ListItr itr;
	
	if(_begin == NULL || _end == NULL || _predicate == NULL)
	{
		return NULL;
	}
	
	flag.m_innerContext = NULL;
	flag.m_innearFunc = Find;
	flag.m_userContext = _context;
	flag.m_userFunc = _predicate;
	itr = All(&flag, _begin, _end);
	return itr;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListFlag flag;
	size_t count = 0;
	
	if(_begin == NULL || _end == NULL || _predicate == NULL)
	{
		return 0;
	}
	
	flag.m_innerContext = &count;
	flag.m_innearFunc = Count;
	flag.m_userContext = _context;
	flag.m_userFunc = _predicate;
	All(&flag, _begin, _end);
	return count;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	ListFlag flag;
	ListItr itr = _begin;
	
	if(_begin == NULL || _end == NULL || _action == NULL)
	{
		return NULL;
	}

	flag.m_innerContext = NULL;
	flag.m_innearFunc = ForEach;
	flag.m_userContext = _context;
	flag.m_userFunc = _action;
	itr = All(&flag, _begin, _end);
	return itr;
	
	return All(_begin, _end, &flag);
}

static ListItr All(ListFlag* _flag, ListItr _begin, ListItr _end)
{
	int res, returnVal;
	ListItr current = _begin;

	while(current != _end)
	{
		res = (_flag->m_userFunc)(ListItrGet(current),_flag->m_userContext);
		returnVal = (_flag->m_innearFunc)(res, _flag->m_innerContext);
		if(returnVal == 0)
  		{
 			break;	
	 	}
	 	current = ListItrNext(current);
	 	
	}
	return current;
}

static int Find(int _status, void* _count)
{
	return !_status;;
}

static int Count(int _status, void* _count)
{
	if(_status)
	{
		*(size_t*)_count += 1;
	}
	return 1;
}

static int ForEach(int _status, void* _count)
{
	return _status;
}
