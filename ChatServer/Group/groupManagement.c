#include <stdlib.h> /*malloc*/
#include <string.h> /*strcat, strlen*/
#include <stdio.h>
#include "group.h"
#include "groupManagement.h"
#include "../../GenericDataStructures+DynamicLibrary/HashMapGen/hashMap.h"  
#include "../../GenericDataStructures+DynamicLibrary/QueueGen/QueueGen.h"
#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 

#define MAX_GROUP_NUM 50
#define SUCCESS 0
#define FAIL -1
#define MAX_LEN_IP 12
#define MAX_LEN_PORT 5
#define BLOCK_SIZE (MAX_GROUP_NUM/10)
#define SWAP(x,y,t)\
		{\
			t temp;\
			temp = x;\
			x = y;\
			y = temp;\
		}

struct GroupAddress
{
	char m_ip[MAX_LEN_IP];
	char m_port[MAX_LEN_PORT]; 
};

struct GroupMan
{
	HashMap *m_groups;
	Queue *m_addrPool;
};

static GroupMan_result CreateAddressPool(Queue *_pool);
static size_t HashFuncGroupManGroupMan(void *_userName);
static int EqualityFuncGroupMan(const void *_userName1, const void *_userName2);
static void ReverseString(char *_str, int _length);
static GroupMan_result MyItoA(int _num, char *_buf);
static int InsertingGroupNameInVector(const void *_key, void *_pValue, void *_context);

GroupMan *GroupManCreate()
{
	GroupMan *groupMan = NULL;

	if((groupMan = (GroupMan*)malloc(sizeof(GroupMan))) == NULL)
	{
		return NULL;
	}

	if((groupMan->m_groups = HashMap_Create(MAX_GROUP_NUM, HashFuncGroupManGroupMan, EqualityFuncGroupMan)) == NULL)
	{
		free(groupMan);
		return NULL;
	}

	if((groupMan->m_addrPool = QueueCreate(MAX_GROUP_NUM)) == NULL)
	{
		HashMap_Destroy(&groupMan->m_groups, NULL, NULL);
		free(groupMan);
		return NULL;
	}

	if (CreateAddressPool(groupMan->m_addrPool) != GROUP_MAN_SUCCESS)
	{
		QueueDestroy(&groupMan->m_addrPool, NULL);
		HashMap_Destroy(&groupMan->m_groups,NULL,NULL);
		free(groupMan);
		return NULL;
	}

	return groupMan;
}

void GroupManDestroy(GroupMan **_groupMan)
{
	if (_groupMan == NULL || *_groupMan == NULL)
	{
		return;
	}

	HashMap_Destroy(&(*_groupMan)->m_groups, NULL, NULL); 
	QueueDestroy(&(*_groupMan)->m_addrPool, NULL);	
	free(*_groupMan);
	*_groupMan = NULL;
}

GroupMan_result GroupManCreateGroup(GroupMan *_groups, char *_groupName, char* _groupAddrIP)
{
	Group *group = NULL;
	GroupAddress *addr = NULL;
	char *groupName =  (char *)malloc(sizeof(char) * strlen(_groupName) + 1);
	if(groupName == NULL)
	{
		return GROUP_MAN_ALLOC_FAIL;
	}

	strcpy(groupName, _groupName);
	if (HashMap_Find(_groups->m_groups, _groupName, (void *)&group) == MAP_SUCCESS)
	{
		free(groupName);
		return GROUP_MAN_GROUP_ALREADY_EXISTS;
	}
	
	if (QueueRemove(_groups->m_addrPool, (void *)&addr) != QUEUE_SUCCESS)
	{
		free(groupName);
		return GROUP_MAN_ADDR_FAIL;
	}

	group = GroupCreate(_groupName, addr);
	if (group == NULL || (HashMap_Insert(_groups->m_groups, groupName, group) != MAP_SUCCESS))
	{
		GroupDestroy(&group);
		free(groupName);
		return GROUP_MAN_GROUP_ALLOC_FAIL;
	}

	UserAddedToGroup(group);
	strcpy(_groupAddrIP, addr->m_ip);

	return GROUP_MAN_SUCCESS;
}

GroupMan_result GroupManAddUser(GroupMan *_groups, char *_groupName, char* _groupAddrIP)
{
	Group *joiningGroup = NULL;
	GroupAddress *joiningGroupAddr = NULL;

	if (HashMap_Find(_groups->m_groups, _groupName, (void *)&joiningGroup) != MAP_SUCCESS) 
	{
		return GROUP_MAN_GROUP_DOESNT_EXISTS;
	}

	UserAddedToGroup(joiningGroup);
	joiningGroupAddr = (GroupAddress*)GetGroupAddress(joiningGroup);
	strcpy(_groupAddrIP, joiningGroupAddr->m_ip);

	return GROUP_MAN_SUCCESS;
}

GroupMan_result GroupManRemoveUser(GroupMan *_groups, char *_groupName)
{
	Group *deletingGroup = NULL;
	void *key = NULL;
	void *pValue = NULL;

	if(HashMap_Find(_groups->m_groups, _groupName, (void *)&deletingGroup) != MAP_SUCCESS)
	{
		return GROUP_MAN_GROUP_DOESNT_EXISTS;
	}

	RemovingUserFromGroup(deletingGroup);
	if (GetNumOfUsersInGroup(deletingGroup) == 0)
	{
		HashMap_Remove(_groups->m_groups, _groupName, &key, &pValue);
		free(key);
		GroupDestroy(&deletingGroup);
	}
	return GROUP_MAN_SUCCESS;
}

Vector* GroupManGetAllActiveGroups(GroupMan* _groups)
{
	Vector* groupNames = NULL; 

	if((groupNames = VectorCreate(HashMap_Size(_groups->m_groups), BLOCK_SIZE)) == NULL)
	{
		return NULL;
	}

	HashMap_ForEach(_groups->m_groups, InsertingGroupNameInVector, groupNames);

	return groupNames;
}

static GroupMan_result CreateAddressPool(Queue *_pool)
{
	int i;
	char temp[4] = {0};
	GroupAddress *groupAddr = NULL;
	char *addr = "224.0.0.";
	char *port = "2346";

	for (i = 1; i <= MAX_GROUP_NUM; ++i)
	{
		if((groupAddr = (GroupAddress*)malloc(sizeof(GroupAddress))) == NULL)
		{
			return GROUP_MAN_GROUP_ADDR_ALLOC_FAIL;
		}

		strcpy(groupAddr->m_ip, addr);
		MyItoA(i, temp);
		strcat(groupAddr->m_ip, temp);
		strcpy(groupAddr->m_port, port);
		if (QueueInsert(_pool, groupAddr) != QUEUE_SUCCESS)
		{
			return GROUP_MAN_QUEUE_INSERT_ERROR;
		}
	}

	return GROUP_MAN_SUCCESS;
}

static int InsertingGroupNameInVector(const void *_key, void *_pValue, void *_context)
{
	char *groupName = GetGroupName((Group*)_pValue);
	VectorAppend((Vector*)_context, groupName);
	return 1;
}

static size_t HashFuncGroupManGroupMan(void *_userName)
{
	size_t counter = 0;
    int i = 1;
	char* temp = (char*)_userName;
	
	while(*temp != '\0')
	{
		counter += (*temp * i);
		++temp;
        ++i;
	}
	return counter;
}

static int EqualityFuncGroupMan(const void *_userName1, const void *_userName2)
{
	if(strcmp((char*)_userName1, (char*)_userName2))
	{
		return 0;
	}
	return 1;
}

static void ReverseString(char *_str, int _length)
{
	int i = 0;
	char temp;
	for (i = 0; i < _length / 2; i++)
	{
		SWAP(_str[i], _str[_length - 1 - i], char);
	}
}

static GroupMan_result MyItoA(int _num, char *_buf)
{
	int i;
	int sign = 0;

	if (_buf == NULL)
	{
		return GROUP_MAN_BUF_NOT_INITIAILIZED;
	}

	if (_num < 0)
	{
		sign = -1;
		_num = _num * sign;
	}
	for (i = 0; _num > 0; i++)
	{
		_buf[i] = '0' + _num % 10;
		_num = _num / 10;
	}
	if (sign == -1)
	{
		i++;
		_buf[i] = '-';
	}
	_buf[i + 1] = '\0';
	ReverseString(_buf, strlen(_buf));
	return GROUP_MAN_SUCCESS;
}
