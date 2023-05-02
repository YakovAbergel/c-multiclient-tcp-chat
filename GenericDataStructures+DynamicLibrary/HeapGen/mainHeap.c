#include "heapGen.h" /*function signatures relating to heapGen*/
#include "../VectorGen/vectorGen.h" /*function signatures relating to vectorGen*/
#include <stdio.h> /*printf*/

typedef struct Person Person;

struct Person
{
	int m_id;
	char* m_name;
	int m_age;
};

static int Compar(const void *_left, const void *_right);
static int PrintVec(void* _element, size_t _index, void* _context);
static int PrintHeap(const void* _element, void* _context);
static int FindHeap(const void* _element, void* _context);
static int ComparPerson(const void *_left, const void *_right);
static int PrintHeapPerson(const void* _element, void* _context);
static int FindHeapPerson(const void* _element, void* _context);
static int PrintVecPerson(void* _element, size_t _index, void* _context);

void HeapBuildGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	
	heap = HeapBuild(vec, ComparPerson);
	if(heap == NULL)
	{
		printf("%s", "Check HeapBuildGenTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapBuildGenTest1 with valid input - FAIL\n");
	}
}

void HeapBuildGenTest2()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	
	vec = VectorCreate(2,5);
	heap = HeapBuild(vec, NULL);
	if(heap == NULL)
	{
		printf("%s", "Check HeapBuildGenTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapBuildGenTest2 with valid input - FAIL\n");
	}
}

void HeapBuildGenTest3()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	
	vec = VectorCreate(2,5);
	heap = HeapBuild(vec, ComparPerson);
	if(heap != NULL)
	{
		printf("%s", "Check HeapBuildGenTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapBuildGenTest3 with valid input - FAIL\n");
	}
}

void HeapBuildGenTest4()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	VectorAppend(vec, d);
	heap = HeapBuild(vec, ComparPerson);
	if(heap != NULL)
	{
		printf("%s", "Check HeapBuildGenTest4 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapBuildGenTest4 with valid input - FAIL\n");
	}
}

void HeapGenDestroyTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	
	vec = VectorCreate(2,5);
	vec = HeapDestroy(&heap);
	if(vec == NULL)
	{
		printf("%s", "Check HeapGenDestroyTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapGenDestroyTest1 with valid input - FAIL\n");
	}
}

void HeapGenDestroyTest2()
{
	Vector* vec = NULL;
	Vector* vec1 = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	VectorAppend(vec, d);
	heap = HeapBuild(vec, ComparPerson);
	vec1 = HeapDestroy(&heap);
	
	if(vec1 != NULL)
	{
		printf("%s", "Check HeapGenDestroyTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapGenDestroyTest2 with valid input - FAIL\n");
	}
}

void HeapInsertGenTest1()
{
	HeapResultCode res;
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person* a = &aa;

	vec = VectorCreate(2,5);
	res = HeapInsert(heap, a);
	if(res == HEAP_NOT_INITIALIZED)
	{
		printf("%s", "Check HeapInsertGenTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapInsertGenTest1 with valid input - FAIL\n");
	}
}

void HeapInsertGenTest2()
{
	HeapResultCode res;
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,0);

	heap = HeapBuild(vec, ComparPerson);
	res = HeapInsert(heap, NULL);
	if(res == HEAP_NOT_INITIALIZED)
	{
		printf("%s", "Check HeapInsertGenTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapInsertGenTest2 with valid input - FAIL\n");
	}
}

void HeapInsertGenTest3()
{
	HeapResultCode res;
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;


	vec = VectorCreate(2,0);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	heap = HeapBuild(vec, ComparPerson);
	res = HeapInsert(heap, c);
	if(res == HEAP_REALLOCATION_FAILED)
	{
		printf("%s", "Check HeapInsertGenTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapInsertGenTest3 with valid input - FAIL\n");
	}
}

void HeapInsertGenTest4()
{
	HeapResultCode res;
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	vec = VectorCreate(2,1);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	heap = HeapBuild(vec, ComparPerson);
	res = HeapInsert(heap, c);
	if(res == HEAP_SUCCESS)
	{
		printf("%s", "Check HeapInsertGenTest4 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapInsertGenTest4 with valid input - FAIL\n");
	}
}

void HeapPeekGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,5);
	
	if(HeapPeek(heap) == NULL)
	{
		printf("%s", "Check HeapPeekGenTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapPeekGenTest1 with valid input - FAIL\n");
	}
}

void HeapPeekGenTest2()
{
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,5);
	heap = HeapBuild(vec, ComparPerson);
	
	if(HeapPeek(heap) == NULL)
	{
		printf("%s", "Check HeapPeekGenTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapPeekGenTest2 with valid input - FAIL\n");
	}
}

void HeapPeekGenTest3()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, ComparPerson);
	
	if((*(int*)HeapPeek(heap)) == 8)
	{
		printf("%s", "Check HeapPeekGenTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapPeekGenTest3 with valid input - FAIL\n");
	}
}

void HeapExtractGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,5);
	
	if(HeapExtract(heap) == NULL)
	{
		printf("%s", "Check HeapExtractGenTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapExtractGenTest1 with valid input - FAIL\n");
	}
}

void HeapExtractGenTest2()
{
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,5);
	heap = HeapBuild(vec, ComparPerson);
	
	if(HeapExtract(heap) == NULL)
	{
		printf("%s", "Check HeapExtractGenTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapExtractGenTest2 with valid input - FAIL\n");
	}
}

void HeapExtractGenTest3()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, ComparPerson);
	
	if((*(int*)HeapExtract(heap)) == 8 && HeapSize(heap) == 2)
	{
		printf("%s", "Check HeapExtractGenTest3 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapExtractGenTest3 with valid input - FAIL\n");
	}
}

void HeapSizeGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;

	vec = VectorCreate(2,5);
	
	if(HeapSize(heap) == 0)
	{
		printf("%s", "Check HeapSizeGenTest1 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapSizeGenTest1 with valid input - FAIL\n");
	}
}

void HeapSizeGenTest2()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, ComparPerson);
	if(HeapSize(heap) == 3)
	{
		printf("%s", "Check HeapSizeGenTest2 with valid input - PASS\n");
	}
	else
	{
		printf("%s", "Check HeapSizeGenTest2 with valid input - FAIL\n");
	}
}

void HeapPrintGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, ComparPerson);
	
	HeapForEach(heap, PrintHeapPerson, NULL);
	putchar('\n');
		
	printf("if print 8, 1, 3 so PASS else FAIL\n");
}

void HeapFindGenTest1()
{
	Vector* vec = NULL;
	Heap* heap = NULL;
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {10,"c",30};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	
	vec = VectorCreate(2,5);
	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, ComparPerson);
	
	HeapForEach(heap, FindHeapPerson, c);
	putchar('\n');
	HeapForEach(heap, FindHeapPerson, d);
	putchar('\n');
		
	printf("if print find and -, so PASS else FAIL\n");
}

int main()
{
	HeapBuildGenTest1();
	HeapBuildGenTest2();
	HeapBuildGenTest3();
	HeapBuildGenTest4();
	HeapGenDestroyTest1();
	HeapGenDestroyTest2();
	HeapInsertGenTest1();
	HeapInsertGenTest2();
	HeapInsertGenTest3();
	HeapInsertGenTest4();
	HeapPeekGenTest1();
	HeapPeekGenTest2();
	HeapPeekGenTest3();
	HeapExtractGenTest1();
	HeapExtractGenTest2();
	HeapExtractGenTest3();
	HeapSizeGenTest1();
	HeapSizeGenTest2();
	HeapPrintGenTest1();
	HeapFindGenTest1();

	/*Vector* vec;
	Heap* heap;
	
	Person aa = {3,"a",20};
	Person bb = {1,"b",15};
	Person cc = {8,"c",30};
	Person dd = {5,"d",3};
	Person* a = &aa;
	Person* b = &bb;
	Person* c = &cc;
	Person* d = &dd;
	Person** e;
	
	vec = VectorCreate(2,5);

	VectorAppend(vec, a);
	VectorAppend(vec, b);
	VectorAppend(vec, c);
	VectorAppend(vec, d);
	heap = HeapBuild(vec, ComparPerson);
	VectorForEach(vec, PrintVecPerson, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeapPerson, NULL);
	putchar('\n');
	HeapInsert(heap, d);
	VectorForEach(vec, PrintVecPerson, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeapPerson, NULL);
	putchar('\n');
	HeapForEach(heap, FindHeapPerson, d);
	printf("%d\n",(*(int*)HeapPeek(heap)));
	HeapExtract(heap);
	VectorForEach(vec, PrintVecPerson, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeapPerson, NULL);
	putchar('\n');
	printf("%ld\n",(HeapSize(heap)));*/

	/*Vector* vec;
	Heap* heap;
	
	int aa = 7;
	int bb = 5;
	int cc = 10;
	int ee = 11;
	int* a = &aa;
	int* b = &bb;
	int* c = &cc;
	int* e = &ee;
	int** d;
	
	vec = VectorCreate(2,5);

	VectorAppend(vec, a);

	VectorAppend(vec, b);
	VectorAppend(vec, c);
	VectorAppend(vec, c);
	heap = HeapBuild(vec, Compar);
	VectorForEach(vec, PrintVec, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeap, NULL);
	putchar('\n');
	HeapInsert(heap, e);
	VectorForEach(vec, PrintVec, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeap, NULL);
	putchar('\n');
	HeapForEach(heap, FindHeap, e);
	printf("%d\n",(*(int*)HeapPeek(heap)));
	HeapExtract(heap);
	VectorForEach(vec, PrintVec, NULL);
	putchar('\n');
	HeapForEach(heap, PrintHeap, NULL);
	putchar('\n');
	printf("%ld\n",(HeapSize(heap)));*/

	return 0;
}

static int ComparPerson(const void *_left, const void *_right)
{
	if(((Person*)_left)->m_id > ((Person*)_right)->m_id)
	{
		return TRUE;
	}
	
	return FALSE;
}

static int PrintHeapPerson(const void* _element, void* _context)
{
	if(_context == NULL)
	{
		printf("(%d)  ", ((Person*)_element)->m_id);
		return 1;
	}
}

static int FindHeapPerson(const void* _element, void* _context)
{
	if(((Person*)_element)->m_id == ((Person*)_context)->m_id)
	{
		printf("\nfind\n");
		return 0;
	}
	return 1;
}

static int PrintVecPerson(void* _element, size_t _index, void* _context)
{
	if(_context == NULL)
	{
		printf("(%ld: %d)  ",_index, ((Person*)_element)->m_id);
		return 1;
	}
}

static int Compar(const void *_left, const void *_right)
{
	if((*(int*)_left) > (*(int*)_right))
	{
		return TRUE;
	}
	
	return FALSE;
}

static int PrintHeap(const void* _element, void* _context)
{
	if(_context == NULL)
	{
		printf("(%d)  ", *((int*)_element));
		return 1;
	}
}

static int FindHeap(const void* _element, void* _context)
{
	if(*((int*)_context) == *((int*)_element))
	{
		printf("\nfind\n");
		return 0;
	}
	return 1;
}

static int PrintVec(void* _element, size_t _index, void* _context)
{
	if(_context == NULL)
	{
		printf("(%ld: %d)  ",_index, *((int*)_element));
		return 1;
	}
}
