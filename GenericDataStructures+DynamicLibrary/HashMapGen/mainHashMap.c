#include <stdio.h>
#include "../ListFunc/listFunc.h"
#include "../ListItr/listItr.h"
#include "../ListGen/listGen.h"
#include "hashMap.h"

#define TRUE 1
#define FALSE 0

typedef struct Student Student;
typedef struct Grade Grade;

struct Student
{
    int m_ID;
    char m_name[6];
    int m_age;
};

struct Grade
{
    int m_english;
    int m_bible;
    int m_math;
};

void ChangeKey(void *_key)
{
    ((Student *)_key)->m_age = 42;
}

void ChangeVal(void *_value)
{
    ((Grade *)_value)->m_math = 42;
}

int PrintBucket(const void *_key, void *_value, void *_context)
{
    printf("ID: %d, name: %s, english grade: %d\n", ((Student *)_key)->m_ID, ((Student *)_key)->m_name, ((Grade *)_value)->m_english);

    return 1;
}

int FindStudent(const void *_key, void *_value, void *_context)
{
    if (((Student *)_key)->m_ID == ((Student *)_context)->m_ID)
    {
        PrintBucket(_key, _value, NULL);
        return 0;
    }
    return 1;
}

static size_t HashFunc(void *_key)
{
    return (size_t)(((Student *)_key)->m_ID);
}

static int IsEqual(void *_firstKey, void *_secondKey)
{
    if (((Student *)_firstKey)->m_ID == ((Student *)_secondKey)->m_ID)
    {
        return TRUE;
    }
    return FALSE;
}

static void HashCreateTest1()
{
    HashMap *map = NULL;
    map = HashMap_Create(10, HashFunc, IsEqual);
    if (map != NULL)
    {
        printf("HashCreateTest1 with valid parameters - pass\n");
    }
    else
    {
        printf("HashCreateTest1 with valid parameters - FAILED\n");
    }
}

static void HashCreateTest2()
{
    HashMap *map = NULL;
    map = HashMap_Create(5, HashFunc, IsEqual);
    if (map == NULL)
    {
        printf("HashCreateTest2 with not valid size - pass\n");
    }
    else
    {
        printf("HashCreateTest2 with not valid size  - FAILED\n");
    }
}

static void HashCreateTest3()
{
    HashMap *map = NULL;
    map = HashMap_Create(10, NULL, IsEqual);
    if (map == NULL)
    {
        printf("HashCreateTest3 with NULL HashFunction - pass\n");
    }
    else
    {
        printf("HashCreateTest3 with NULL HashFunction - FAILED\n");
    }
}

static void HashCreateTest4()
{
    HashMap *map = NULL;
    map = HashMap_Create(10, HashFunc, NULL);
    if (map == NULL)
    {
        printf("HashCreateTest4 with NULL EqualityFunction - pass\n");
    }
    else
    {
        printf("HashCreateTest4 with NULL EqualityFunction  - FAILED\n");
    }
}

static void HashMap_DestroyTest1()
{
    HashMap *map = NULL;
    Student student1 = {5, "Moty", 20};
    Grade grade1 = {80, 90, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Destroy(&map, NULL, NULL);

    if (map == NULL)
    {
        printf("HashMap_DestroyTest1 with valid parameters without key destroy and value destroy - pass\n");
    }
    else
    {
        printf("HashMap_DestroyTest1 with valid parameters without key destroy and value destroy - FAILED\n");
    }
}

static void HashMap_DestroyTest2()
{
    HashMap *map = NULL;
    Student student1 = {5, "Moty", 20};
    Grade grade1 = {80, 90, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Destroy(&map, ChangeKey, ChangeVal);

    if (map == NULL && student1.m_age == 42 && grade1.m_math == 42)
    {
        printf("HashMap_DestroyTest2 with valid parameters - pass\n");
    }
    else
    {
        printf("HashMap_DestroyTest2 with valid parameters - FAILED\n");
    }
}

static void HashMap_DestroyTest3()
{
    HashMap *map = NULL;
    Student student1 = {5, "Moty", 20};
    Grade grade1 = {80, 90, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Destroy(NULL, NULL, NULL);

    if (map != NULL)
    {
        HashMap_Destroy(&map, NULL, NULL);
        printf("HashMap_DestroyTest3 with NULL list - pass\n");
    }
    else
    {
        printf("HashMap_DestroyTest3 with NULL list - FAILED\n");
    }
}

static void HashMap_DestroyTest4()
{
    HashMap *map = NULL;
    Student student1 = {5, "Moty", 20};
    Grade grade1 = {80, 90, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Destroy(&map, NULL, NULL);
    printf("HashMap_DestroyTest4 duble free test:\n");
    HashMap_Destroy(&map, NULL, NULL);
    printf("double free test pass\n");
}
static void HashMap_InsertTest1()
{
    HashMap *map = NULL;
    Map_Result insertResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    insertResult = HashMap_Insert(map, &student1, &grade1);
    HashMap_Find(map, &student1, (void **)&grades);
    if (insertResult == MAP_SUCCESS && grades->m_bible == 90)
    {
        printf("HashMap_InsertTest1 with valid parameters - pass\n");
    }
    else
    {
        printf("HashMap_InsertTest1 with valid parameters - FAILED\n");
    }
}

static void HashMap_InsertTest2()
{
    HashMap *map = NULL;
    Map_Result insertResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    insertResult = HashMap_Insert(NULL, &student1, &grade1);
    findResult = HashMap_Find(map, &student1, (void **)&grades);
    if (insertResult == MAP_UNINITIALIZED_ERROR && findResult == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("HashMap_InsertTest2 with NULL map  - pass\n");
    }
    else
    {
        printf("HashMap_InsertTest2 with NULL map   - FAILED\n");
    }
}

static void HashMap_InsertTest3()
{
    HashMap *map = NULL;
    Map_Result insertResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    insertResult = HashMap_Insert(map, NULL, &grade1);
    findResult = HashMap_Find(map, &student1, (void **)&grades);
    if (insertResult == MAP_KEY_NULL_ERROR && findResult == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("HashMap_InsertTest3 with NULL key  - pass\n");
    }
    else
    {
        printf("HashMap_InsertTest3 with NULL key  - FAILED\n");
    }
}

static void HashMap_InsertTest4()
{
    HashMap *map = NULL;
    Map_Result insertResult, findResult;
    Student student1 = {5, "Moty"};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    insertResult = HashMap_Insert(map, &student1, NULL);
    findResult = HashMap_Find(map, &student1, (void **)&grades);
    if (insertResult == MAP_SUCCESS && findResult == MAP_SUCCESS && grades == NULL)
    {
        printf("HashMap_InsertTest4 with NULL value  - pass\n");
    }
    else
    {
        printf("HashMap_InsertTest4 with NULL value  - FAILED\n");
    }
}

static void HashMap_InsertTest5()
{
    HashMap *map = NULL;
    Map_Result insertResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {16, "Libat"};
    Grade grade2 = {20, 30, 40};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    insertResult = HashMap_Insert(map, &student2, &grade2);
    HashMap_Find(map, &student2, (void **)&grades);
    if (insertResult == MAP_SUCCESS && grades->m_bible == 30)
    {
        printf("HashMap_InsertTest5 with valid parameters and insert second element to list- pass\n");
    }
    else
    {
        printf("HashMap_InsertTest5 with valid parameters and insert second element to list - FAILED\n");
    }
}

static void HashMap_InsertTest6()
{
    HashMap *map = NULL;
    Map_Result insertResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {10, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    insertResult = HashMap_Insert(map, &student3, &grade3);
    HashMap_Find(map, &student3, (void **)&grades);
    if (insertResult == MAP_KEY_DUPLICATE_ERROR && grades->m_bible == 30)
    {
        printf("HashMap_InsertTest6 with dupkicate insertsion error - pass\n");
    }
    else
    {
        printf("HashMap_InsertTest6 with dupkicate insertsion error - FAILED\n");
    }
}

static void HashMap_RemoveTest1()
{
    HashMap *map = NULL;
    Map_Result removeResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, &student2, (void **)&student, (void **)&grades);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (removeResult == MAP_SUCCESS && grades->m_bible == 30 && student->m_ID == 10 && findResult == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("HashMap_RemoveTest1 with valid paramters - pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest1 with valid paramters - FAILED\n");
    }
}

static void HashMap_RemoveTest2()
{
    HashMap *map = NULL;
    Map_Result removeResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(NULL, &student2, (void **)&student, (void **)&grades);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (removeResult == MAP_UNINITIALIZED_ERROR && findResult == MAP_SUCCESS)
    {
        printf("HashMap_RemoveTest2 with NULL map- pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest2 with NULL map-- FAILED\n");
    }
}

static void HashMap_RemoveTest3()
{
    HashMap *map = NULL;
    Map_Result removeResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, NULL, (void **)&student, (void **)&grades);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (removeResult == MAP_KEY_NULL_ERROR && findResult == MAP_SUCCESS)
    {
        printf("HashMap_RemoveTest3 with NULL searchkay- pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest3 with NULL searchkay-- FAILED\n");
    }
}

static void HashMap_RemoveTest4()
{
    HashMap *map = NULL;
    Map_Result removeResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, &student2, NULL, (void **)&grades);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (removeResult == MAP_UNINITIALIZED_ERROR && findResult == MAP_SUCCESS)
    {
        printf("HashMap_RemoveTest4 with NULL Pkey- pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest4 with NULL Pkey- FAILED\n");
    }
}

static void HashMap_RemoveTest5()
{
    HashMap *map = NULL;
    Map_Result removeResult, findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, &student2, (void **)&student, NULL);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (removeResult == MAP_UNINITIALIZED_ERROR && findResult == MAP_SUCCESS)
    {
        printf("HashMap_RemoveTest6 with NULL Pvaule- pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest6 with NULL Pvalue- FAILED\n");
    }
}

static void HashMap_RemoveTest6()
{
    HashMap *map = NULL;
    Map_Result removeResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, &student2, (void **)&student, (void **)&grades);
    if (removeResult == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("HashMap_RemoveTest6 with valid paramters when searchkey not exsist in map- pass\n");
    }
    else
    {
        printf("HashMap_RemoveTest6 with valid paramters when searchkey not exsist in map- FAILED\n");
    }
}

static void HashMap_FindTest1()
{
    HashMap *map = NULL;
    Map_Result findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student3, &grade3);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (findResult == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("HashMap_FindTest2 with valid paramters when searchkey not exsist in map- pass\n");
    }
    else
    {
        printf("HashMap_FindTest2 with valid paramters when searchkey not exsist in map- FAILED\n");
    }
}

static void HashMap_FindTest2()
{
    HashMap *map = NULL;
    Map_Result findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    findResult = HashMap_Find(map, &student2, (void **)&grades);
    if (findResult == MAP_SUCCESS && grades->m_bible == 30)
    {
        printf("HashMap_FindTest2 with valid paramters - pass\n");
    }
    else
    {
        printf("HashMap_FindTest2 with valid paramters- FAILED\n");
    }
}
static void HashMap_FindTest3()
{
    HashMap *map = NULL;
    Map_Result findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    findResult = HashMap_Find(NULL, &student2, (void **)&grades);
    if (findResult == MAP_UNINITIALIZED_ERROR)
    {
        printf("HashMap_FindTest3 with NULL map - pass\n");
    }
    else
    {
        printf("HashMap_FindTest3 with NULL map - FAILED\n");
    }
}

static void HashMap_FindTest4()
{
    HashMap *map = NULL;
    Map_Result findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    findResult = HashMap_Find(map, &student2, NULL);
    if (findResult == MAP_UNINITIALIZED_ERROR)
    {
        printf("HashMap_FindTest4 with NULL Pvalue - pass\n");
    }
    else
    {
        printf("HashMap_FindTest4 with NULL Pvalue - FAILED\n");
    }
}

static void HashMap_FindTest5()
{
    HashMap *map = NULL;
    Map_Result findResult;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    findResult = HashMap_Find(map, NULL, (void **)&grades);
    if (findResult == MAP_KEY_NULL_ERROR)
    {
        printf("HashMap_FindTest5 with NULL key - pass\n");
    }
    else
    {
        printf("HashMap_FindTest5 with NULL key - FAILED\n");
    }
}

static void HashMap_SizeTest1()
{
    HashMap *map = NULL;
    size_t mapSize = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    mapSize = HashMap_Size(map);
    if (mapSize == 3)
    {
        printf("HashMap_SizeTest1 with valid paramters - pass\n");
    }
    else
    {
        printf("HashMap_SizeTest1 with valid paramters- FAILED\n");
    }
}

static void HashMap_SizeTest2()
{
    HashMap *map = NULL;
    size_t mapSize = 0;
    map = HashMap_Create(10, HashFunc, IsEqual);
    mapSize = HashMap_Size(map);
    if (mapSize == 0)
    {
        printf("HashMap_SizeTest2 with empty map - pass\n");
    }
    else
    {
        printf("HashMap_SizeTest2 with empty map - FAILED\n");
    }
}

static void HashMap_SizeTest3()
{
    HashMap *map = NULL;
    size_t mapSize = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    mapSize = HashMap_Size(NULL);
    if (mapSize == 0)
    {
        printf("HashMap_SizeTest3 with NULL map - pass\n");
    }
    else
    {
        printf("HashMap_SizeTest3 with NULL map - FAILED\n");
    }
}

static void HashMap_SizeTest4()
{
    HashMap *map = NULL;
    Map_Result removeResult;
    size_t mapSize = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Grade *grades;
    Student *student;
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    removeResult = HashMap_Remove(map, &student2, (void **)&student, (void **)&grades);
    mapSize = HashMap_Size(map);
    if (mapSize == 2 && removeResult == MAP_SUCCESS)
    {
        printf("HashMap_SizeTest4 with valid paramters after remove element - pass\n");
    }
    else
    {
        printf("HashMap_SizeTest4 with valid paramters after remove element - FAILED\n");
    }
}

static void HashMap_ForEachTest1()
{
    HashMap *map = NULL;
    size_t forEachResult = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    forEachResult = HashMap_ForEach(map, PrintBucket, NULL);
    if (forEachResult == 3)
    {
        printf("HashMap_ForEachTest1 with valid paramters and NULL context- pass\n");
    }
    else
    {
        printf("HashMap_ForEachTest1 with valid paramters and NULL context - FAILED\n");
    }
}

static void HashMap_ForEachTest2()
{
    HashMap *map = NULL;
    size_t forEachResult = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {22, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {10, "Carmi"};
    Grade grade3 = {100, 100, 100};
    Student student4 = {47, "Ilan"};
    Grade grade4 = {23, 54, 12};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    HashMap_Insert(map, &student4, &grade4);

    forEachResult = HashMap_ForEach(map, FindStudent, &student2);
    if (forEachResult == 1)
    {
        printf("HashMap_ForEachTest2 with valid paramters - pass\n");
    }
    else
    {
        printf("HashMap_ForEachTest2 with valid paramters  - FAILED\n");
    }
}

static void HashMap_ForEachTest3()
{
    HashMap *map = NULL;
    size_t forEachResult = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    forEachResult = HashMap_ForEach(NULL, PrintBucket, NULL);
    if (forEachResult == 0)
    {
        printf("HashMap_ForEachTest3 with NULL map- pass\n");
    }
    else
    {
        printf("HashMap_ForEachTest3 with NULL map-- FAILED\n");
    }
}
static void HashMap_ForEachTest4()
{
    HashMap *map = NULL;
    size_t forEachResult = 0;
    Student student1 = {5, "Moty"};
    Grade grade1 = {80, 90, 100};
    Student student2 = {10, "Libat"};
    Grade grade2 = {20, 30, 40};
    Student student3 = {22, "Carmi"};
    Grade grade3 = {100, 100, 100};
    map = HashMap_Create(10, HashFunc, IsEqual);
    HashMap_Insert(map, &student1, &grade1);
    HashMap_Insert(map, &student2, &grade2);
    HashMap_Insert(map, &student3, &grade3);
    forEachResult = HashMap_ForEach(map, NULL, NULL);
    if (forEachResult == 0)
    {
        printf("HashMap_ForEachTest4 with NULL ACTION FUNCTION- pass\n");
    }
    else
    {
        printf("HashMap_ForEachTest4 with NULL ACTION FUNCTION- FAILED\n");
    }
}
int main(void)
{
    HashCreateTest1();
    HashCreateTest2();
    HashCreateTest3();
    HashCreateTest4();
    HashMap_DestroyTest1();
    HashMap_DestroyTest2();
    HashMap_DestroyTest3();
    HashMap_DestroyTest4();
    HashMap_InsertTest1();
    HashMap_InsertTest2();
    HashMap_InsertTest3();
    HashMap_InsertTest4();
    HashMap_InsertTest5();
    HashMap_InsertTest6();
    HashMap_RemoveTest1();
    HashMap_RemoveTest2();
    HashMap_RemoveTest3();
    HashMap_RemoveTest4();
    HashMap_RemoveTest5();
    HashMap_RemoveTest6();
    HashMap_FindTest1();
    HashMap_FindTest2();
    HashMap_FindTest3();
    HashMap_FindTest4();
    HashMap_FindTest5();
    HashMap_SizeTest1();
    HashMap_SizeTest2();
    HashMap_SizeTest3();
    HashMap_SizeTest4();
    HashMap_ForEachTest1();
    HashMap_ForEachTest2();
    HashMap_ForEachTest3();
    HashMap_ForEachTest4();
    return 0;
}
