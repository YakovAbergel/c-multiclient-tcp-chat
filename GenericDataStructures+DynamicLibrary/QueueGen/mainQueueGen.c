#include "QueueGen.h"
#include <stdio.h> /*printf*/

typedef struct Person Person;

struct Person
{
	int m_id;
	char* m_name;
	int m_age;
};

static int PrintQueuePerson(const void* _element, void* _context);
static void DestroyItemInt(void* _element);
static int FindQueuePerson(const void* _element, void* _context);

void QueueCreateSizeZero()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(0);
	
	if(qPtr == NULL)
	{
		printf("QueueCreateSizeZero = PASS \n");
	}
	else
	{
		printf("QueueCreateSizeZero = FAIL \n");
	}
}

void QueueCreateSizeNoZero()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(1);
	
	if(qPtr != NULL)
	{
		printf("QueueCreateSizeNoZero = PASS \n");
	}
	else
	{
		printf("QueueCreateSizeNoZero = FAIL \n");
	}
}

void QueueDestroyTest1()
{
	Queue* qPtr = NULL;
	qPtr = QueueCreate(1);
	QueueDestroy(&qPtr, NULL);
	
	if(qPtr == NULL)
	{
		printf("QueueDestroyTest1 = PASS \n");
	}
	else
	{
		printf("QueueDestroyTest1 = FAIL \n");
	}
}

void QueueDestroyTest2()
{
	Queue* qPtr = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	
	qPtr = QueueCreate(4);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	QueueInsert(qPtr, d);
	QueueDestroy(&qPtr, DestroyItemInt);
	
	if(qPtr == NULL && aa == 4 && bb == 2 && cc == 9 && dd == 6)
	{
		printf("QueueDestroyTest2 = PASS \n");
	}
	else
	{
		printf("QueueDestroyTest2 = FAIL \n");
	}
}

void QueueInsertTest1()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int dd = 5;
	int* d = &dd;
	
	res = QueueInsert(qPtr, d);

	if(res == QUEUE_UNINITIALIZED_ERROR)
	{
		printf("QueueInsertTest1 = PASS \n");
	}
	else
	{
		printf("QueueInsertTest1 = FAIL \n");
	}
}

void QueueInsertTest2()
{
	QueueResult res;
	Queue* qPtr = NULL;

	qPtr = QueueCreate(3);
	res = QueueInsert(qPtr, NULL);

	if(res == QUEUE_DATA_UNINITIALIZED_ERROR)
	{
		printf("QueueInsertTest2 = PASS \n");
	}
	else
	{
		printf("QueueInsertTest2 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueInsertTest3()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	
	qPtr = QueueCreate(3);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	res = QueueInsert(qPtr, d);

	if(res == QUEUE_OVERFLOW_ERROR)
	{
		printf("QueueInsertTest3 = PASS \n");
	}
	else
	{
		printf("QueueInsertTest3 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueInsertTest4()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int dd = 5;
	int* d = &dd;
	
	qPtr = QueueCreate(4);
	res = QueueInsert(qPtr, d);

	if(res == QUEUE_SUCCESS)
	{
		printf("QueueInsertTest4 = PASS \n");
	}
	else
	{
		printf("QueueInsertTest4 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueInsertTest5()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;
	
	qPtr = QueueCreate(4);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	res = QueueInsert(qPtr, d);

	if(res == QUEUE_SUCCESS)
	{
		printf("QueueInsertTest5 = PASS \n");
	}
	else
	{
		printf("QueueInsertTest5 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueRemoveTest1()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int** d;
	
	res = QueueRemove(qPtr, (void**)d);

	if(res == QUEUE_UNINITIALIZED_ERROR)
	{
		printf("QueueRemoveTest1 = PASS \n");
	}
	else
	{
		printf("QueueRemoveTest1 = FAIL \n");
	}
}

void QueueRemoveTest2()
{
	QueueResult res;
	Queue* qPtr = NULL;

	qPtr = QueueCreate(3);
	res = QueueRemove(qPtr, NULL);

	if(res == QUEUE_DATA_UNINITIALIZED_ERROR)
	{
		printf("QueueRemoveTest2 = PASS \n");
	}
	else
	{
		printf("QueueRemoveTest2 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueRemoveTest3()
{
	QueueResult res;
	Queue* qPtr = NULL;
	int aa = 3;
	int* a = &aa;

	
	qPtr = QueueCreate(3);
	res = QueueRemove(qPtr, (void**)a);

	if(res == QUEUE_UNDERFLOW_ERROR)
	{
		printf("QueueRemoveTest3 = PASS \n");
	}
	else
	{
		printf("QueueRemoveTest3 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueRemoveTest4()
{
	QueueResult res1,res2,res3,res4;
	Queue* qPtr = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;

	qPtr = QueueCreate(4);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	QueueInsert(qPtr, d);

	res1 = QueueRemove(qPtr, (void**)a);
	res2 = QueueRemove(qPtr, (void**)b);
	res3 = QueueRemove(qPtr, (void**)c);
	res4 = QueueRemove(qPtr, (void**)d);

	if(res1 == QUEUE_SUCCESS && res2 == QUEUE_SUCCESS && res3 == QUEUE_SUCCESS && res4 == QUEUE_SUCCESS && *a == aa && *b == bb && *c == cc && *d == dd)
	{
		printf("QueueRemoveTest4 = PASS \n");
	}
	else
	{
		printf("QueueRemoveTest4 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueIsEmptyTest1()
{
	Queue* qPtr = NULL;

	if(QueueIsEmpty(qPtr) == 1)
	{
		printf("QueueIsEmptyTest1 = PASS \n");
	}
	else
	{
		printf("QueueIsEmptyTest1 = FAIL \n");
	}
}

void QueueIsEmptyTest2()
{
	Queue* qPtr = NULL;

	qPtr = QueueCreate(4);
	
	if(QueueIsEmpty(qPtr) == 1)
	{
		printf("QueueIsEmptyTest2 = PASS \n");
	}
	else
	{
		printf("QueueIsEmptyTest2 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueueIsEmptyTest3()
{
	Queue* qPtr = NULL;
	int aa = 3;
	int bb = 1;
	int cc = 8;
	int dd = 5;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* d = &dd;

	qPtr = QueueCreate(4);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	QueueInsert(qPtr, d);
	
	if(QueueIsEmpty(qPtr) == 0)
	{
		printf("QueueIsEmptyTest3 = PASS \n");
	}
	else
	{
		printf("QueueIsEmptyTest3 = FAIL \n");
	}
	QueueDestroy(&qPtr, NULL);
}

void QueuePrintGenTest1()
{
	Queue* qPtr = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	qPtr = QueueCreate(3);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);

	QueueForEach(qPtr, PrintQueuePerson, NULL);
	putchar('\n');
		
	printf("if print 3, 1, 8 so PASS else FAIL\n");
	QueueDestroy(&qPtr, NULL);
}

void QueueFindGenTest1()
{
	Queue* qPtr = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {10,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	
	qPtr = QueueCreate(3);
	QueueInsert(qPtr, a);
	QueueInsert(qPtr, b);
	QueueInsert(qPtr, c);
	
	QueueForEach(qPtr, FindQueuePerson, c);
	putchar('\n');
	QueueForEach(qPtr, FindQueuePerson, d);
	putchar('\n');
		
	printf("if print find and -, so PASS else FAIL\n");
	QueueDestroy(&qPtr, NULL);
}
int main()
{
	QueueCreateSizeZero();
	QueueCreateSizeNoZero();
	QueueDestroyTest1();
	QueueDestroyTest2();
	QueueInsertTest1();
	QueueInsertTest2();
	QueueInsertTest3();
	QueueInsertTest4();
	QueueInsertTest5();
	QueueRemoveTest1();
	QueueRemoveTest2();
	QueueRemoveTest3();
	QueueRemoveTest4();
	QueueIsEmptyTest1();
	QueueIsEmptyTest2();
	QueueIsEmptyTest3();
	QueuePrintGenTest1();
	QueueFindGenTest1();

	/*Queue* q = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	Person** e;
	
	q = QueueCreate(3);
	QueueInsert(q, a);
	QueueInsert(q, b);
	QueueInsert(q, c);
	QueueForEach(q, PrintQueuePerson, NULL);
	putchar('\n');
	QueueRemove(q, (void**)e);
	QueueForEach(q, PrintQueuePerson, NULL);
	putchar('\n');
	printf("%ld \n",QueueIsEmpty(q));
	QueueRemove(q, (void**)e);
	QueueRemove(q, (void**)e);
	printf("%ld \n",QueueIsEmpty(q));
*/
	return 0;
}

static int PrintQueuePerson(const void* _element, void* _context)
{
	if(_context == NULL)
	{
		printf("(%d)  ", ((Person*)_element)->m_id);
		return 1;
	}
}

static int FindQueuePerson(const void* _element, void* _context)
{
	if(((Person*)_element)->m_id == ((Person*)_context)->m_id)
	{
		printf("\nfind\n");
		return 0;
	}
	return 1;
}

static void DestroyItemInt(void* _element)
{
	*(int*)_element = *(int*)_element + 1;
}
