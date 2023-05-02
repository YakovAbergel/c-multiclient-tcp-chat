#ifndef __USER_H__
#define __USER_H__
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"

typedef struct User User;

typedef enum User_Result 
{
	USER_SUCCESS = 0,
	USER_LIST_PUSH_HEAD_ERROR,
	USER_ALLOCATION_ERROR,
	USER_GROUP_NOT_FOUND,
	USER_GROUP_DISCONNECT_SUCCESS,
	USER_INSERT_ERROR,
	USER_ALREADY_IN_GROUP
}User_Result;


User* UserCreate(char* _userName, char* _password);

void GetPassword(User* _user,char* _password);

void GetUserName(User* _user,char* _userName);

void SetUserToConnect(User* _user);

void SetUserToDisConnect(User* _user);

int UserIsConnect(User* _user);

User_Result UserConnectToGroup(User* _user, char* _groupName, int _flag);

List* UserGetGroupsList(User* _user);

User_Result UserDisConnectFromGroup(User* _user, char* _groupName);

void DeletingAllUserGroups(User* _user);


#endif /* __USER_H__ */
