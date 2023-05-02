#include <stdio.h>
#include "listFunc.h"
#include "../ListItr/listItr.h"
#include "../ListGen/listGen.h"
#include "../ListGen/listInternal.h"

static int PrintForEach(void* _element, void* _context);
static int Predicate(void* _element, void* _context);

int main()
{
	List* list = NULL;
	int aa = 4;
	int bb = 3;
	int cc = 2;
	int dd = 1;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	Node* n4;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushHead(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrBegin(list);
	n2 = ListItrEnd(list);
	n3 = ListItrPrev(n2);
	printf("%d\n",*(int*)(ListItrGet(n1)));
	printf("%d\n",*(int*)(ListItrGet(n3)));
	ListItrForEach(n1, n2, PrintForEach, NULL);
	putchar('\n');
	n1 = ListItrBegin(list);
	n2 = ListItrEnd(list);
	n3 = ListItrNext(n2);
	ListItrForEach(n1, n2, PrintForEach, NULL);
	putchar('\n');
	printf("%ld\n", ListItrCountIf(n1, n2, Predicate, (void*) a));
	n4 = ListItrFindFirst(n1, n2, Predicate, (void*) b);
	ListItrForEach(n4, ListItrNext(n4), PrintForEach, NULL);
	putchar('\n');
	
	return 0;
}

static int Predicate(void* _element, void* _context)
{
	if(*(int*)_context == *(int*)_element)
	{
		return 1;
	}
	return 0;
}

static int PrintForEach(void* _element, void* _context)
{
	if(_context == NULL)
	{
		printf("(%d)  ", *((int*)_element));
		return 1;
	}
}

