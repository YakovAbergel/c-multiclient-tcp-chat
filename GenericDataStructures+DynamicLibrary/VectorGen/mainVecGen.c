#include "vectorGen.h" /*function signatures relating to vectorGen*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*free*/

typedef struct Person Person;

struct Person
{
	int m_id;
	char* m_name;
	int m_age;
};

static int ForEach(void* _element, size_t _index, void* _context);
static int DestroyElement(void* _element);

void VecGenCreateTest1()
{
	Vector *pVec = NULL;
	pVec = VectorCreate(0, 0);
	if(pVec == NULL)
	{
		printf("%s", "Check VecGenCreateTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenCreateTest1 with valid input - FAIL\n");
	}
}

void VecGenCreateTest2()
{
	Vector *pVec = NULL;
	pVec = VectorCreate(0, 2);
	if(pVec != NULL)
	{
		printf("%s", "Check VecGenCreateTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenCreateTest2 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenCreateTest3()
{
	Vector *pVec = NULL;
	pVec = VectorCreate(2, 0);
	if(pVec != NULL)
	{
		printf("%s", "Check VecGenCreateTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenCreateTest3 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenCreateTest4()
{
	Vector *pVec = NULL;
	pVec = VectorCreate(2, 3);
	if(pVec != NULL)
	{
		printf("%s", "Check VecGenCreateTest4 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenCreateTest4 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenDestroyTest1()
{
	Vector *pVec = NULL;
	int a = 1, b = 2, c = 3, d = 4;
	pVec = VectorCreate(2, 1);
	VectorAppend(pVec, &a);
	VectorAppend(pVec, &b);
	VectorAppend(pVec, &c);
	VectorAppend(pVec, &d);
	VectorDestroy(&pVec, DestroyElement);
	if(pVec == NULL && a == 2 && b == 3 && c == 4)
	{
		printf("%s", "Check VecGenDestroyTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenDestroyTest1 with valid input - FAIL\n");
	}
}

void VecGenAppendTest1()
{
	Vector *pVec = NULL;
	VectorResult res1, res2;
	int aa = 10;
	int* a = &aa;
    Person p1 = {1,"ziv",25};
    Person* p = &p1;
	res1 = VectorAppend(pVec, a);
	res2 = VectorAppend(pVec, p);
	
	if(res1 == VECTOR_UNITIALIZED_ERROR && res2 == VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenAppendTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenAppendTest1 with valid input - FAIL\n");
	}
}

void VecGenAppendTest2()
{
	Vector *pVec = NULL;
	VectorResult result1, result2;
	
	pVec = VectorCreate(2, 0);
	result1 = VectorAppend(pVec, NULL);
	result2 = VectorAppend(pVec, NULL);
	
	if(result1 == VECTOR_UNITIALIZED_ERROR && result2 == VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenAppendTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenAppendTest2 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

/*result2 is not equal to VECTOR_OVERFLOW_ERROR*/
void VecGenAppendTest3()
{
	Vector *pVec = NULL;
	VectorResult result1, result2;
	Person aa = {4,"ron",22};
	Person* a = &aa;
    Person p1 = {1,"ziv",25};
    Person* p = &p1;
    
   	pVec = VectorCreate(1, 0);
	result1 = VectorAppend(pVec, a);
	result2 = VectorAppend(pVec, p);
	
	if(result1 == VECTOR_SUCCESS && result2 == VECTOR_OVERFLOW_ERROR)
	{
		printf("%s", "Check VecGenAppendTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenAppendTest3 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenAppendTest4()
{
	Vector *pVec = NULL;
	VectorResult result1, result2, result3;
	Person aa = {4,"ron",40};
	Person bb = {2,"yosi",28};
	Person p1 = {1,"ziv",25};
	Person* a = &aa;
	Person* b = &bb;
    Person* p = &p1;
    
   	pVec = VectorCreate(1, 1);
	result1 = VectorAppend(pVec, a);
	result2 = VectorAppend(pVec, a);
	result3 = VectorAppend(pVec, a);
	
	if(result1 == VECTOR_SUCCESS && result2 == VECTOR_SUCCESS && result3 == VECTOR_SUCCESS)
	{
		printf("%s", "Check VecGenAppendTest4 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check VecGenAppendTest4 with valid input - FAIL\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenRemoveTest1()
{
	Vector *pVec = NULL;
	VectorResult result1;
	int** d;
	result1 = VectorRemove(pVec, (void**)d);

	if(result1 != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenRemoveTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenRemoveTest1 with valid input - PASS\n");
	}
}

void VecGenRemoveTest2()
{
	Vector *pVec = NULL;
	VectorResult res1, res2;
	int aa = 10;
	int* a = &aa;

	pVec = VectorCreate(2, 0);
	res1 = VectorAppend(pVec, a);
	res2 = VectorRemove(pVec, NULL);
	
	if(res2 != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenRemoveTest2 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenRemoveTest2 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenRemoveTest3()
{
	Vector *pVec = NULL;
	VectorResult res;
	int** d;
	
	pVec = VectorCreate(2, 0);
	res = VectorRemove(pVec, (void**)d);
	
	if(res != VECTOR_UNDERFLOW_ERROR)
	{
		printf("%s", "Check VecGenRemoveTest3 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenRemoveTest3 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

/*I did a destroy in the end I got a segfault */
void VecGenRemoveTest4()
{
	Vector *pVec = NULL;
	VectorResult res;
	int aa = 10;
	int* a = &aa;
	int** d;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorRemove(pVec, (void**)d);
	
	if(res != VECTOR_SUCCESS)
	{
		printf("%s", "Check VecGenRemoveTest4 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenRemoveTest4 with valid input - PASS\n");
	}
}

void VecGenGetTest1()
{
	Vector *pVec = NULL;
	int** d;
	VectorResult res;
	
	res = VectorGet(pVec, 1, (void**)d);
	
	if(res != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenGetTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenGetTest1 with valid input - PASS\n");
	}

}

void VecGenGetTest2()
{
	Vector *pVec = NULL;
	VectorResult res;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorGet(pVec, 1, NULL);
	
	if(res != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenGetTest2 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenGetTest2 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenGetTest3()
{
	Vector *pVec = NULL;
	VectorResult res;
	int** d;
	
	pVec = VectorCreate(2, 0);
	res = VectorGet(pVec, 0, (void**)d);
	
	if(res != VECTOR_UNDERFLOW_ERROR)
	{
		printf("%s", "Check VecGenGetTest3 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenGetTest3 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenGetTest4()
{
	Vector *pVec = NULL;
	VectorResult res;
	int** d;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorGet(pVec, 1, (void**)d);
	
	if(res != VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("%s", "Check VecGenGetTest4 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenGetTest4 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

/*I did a destroy in the end I got a segfault */
void VecGenGetTest5()
{
	Vector *pVec = NULL;
	VectorResult res;
	int** d;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorGet(pVec, 0, (void**)d);
	
	if(res != VECTOR_SUCCESS || **d != 10)
	{
		printf("%s", "Check VecGenGetTest5 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenGetTest5 with valid input - PASS\n");
	}
}

void VecGenSetTest1()
{
	Vector *pVec = NULL;
	int a = 4;
	int* d = &a;
	VectorResult res;
	
	res = VectorSet(pVec, 1, (void*)d);
	
	if(res != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenSetTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSetTest1 with valid input - PASS\n");
	}
}

void VecGenSetTest2()
{
	Vector *pVec = NULL;
	VectorResult res;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorGet(pVec, 0, NULL);
	
	if(res != VECTOR_UNITIALIZED_ERROR)
	{
		printf("%s", "Check VecGenSetTest2 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSetTest2 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenSetTest3()
{
	Vector *pVec = NULL;
	VectorResult res;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	res = VectorSet(pVec, 0, (void*)a);
	
	if(res != VECTOR_UNDERFLOW_ERROR)
	{
		printf("%s", "Check VecGenSetTest3 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSetTest3 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenSetTest4()
{
	Vector *pVec = NULL;
	VectorResult res;
	int dd = 5;
	int* d;
	int aa = 10;
	int* a = &aa;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, a);
	res = VectorSet(pVec, 1, (void*)d);
	
	if(res != VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("%s", "Check VecGenSetTest4 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSetTest4 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenSetTest5()
{
	Vector *pVec = NULL;
	VectorResult res;
	int dd = 20;
	int* d = &dd;
	int aa = 30;
	int* a = &aa;
	int** e;
	
	pVec = VectorCreate(2, 0);
	VectorAppend(pVec, d);
	VectorAppend(pVec, a);
	res = VectorSet(pVec, 0, a);
	VectorGet(pVec, 0, (void**)e);
	
	if(res != VECTOR_SUCCESS || **e != 30)
	{
		printf("%s", "Check VecGenSetTest5 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSetTest5 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenSizeTest1()
{
	Vector *pVec = NULL;
	size_t res;
	res = VectorSize(pVec);
	
	if(res != 0)
	{
		printf("%s", "Check VecGenSizeTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSizeTest1 with valid input - PASS\n");
	}
}

void VecGenSizeTest2()
{
	Vector *vec = NULL;
	size_t res;
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	
	res = VectorSize(vec);
	
	if(res != 3)
	{
		printf("%s", "Check VecGenSizeTest2 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenSizeTest2 with valid input - PASS\n");
	}
	VectorDestroy(&vec, NULL);
}

void VecGenCapacityTest1()
{
	Vector *pVec = NULL;
	size_t res;
	res = VectorCapacity(pVec);
	
	if(res != 0)
	{
		printf("%s", "Check VecGenCapacityTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenCapacityTest1 with valid input - PASS\n");
	}
}

void VecGenCapacityTest2()
{
	Vector *pVec = NULL;
	size_t res;
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	
	pVec = VectorCreate(2,5);
	VectorAppend(pVec, a);
	VectorAppend(pVec, b);
	VectorAppend(pVec, c);
	
	res = VectorCapacity(pVec);
	
	if(res != 7)
	{
		printf("%s", "Check VecGenCapacityTest2 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenCapacityTest2 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}

void VecGenForEachPrintTest1()
{
	Vector *pVec = NULL;
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	
	pVec = VectorCreate(2,5);
	VectorAppend(pVec, a);
	VectorAppend(pVec, b);
	VectorAppend(pVec, c);
	
	printf("print: 7 5 10 = PASS, else FAIL\n");
	VectorForEach(pVec, ForEach, NULL);
	putchar('\n');
	VectorDestroy(&pVec, NULL);
}

void VecGenForEachFindTest1()
{
	Vector *pVec = NULL;
	size_t res;
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int d = 5;
	int* dd = &d;
	
	pVec = VectorCreate(2,5);
	VectorAppend(pVec, a);
	VectorAppend(pVec, b);
	VectorAppend(pVec, c);
	res = VectorForEach(pVec, ForEach, (void*)dd);
	
	if(res != 1)
	{
		printf("%s", "Check VecGenForEachFindTest1 with valid input - FAIL\n");
	}
	else
	{
		printf("%s", "Check VecGenForEachFindTest1 with valid input - PASS\n");
	}
	VectorDestroy(&pVec, NULL);
}


int main()
{


	VecGenCreateTest1();
	VecGenCreateTest2();
	VecGenCreateTest3();
	VecGenCreateTest4();
	VecGenDestroyTest1();
	VecGenAppendTest1();
	VecGenAppendTest2();
	VecGenAppendTest3();
	VecGenAppendTest4();
	VecGenRemoveTest1();
	VecGenRemoveTest2();
	VecGenRemoveTest3();
	VecGenRemoveTest4();
	VecGenGetTest1();
	VecGenGetTest2();
	VecGenGetTest3();
	VecGenGetTest4();
	VecGenGetTest5();
	VecGenSetTest1();
	VecGenSetTest2();
	VecGenSetTest3();
	VecGenSetTest4();
	VecGenSetTest5();
	VecGenSizeTest1();
	VecGenSizeTest2();
	VecGenCapacityTest1();
	VecGenCapacityTest2();
	VecGenForEachPrintTest1();
	VecGenForEachFindTest1();
	/*Vector* vec;
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int** d;
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	VectorAppend(vec, c);
	VectorPrint(vec);
	printf("%ld\n",VectorSize(vec));
	printf("%ld\n",VectorCapacity(vec));
	VectorRemove(vec, (void**)d);
	VectorPrint(vec);
	printf("%d\n",**d);
	VectorGet(vec, 1, (void**) d);
	printf("%d\n",**d);
	VectorSet(vec, 1, vec->m_items[0]);
	VectorPrint(vec);
	VectorForEach(vec, ForEach, NULL);
	putchar('\n');
	printf("index = %ld, num = %d",VectorForEach(vec, ForEach, a), VectorGet(vec, VectorForEach(vec, ForEach, c), (void**) d));*/
	return 0;
}

static int ForEach(void* _element, size_t _index, void* _context)
{
	/*print elements*/
	if(_context == NULL)
	{
		printf("(%ld: %d)  ",_index, *((int*)_element));
		return 1;
	}
	
	/*find element by context*/
	if(*((int*)_context) == *((int*)_element))
	{
		return 0;
	}
	return 1;
}

static int DestroyElement(void* _element)
{
	*(int*)_element = *(int*)_element + 1;
}


