#ifndef __USERMANAGMENT_H__
#define __USERMANAGMENT_H__

#include "../../GenericDataStructures+DynamicLibrary/HashMapGen/hashMap.h"  
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"   


typedef struct UserMan UserMan;


typedef enum UserMan_Result
{
    USER_MAN_SUCCESS,
    USER_MAN_ALREADY_REGISTERED,
    USER_MAN_NOT_REGISTERED,
    USER_MAN_ALREADY_LOGGED_IN,
    USER_MAN_PASSWORD_INCORRECT,
    USER_MAN_ALLOCATION_ERROR,
    USER_MAN_INSERT_ERROR, 
    USER_MAN_GROUP_NOT_FOUND,
    USER_MAN_ADD_GROUP_ERR
    
}UserMan_Result;


UserMan* CreateUserMan(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);

void UserManDestroy(UserMan** _UserMan);

UserMan_Result UserManRegistration(UserMan* _UserMan, char* _userName, char* _password);

UserMan_Result UserManLogIn(UserMan* _UserMan, char* _userName, char* _password);

UserMan_Result UserManAddGroupToUserGroupList(UserMan* _userMan, char* _userName, char* _groupName, int _flag);

UserMan_Result UserManRemoveGroupFromUsersGroupList(UserMan* _userMan, char* _userName, char* _groupName);

void LoadingRegisteredUsers(UserMan* _usersMan);

void UserManLogOut(UserMan* _userMan, char* _userName);

List* UserManGetUsersList(UserMan* _userMan, char* _userName);



#endif /* __USERMANAGMENT_H__ */
