#include <stdio.h>   /*printf*/
#include <stdlib.h>  /*size_t*/
#include <string.h>  /*strcpy*/

#include "../../GenericDataStructures+DynamicLibrary/HashMapGen/hashMap.h"  
#include "userManagment.h" 
#include "user.h"  

#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"   
#include "../../GenericDataStructures+DynamicLibrary/ListFunc/listFunc.h"  
#include "../../GenericDataStructures+DynamicLibrary/ListItr/listItr.h"  

#define LIMIT 20
#define SUCCESS 0
#define FAIL -1
#define MAX_LEN_NAME 20
#define MAX_LEN_PASSWORD 10

struct UserMan
{
	HashMap* m_users;
};

static void WritingDataToFile(char *_name, char *_password);


UserMan* CreateUserMan(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	UserMan* userMan = NULL;
	if((userMan = (UserMan*)malloc(sizeof(UserMan)))  == NULL)
	{
		return NULL;
	}

	if((userMan->m_users = HashMap_Create(_capacity, _hashFunc, _keysEqualFunc)) == NULL)
	{
		free(userMan);
		return NULL;
	}

	return userMan;
}

void UserManDestroy(UserMan** _UserMan)
{
	if(NULL == _UserMan || NULL == *_UserMan)
	{
		HashMap_Destroy(&(*_UserMan)->m_users, NULL, NULL);
		free(*_UserMan);
		*_UserMan = NULL;
	}
}

UserMan_Result UserManRegistration(UserMan* _UserMan, char* _userName, char* _password)
{
	User* newUser = NULL;
	void* pValue = NULL;
	Map_Result status;
	char* key = (char*)malloc(sizeof(char) * strlen(_userName) + 1);
	strcpy(key, _userName);

	status = HashMap_Find(_UserMan->m_users, key, &pValue);
	if(status == MAP_KEY_NOT_FOUND_ERROR)
	{
		newUser = UserCreate(_userName, _password);
		if(newUser == NULL)
		{
			return USER_MAN_ALLOCATION_ERROR;
		}
	}
	else
	{
		return USER_MAN_ALREADY_REGISTERED;
	}
	if(HashMap_Insert(_UserMan->m_users, key,  newUser) != MAP_SUCCESS)
	{
		return USER_MAN_INSERT_ERROR;
	}
	WritingDataToFile(_userName, _password);
	return USER_MAN_SUCCESS;
}

UserMan_Result UserManLogIn(UserMan* _UserMan, char* _userName, char* _password)
{
	void* pValue = NULL;
	Map_Result status;
	char userPassword[MAX_LEN_PASSWORD] = {0};
	char userName[MAX_LEN_NAME] = {0};

	status = HashMap_Find(_UserMan->m_users, _userName, &pValue);

	if(status != MAP_SUCCESS)
	{
		return USER_MAN_NOT_REGISTERED;
	}

	if(UserIsConnect((User*)pValue))
	{
		return USER_MAN_ALREADY_LOGGED_IN;
	}

	GetPassword((User*)pValue, userPassword);
	GetUserName((User*)pValue, userName);

	if(strcmp(userPassword, _password) == 0)
	{
		SetUserToConnect((User*)pValue);
        return USER_MAN_SUCCESS;
	}

	return USER_MAN_PASSWORD_INCORRECT;
	
}

UserMan_Result UserManAddGroupToUserGroupList(UserMan* _userMan, char* _userName, char* _groupName, int _flag)
{
	User* user = NULL;
	int status = 0;
	char userName[MAX_LEN_NAME] = {0};

	status = HashMap_Find(_userMan->m_users, _userName, (void*)&user);
	if(status == MAP_SUCCESS)
	{
		/*GetUserName(user, userName);*/
		if(UserConnectToGroup(user, _groupName, _flag) != USER_SUCCESS)
		{
			return USER_MAN_ADD_GROUP_ERR;
		}
		return USER_SUCCESS;
	}
	return USER_MAN_NOT_REGISTERED;
}

UserMan_Result UserManRemoveGroupFromUsersGroupList(UserMan* _userMan, char* _userName, char* _groupName)
{
	User* user = NULL;
	int status = 0;

	if((status = HashMap_Find(_userMan->m_users, _userName, (void*)&user)) != MAP_SUCCESS)
	{
		return USER_MAN_ALREADY_REGISTERED;
	}

	if((status = UserDisConnectFromGroup(user, _groupName)) == USER_GROUP_NOT_FOUND)
	{
		return USER_MAN_GROUP_NOT_FOUND;
	}

	return USER_SUCCESS;
}

void UserManLogOut(UserMan* _userMan, char* _userName)
{
	HashMap* usersHash = _userMan->m_users;
	void* user = NULL;
	int status = 0;
	status = HashMap_Find(usersHash, _userName, &user);
	SetUserToDisConnect((User*)user);
	DeletingAllUserGroups((User*)user);
}

List* UserManGetUsersList(UserMan* _userMan, char* _userName)
{
	User* user = NULL;
	int status = 0;

	status = HashMap_Find(_userMan->m_users, _userName, (void*)&user);
	if(status == MAP_SUCCESS)
	{
		return UserGetGroupsList(user);
	}
	return NULL;
}

void LoadingRegisteredUsers(UserMan* _usersMan)
{
	FILE* fp;
	User* newUser = NULL;
	char name[MAX_LEN_NAME] = {0};
	char pass[MAX_LEN_PASSWORD] = {0};
	char *addName = NULL;

	fp =fopen("RegisteredUsers.txt", "r");
	if (NULL == fp)
	{
		return;
	}

	while (fgets(name, MAX_LEN_NAME, fp) != NULL)
	{
		fgets(pass, MAX_LEN_PASSWORD, fp);
		name[strcspn(name, "\n")] = '\0';
		pass[strcspn(pass, "\n")] = '\0';
		newUser = UserCreate(name, pass);
		if(newUser != NULL)
		{
			addName = (char*)malloc(sizeof(char) * strlen(name) + 1);
			strcpy(addName, name);
			HashMap_Insert(_usersMan->m_users, addName,  newUser);
		}
	}

	fclose(fp);	
}

static void WritingDataToFile(char *_name, char *_password)
{
	FILE *fp;
	fp =fopen("RegisteredUsers.txt", "a");
	if (NULL == fp)
	{
		printf("Failed to open file.\n");
	}
	fprintf(fp, "%s\n", _name);
	fprintf(fp, "%s\n", _password);
	fclose(fp);
}

