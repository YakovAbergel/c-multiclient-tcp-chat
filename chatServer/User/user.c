#include <string.h>  /*strcpy*/
#include <stdlib.h>  /*malloc*/
#include <stdio.h>   /*printf*/
#include "user.h"  
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"
#include "../../GenericDataStructures+DynamicLibrary/ListItr/listItr.h"
#include "../../GenericDataStructures+DynamicLibrary/ListFunc/listFunc.h"

#define CONNECT 1
#define NOT_CONNECT 0
#define TRUE      1
#define FALSE     0
#define MAX_LEN_NAME 20
#define MAX_LEN_PASSWORD 10

struct User
{
	char m_userName[MAX_LEN_NAME];
	char m_userPassword[MAX_LEN_PASSWORD];
    int m_isConnect;
	List* m_listGroups;
};

static int SearchUserInGroup(void * _groupName1, void* _groupName2);
static User_Result IsUserAlreadyInGroup(List* _userGroupsList, char* _groupName);

User* UserCreate(char* _userName, char* _password)
{
	User* user = NULL;
	
	if((user = (User*)malloc(sizeof(User))) == NULL)
	{
		return NULL;
	}
	
	if((user->m_listGroups = ListCreate()) == NULL)
	{
		free(user);
		return NULL;
	}

	strcpy(user->m_userName, _userName);
	strcpy(user->m_userPassword, _password);
	user->m_isConnect = NOT_CONNECT;
	
	return user;
}

void GetPassword(User* _user,char* _password)
{
	strcpy(_password, _user->m_userPassword);
}

void GetUserName(User* _user,char* _userName)
{
	strcpy(_userName, _user->m_userName);
}

void SetUserToConnect(User* _user)
{
	_user->m_isConnect = CONNECT;
}

void SetUserToDisConnect(User* _user)
{
	_user->m_isConnect = NOT_CONNECT;
}

int UserIsConnect(User* _user)
{
	return (_user->m_isConnect == CONNECT);
}

User_Result UserConnectToGroup(User* _user, char* _groupName, int _flag)
{
	List* userGroupsList = _user->m_listGroups;
	char* groupName = (char*)malloc(sizeof(char) * strlen(_groupName) + 1);
	if(groupName == NULL)
	{
		return USER_ALLOCATION_ERROR;
	}
	
	strcpy(groupName, _groupName);
	
	if(_flag == 1)
	{
		if(IsUserAlreadyInGroup(userGroupsList, groupName) == USER_ALREADY_IN_GROUP)
		{
			return USER_ALREADY_IN_GROUP;
		}
	}
	
	if(ListPushHead(userGroupsList, groupName) != LIST_SUCCESS)
	{
		return USER_LIST_PUSH_HEAD_ERROR;
	}
	
	return USER_SUCCESS;
}

List* UserGetGroupsList(User* _user)
{
	return _user->m_listGroups;
}

User_Result UserDisConnectFromGroup(User* _user, char* _groupName)
{
	List* userGroupsList = _user->m_listGroups;
	ListItr begin = ListItrBegin(userGroupsList);
	ListItr end = ListItrEnd(userGroupsList);
	ListItr temp = NULL;
	
	if(begin == end)
	{
		return USER_GROUP_NOT_FOUND;
	}
	
	temp = ListItrFindFirst(begin, end, SearchUserInGroup, _groupName);
	free(ListItrRemove(temp));
	return USER_GROUP_DISCONNECT_SUCCESS;
}

void DeletingAllUserGroups(User* _user)
{
	List* userGroupsList = _user->m_listGroups;
	ListItr begin = ListItrBegin(userGroupsList);
	ListItr end = ListItrEnd(userGroupsList);
	ListItr next = NULL;

	while(begin != end)
	{
		next = ListItrNext(begin);
		free(ListItrGet(begin));/**/
		ListItrRemove(begin);
		begin = next;
	}
}

static User_Result IsUserAlreadyInGroup(List* _userGroupsList, char* _groupName)
{
	ListItr begin = ListItrBegin(_userGroupsList);
	ListItr end = ListItrEnd(_userGroupsList);
	char* currGroupName = NULL;
	while(begin != end)
	{
		currGroupName = (char*)ListItrGet(begin);
		if(strcmp(currGroupName, _groupName) == 0)
		{
			return USER_ALREADY_IN_GROUP;
		}
		begin = ListItrNext(begin);
	}
	return USER_SUCCESS;
}

static int SearchUserInGroup(void * _groupName1, void* _groupName2)
{
    if((strcmp((char*)_groupName1, (char*)_groupName2)) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
