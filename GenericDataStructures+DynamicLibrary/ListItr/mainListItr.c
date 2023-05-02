#include "../ListGen/listGen.h"
#include "listItr.h" 
#include "../ListGen/listInternal.h"
#include <stdio.h>

void ListItrBeginTest1()
{
	List* list = NULL;
	
	if(ListItrBegin(list) == NULL)
	{
		printf("ListItrBeginTest1 = PASS \n");
	}
	else
	{
		printf("ListItrBeginTest1 = FAIL \n");
	}
}

void ListItrBeginTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	Node* n1;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrBegin(list);
	
	if(*(int*)n1->m_data == 5)
	{
		printf("ListItrBeginTest2 = PASS \n");
	}
	else
	{
		printf("ListItrBeginTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrBeginTest3()
{
	List* list = NULL;

	Node* n1;
	
	list = ListCreate();

	n1 = ListItrBegin(list);
	
	if(n1 == &(list->m_tail))
	{
		printf("ListItrBeginTest3 = PASS \n");
	}
	else
	{
		printf("ListItrBeginTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrEndTest1()
{
	List* list = NULL;
	
	if(ListItrEnd(list) == NULL)
	{
		printf("ListItrEndTest1 = PASS \n");
	}
	else
	{
		printf("ListItrEndTest1 = FAIL \n");
	}
}

void ListItrEndTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	Node* n1;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	
	if(*(int*)n1->m_prev->m_data == 1 && n1 == &(list->m_tail))
	{
		printf("ListItrEndTest2 = PASS \n");
	}
	else
	{
		printf("ListItrEndTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrEqualsTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(ListItrEquals((void*)n1, (void*)n2) == 1 && ListItrEquals((void*)n1, (void*)n3) == 0)
	{
		printf("ListItrEqualsTest1 = PASS \n");
	}
	else
	{
		printf("ListItrEqualsTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrEqualsTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if((ListItrEquals(NULL, (void*)n2) == 0) && (ListItrEquals((void*)n1, NULL) == 0))
	{
		printf("ListItrEqualsTest2 = PASS \n");
	}
	else
	{
		printf("ListItrEqualsTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrNextTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(ListItrNext(NULL) == NULL)
	{
		printf("ListItrNextTest1 = PASS \n");
	}
	else
	{
		printf("ListItrNextTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrNextTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(*(int*)((Node*)(ListItrNext((void*)n3)))->m_data == 8)
	{
		printf("ListItrNextTest2 = PASS \n");
	}
	else
	{
		printf("ListItrNextTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrPrevTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(ListItrPrev(NULL) == NULL)
	{
		printf("ListItrPrevTest1 = PASS \n");
	}
	else
	{
		printf("ListItrPrevTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrPrevTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(*(int*)((Node*)(ListItrPrev((void*)n3)))->m_data == 5 && *(int*)((Node*)(ListItrPrev((void*)n2)))->m_data == 1)
	{
		printf("ListItrPrevTest2 = PASS \n");
	}
	else
	{
		printf("ListItrPrevTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrPrevTest3()
{
	List* list = NULL;
	int aa = 3;
	int* a = &aa;
	Node* n1;

	list = ListCreate();
	ListPushHead(list, a);
	n1 = ListItrBegin(list);

	if((Node*)(ListItrPrev((void*)n1)) == n1)
	{
		printf("ListItrPrevTest3 = PASS \n");
	}
	else
	{
		printf("ListItrPrevTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrGetTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(ListItrGet(NULL) == NULL)
	{
		printf("ListItrGetTest1 = PASS \n");
	}
	else
	{
		printf("ListItrGetTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrGetTest2()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);

	if(ListItrGet(n2) == n2->m_data)
	{
		printf("ListItrGetTest2 = PASS \n");
	}
	else
	{
		printf("ListItrGetTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrSetTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n2 = ListItrEnd(list);
	n3 = ListItrBegin(list);
	n1 = ListItrBegin(list);
	ListItrSet((void*)n1, (void*)b);

	if((ListItrGet(n1) == b) && (ListItrSet(NULL, (void*)b)) == NULL && ListItrSet((void*)n1, NULL) == NULL) 
	{
		printf("ListItrSetTest1 = PASS \n");
	}
	else
	{
		printf("ListItrSetTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrSetTest2()
{
	List* list = NULL;
	int bb = 1;
	int* b = &bb;
	Node* n1;

	
	list = ListCreate();
	n1 = ListItrBegin(list);

	if(ListItrSet((void*)n1, (void*)b) == NULL) 
	{
		printf("ListItrSetTest2 = PASS \n");
	}
	else
	{
		printf("ListItrSetTest2 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrInsertBeforeTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushHead(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n2 = ListItrEnd(list);
	n1 = ListItrBegin(list);
	ListItrInsertBefore((void*)n1, (void*)c);
	ListItrInsertBefore((void*)n2, (void*)b);
	
	if((ListItrGet(ListItrPrev(n1)) == c) && (ListItrGet(ListItrPrev(n2)) == b)) 
	{
		printf("ListItrInsertBeforeTest1 = PASS \n");
	}
	else
	{
		printf("ListItrInsertBeforeTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListItrRemoveTest1()
{
	List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	Node* n3;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushHead(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrBegin(list);
	ListItrRemove(n1);
	
	if((ListItrGet(ListItrBegin(list)) == c))
	{
		printf("ListItrRemoveTest1 = PASS \n");
	}
	else
	{
		printf("ListItrRemoveTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

int main()
{
	ListItrBeginTest1();
	ListItrBeginTest2();
	ListItrBeginTest3();
	ListItrEndTest1();
	ListItrEndTest2();
	ListItrEqualsTest1();
	ListItrEqualsTest2();
	ListItrNextTest1();
	ListItrNextTest2();
	ListItrPrevTest1();
	ListItrPrevTest2();
	ListItrPrevTest3();
	ListItrGetTest1();
	ListItrGetTest2();
	ListItrSetTest1();
	ListItrSetTest2();
	ListItrRemoveTest1();
	ListItrInsertBeforeTest1();
	
	/*List* list = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	int* e;
	Node* n1;
	Node* n2;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	n1 = ListItrBegin(list);
	printf("%d\n",*(int*)n1->m_data);
	n1 = ListItrEnd(list);
	n2 = ListItrEnd(list);
	printf("%d\n",*(int*)n1->m_prev->m_data);
	printf("%d\n",*(int*)n2->m_prev->m_data);
	printf("%d\n",ListItrEquals((void*)n1, (void*)n2));
	n1 = ListItrBegin(list);
	n2 = ListItrEnd(list);
	printf("%d\n",*(int*)((Node*)(ListItrNext((void*)n1)))->m_data);
	printf("%d\n",*(int*)((Node*)(ListItrPrev((void*)n2)))->m_data);
	printf("%d\n",*(int*)ListItrGet(n1));
	ListItrSet((void*)n1, (void*)a);
	printf("%d\n",*(int*)ListItrGet(n1));
	/*n1 = ListItrInsertBefore((void*)n1, (void*)n2);
	printf("%d\n",*(int*)((Node*)(ListItrNext((void*)n1)))->m_data);
	n1 = ListItrBegin(list);
	printf("%d\n",*(int*)ListItrGet(n1));
	ListItrRemove(n1);
	n1 = ListItrBegin(list);
	printf("%d\n",*(int*)ListItrGet(n1));*/
	
	
	return 0;
}
