#include "listGen.h"
#include "listInternal.h" 
#include <stdio.h> /*printf*/

typedef struct Person Person;

struct Person
{
	int m_id;
	char* m_name;
	int m_age;
};

static void DestroyItemInt(void* _element);

void ListCreateTest1()
{
	List* list = NULL;
	list = ListCreate();
	if(list != NULL)
	{
		printf("ListCreateTest1 = PASS \n");
	}
	else
	{
		printf("ListCreateTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListDestroyTest1()
{
	List* list = NULL;
	list = ListCreate();
	ListDestroy(&list, NULL);
	
	if(list == NULL)
	{
		printf("ListDestroyTest1 = PASS \n");
	}
	else
	{
		printf("ListDestroyTest1 = FAIL \n");
	}
}

void ListDestroyTest2()
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
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushHead(list, b);
	ListPushHead(list, c);
	ListPushHead(list, d);
	ListDestroy(&list, DestroyItemInt);
	
	if(list == NULL && aa == 4 && bb == 2 && cc == 9 && dd == 6)
	{
		printf("ListDestroyTest2 = PASS \n");
	}
	else
	{
		printf("ListDestroyTest2 = FAIL \n");
	}
}
	
void ListPushHeadTest1()
{
	ListResult res;
	List* list = NULL;

	list = ListCreate();
	res = ListPushHead(list, NULL);

	if(res == LIST_NULL_ELEMENT_ERROR)
	{
		printf("ListPushHeadTest1 = PASS \n");
	}
	else
	{
		printf("ListPushHeadTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPushHeadTest2()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	res = ListPushHead(list, d);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPushHeadTest2 = PASS \n");
	}
	else
	{
		printf("ListPushHeadTest2 = FAIL \n");
	}
}

void ListPushHeadTest3()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	res = ListPushHead(list, d);

	if(res == LIST_SUCCESS)
	{
		printf("ListPushHeadTest3 = PASS \n");
	}
	else
	{
		printf("ListPushHeadTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPushTailTest1()
{
	ListResult res;
	List* list = NULL;

	list = ListCreate();
	res = ListPushTail(list, NULL);

	if(res == LIST_NULL_ELEMENT_ERROR)
	{
		printf("ListPushTailTest1 = PASS \n");
	}
	else
	{
		printf("ListPushTailTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPushTailTest2()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	res = ListPushTail(list, d);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPushTailTest2 = PASS \n");
	}
	else
	{
		printf("ListPushTailTest2 = FAIL \n");
	}
}

void ListPushTailTest3()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	res = ListPushTail(list, d);

	if(res == LIST_SUCCESS)
	{
		printf("ListPushTailTest3 = PASS \n");
	}
	else
	{
		printf("ListPushTailTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopHeadTest1()
{
	ListResult res;
	List* list = NULL;

	list = ListCreate();
	res = ListPopHead(list, NULL);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPopHeadTest1 = PASS \n");
	}
	else
	{
		printf("ListPopHeadTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopHeadTest2()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	res = ListPopHead(list,(void**)d);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPopHeadTest2 = PASS \n");
	}
	else
	{
		printf("ListPopHeadTest2 = FAIL \n");
	}
}

void ListPopHeadTest3()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	res = ListPopHead(list, (void**)d);

	if(res == LIST_UNDERFLOW_ERROR)
	{
		printf("ListPopHeadTest3 = PASS \n");
	}
	else
	{
		printf("ListPopHeadTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopHeadTest4()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	ListPushTail(list, d);
	res = ListPopHead(list, (void**)d);

	if(res == LIST_SUCCESS)
	{
		printf("ListPopHeadTest4 = PASS \n");
	}
	else
	{
		printf("ListPopHeadTest4 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopTailTest1()
{
	ListResult res;
	List* list = NULL;

	list = ListCreate();
	res = ListPopTail(list, NULL);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPopTailTest1 = PASS \n");
	}
	else
	{
		printf("ListPopTailTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopTailTest2()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	res = ListPopTail(list,(void**)d);

	if(res == LIST_UNINITIALIZED_ERROR)
	{
		printf("ListPopTailTest2 = PASS \n");
	}
	else
	{
		printf("ListPopTailTest2 = FAIL \n");
	}
}

void ListPopTailTest3()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	res = ListPopTail(list, (void**)d);

	if(res == LIST_UNDERFLOW_ERROR)
	{
		printf("ListPopTailTest3 = PASS \n");
	}
	else
	{
		printf("ListPopTailTest3 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListPopTailTest4()
{
	ListResult res;
	List* list = NULL;
	int dd = 5;
	int* d = &dd;
	
	list = ListCreate();
	ListPushTail(list, d);
	res = ListPopTail(list,(void**) d);

	if(res == LIST_SUCCESS)
	{
		printf("ListPopTailTest4 = PASS \n");
	}
	else
	{
		printf("ListPopTailTest4 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListSizeTest1()
{
	List* list = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	ListPushTail(list, d);

	if(ListSize(list) == 4)
	{
		printf("ListSizeTest1 = PASS \n");
	}
	else
	{
		printf("ListSizeTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}

void ListSizeTest2()
{
	List* list = NULL;


	if(ListSize(list) == 0)
	{
		printf("ListSizeTest1 = PASS \n");
	}
	else
	{
		printf("ListSizeTest1 = FAIL \n");
	}
}

void ListSizeTest3()
{
	List* list = NULL;

	list = ListCreate();

	if(ListSize(list) == 0)
	{
		printf("ListSizeTest1 = PASS \n");
	}
	else
	{
		printf("ListSizeTest1 = FAIL \n");
	}
	ListDestroy(&list, NULL);
}
int main()
{
	ListCreateTest1();
	ListDestroyTest1();
	ListDestroyTest2();
	ListPushHeadTest1();
	ListPushHeadTest2();
	ListPushHeadTest3();
	ListPushTailTest1();
	ListPushTailTest2();
	ListPushTailTest3();
	ListPopHeadTest1();
	ListPopHeadTest2();
	ListPopHeadTest3();
	ListPopHeadTest4();
	ListPopTailTest1();
	ListPopTailTest2();
	ListPopTailTest3();
	ListPopTailTest4();
	ListSizeTest1();
	ListSizeTest2();
	ListSizeTest3();
	
	
	
	/*List* list = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	Person* e;
	
	list = ListCreate();
	ListPushHead(list, a);
	ListPushTail(list, b);
	ListPushHead(list, c);
	printf("%ld\n",ListSize(list));
	ListPrint(list);
	ListPopHead(list, (void**)e);
	ListPrint(list);
	ListPopTail(list, (void**)e);
	ListPrint(list);*/
	return 0;
	
}

static void DestroyItemInt(void* _element)
{
	*(int*)_element = *(int*)_element + 1;
}


/*void ListPrint(List* _list)
{
    Node* temp = _list->m_head.m_next;
    while (temp != &_list->m_tail)
    {
        printf("m_data = %d\n", ((Person*)temp->m_data)->m_id);
        
        temp = temp->m_next;
    }
    putchar('\n');
}*/

