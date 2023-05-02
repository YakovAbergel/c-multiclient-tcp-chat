#include <stdlib.h> 	  /*malloc*/
#include <string.h>       /*strcpy*/
#include "group.h"       

#define FAIL    -1
#define SUCCESS  0
#define MAX_LEN_NAME 20

struct Group 
{
	char m_name[MAX_LEN_NAME];
	void* m_address;
	size_t m_numOfUsers;
};

Group *GroupCreate(char *_name, void *_address)
{
	Group *group = NULL;

	if(NULL == _name || NULL == _address)
	{
		return NULL;
	}

	if((group = (Group*)malloc(sizeof(Group))) == NULL)
	{
		return NULL;
	}

	strcpy(group->m_name, _name);
	group->m_address = _address;
	group->m_numOfUsers = 0;

	return group;
}

void GroupDestroy(Group **_group)
{
	if (NULL == _group || NULL == *_group)
	{
		return;
	}
	free(*_group);
	*_group = NULL;
}

int GroupIsEqual(Group *_group1, Group *_group2)
{
	return (_group1 == _group2);
}

void UserAddedToGroup(Group *_group)
{
	++_group->m_numOfUsers;
}

int RemovingUserFromGroup(Group *_group)
{
	if (_group->m_numOfUsers == 0)
	{
		return FAIL;
	}
	
	--_group->m_numOfUsers;
	return SUCCESS;
}

char *GetGroupName(Group *_group)
{
	return _group->m_name;
}

void *GetGroupAddress(Group *_group)
{
	return _group->m_address;
}

size_t GetNumOfUsersInGroup(Group *_group)
{
	if (_group == NULL)
	{
		return FAIL;
	}
	return _group->m_numOfUsers;
}
