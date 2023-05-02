#include "../ServerNetGen/serverNetGen.h"
#include "../Protocol/protocol.h"
#include "../User/userManagment.h"
#include "../Group/groupManagement.h"
#include "serverManagement.h"
#include <stdlib.h>
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"   
#include "../../GenericDataStructures+DynamicLibrary/ListFunc/listFunc.h"  
#include "../../GenericDataStructures+DynamicLibrary/ListItr/listItr.h"  
#include <stdio.h>

#define MAX_LEN_NAME 20
#define MAX_LEN_PASSWORD 10
#define MAX_NUM_OF_CLIENT 1024
#define PORT 2345
#define BACK_LOG 500
#define MAX_LEN_IP 12
#define PACK_SIZE 256


struct ChatServer
{
	Server* m_server;
    UserMan* m_users;
	GroupMan* m_groups;
};

static int GotMsg(int _clientSock, void *_msg, size_t _msgSize, void* _appServer);
static ChatServer_Result FindingCorrectFunc(Tag_Protocol _tag, char* _recvPackBuff, char* _packMsg, int* _replyMsgSize, ChatServer* _chatServer);
static ChatServer_Result RegisterClient(char* _recievedPack, UserMan* _users);
static ChatServer_Result ClientLogin(char* _recievedPack, UserMan* _users);
static ChatServer_Result CreateChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan, char* _groupIP);
static ChatServer_Result JoinToChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan, char* _groupIP);
static ChatServer_Result LeaveToChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan);
static Vector* InsertAllNamesOfGroupsInVector(GroupMan* _groupMan);
static ChatServer_Result LogOutFromChat(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan);
static int LogUserOut(void* _element, void* _context);
static size_t HashFuncServerMan(void* _userName);
static int EqualityFuncServerMan(const void* _userName1, const void* _userName2);

ChatServer* ChatServerCreate()
{
	ChatServer* chatServer = NULL;

	if((chatServer = (ChatServer*)malloc(sizeof(ChatServer))) == NULL)
	{
		return NULL;
	}

    if((chatServer->m_users = CreateUserMan(MAX_NUM_OF_CLIENT, HashFuncServerMan, EqualityFuncServerMan)) == NULL)
    {
        free(chatServer);
        return NULL;
    }

	if((chatServer->m_groups = GroupManCreate()) == NULL)
    {
		UserManDestroy(&chatServer->m_users);
        free(chatServer);
        return NULL;
    }

    if((chatServer->m_server = InitServer(PORT, BACK_LOG, MAX_NUM_OF_CLIENT, NULL, NULL, GotMsg, NULL, chatServer)) == NULL)
    {
		GroupManDestroy(&chatServer->m_groups);
        UserManDestroy(&chatServer->m_users);
        free(chatServer);
        return NULL;
    }

	return chatServer;
}

void ChatServerDestroy(ChatServer** _chatServer)
{
	if(_chatServer == NULL || *_chatServer == NULL)
	{
		ServerDestroy(&(*_chatServer)->m_server);
		GroupManDestroy(&(*_chatServer)->m_groups);
		UserManDestroy(&(*_chatServer)->m_users);
		free(*_chatServer);
		*_chatServer = NULL;
	}
}

Server_Result RunChatServer(ChatServer* _chatServer)
{
    Server_Result res;

    if(_chatServer == NULL)
    {
        return SERVERMAN_UNINITIALIZED_ERROR; 
    }

	LoadingRegisteredUsers(_chatServer->m_users);
    res = RanServer(_chatServer->m_server);

    return res;
}

static int GotMsg(int _clientSock, void *_msg, size_t _msgSize, void* _appServer)
{
	Tag_Protocol tag = 0;
	char packMsg[PACK_SIZE] = {0};
	int replyMsgSize = 0;

	if(_msg == NULL)
	{
		return SERVER_POINTER_NOT_INITIALIZED_ERROR;
	}

	tag = ProtocolGetTag((char*)_msg);
	FindingCorrectFunc(tag, (char*)_msg, packMsg, &replyMsgSize, (ChatServer*)_appServer);
    ServerSendMsg(_clientSock, packMsg, replyMsgSize);
	return SERVERMAN_SUCCESS;
}

static ChatServer_Result FindingCorrectFunc(Tag_Protocol _tag, char* _recvPackBuff, char* _packMsg, int* _replyMsgSize, ChatServer* _chatServer)
{
    ChatServer_Result status;
	char groupIP[MAX_LEN_IP];
	char* groupPort = {"2346"};
	Vector* groupsVector = NULL;

	switch(_tag)
	{
		case TAG_REGESTRESTION_REQUEST:
			status = RegisterClient(_recvPackBuff, _chatServer->m_users);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolRegReplyPack(_packMsg, status);
			break;

        case TAG_LOG_IN_REQUEST:
			status = ClientLogin(_recvPackBuff, _chatServer->m_users);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolLogReplyPack(_packMsg, status);
			break;

		case TAG_CREAT_GROUP_REQUEST:
			status = CreateChatGroup(_recvPackBuff, _chatServer->m_groups, _chatServer->m_users, groupIP);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolCreateGroupReplyPack(_packMsg, groupIP, groupPort, status);
			break;

		case TAG_JOIN_GROUP_REQUEST:
			status = JoinToChatGroup(_recvPackBuff, _chatServer->m_groups, _chatServer->m_users, groupIP);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolJoinGroupReplyPack(_packMsg, groupIP, groupPort, status);
			break;

		case TAG_LEAVE_GROUP_REQUEST:
			status = LeaveToChatGroup(_recvPackBuff, _chatServer->m_groups, _chatServer->m_users);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolLeaveGroupReplyPack(_packMsg, status);
			break;

		case TAG_SHOW_ALL_EXISTING_GROUPS_REQUEST:
			groupsVector = InsertAllNamesOfGroupsInVector(_chatServer->m_groups);
			if(groupsVector != NULL)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolShowAllExistingGroupsReplyPack(_packMsg, groupsVector);
			break;

		case TAG_LOG_OUT_REQUEST:
			status = LogOutFromChat(_recvPackBuff, _chatServer->m_groups, _chatServer->m_users);
			if(status == SERVERMAN_SUCCESS)
			{
				status = 1;
			}
			else
			{
				status = 0;
			}
			*_replyMsgSize = ProtocolLogOutReplyPack(_packMsg, status);
			break;


	}
	return SERVERMAN_SUCCESS;	
}

static ChatServer_Result RegisterClient(char* _recievedPack, UserMan* _users)
{
	char userName[MAX_LEN_NAME];
	char password[MAX_LEN_PASSWORD];
	UserMan_Result status = 0;

	ProtocolRegRequestUnPack(_recievedPack, userName, password);
	status = UserManRegistration(_users, userName, password);
	if(status == USER_MAN_ALREADY_REGISTERED)
	{
		return SERVER_MAN_USER_ALREADY_REGISTERED;
	}
	else if(status == USER_MAN_INSERT_ERROR || status == USER_MAN_ALLOCATION_ERROR)
	{
		return SERVER_MAN_USER_INSERT_FAILED;
	}

	return SERVERMAN_SUCCESS;
}

static ChatServer_Result ClientLogin(char* _recievedPack, UserMan* _users)
{
	char userName[MAX_LEN_NAME];
	char password[MAX_LEN_PASSWORD];
	UserMan_Result status = 0;

	ProtocolLogRequestUnPack(_recievedPack, userName, password);
	status = UserManLogIn(_users, userName, password);
	if(status == USER_MAN_NOT_REGISTERED)
	{
		return SERVER_MAN_USER_NOT_REGISTERED;
	}
	else if(status == USER_MAN_ALREADY_LOGGED_IN)
	{
		return SERVER_MAN_USER_ALREADY_LOGGED_IN;
	}
	else if(status == USER_MAN_PASSWORD_INCORRECT)
	{
		return SERVER_MAN_USER_PASSWORD_INCORRECT;
	}

	return SERVERMAN_SUCCESS;
}

static ChatServer_Result CreateChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan, char* _groupIP)
{
	char groupName[MAX_LEN_PASSWORD];
	char userName [MAX_LEN_NAME];
	int status = 0;
	int flag = 0;

	ProtocolCreateGroupRequestUnPack(_recievedPack, groupName, userName);
	status = GroupManCreateGroup(_groupMan, groupName, _groupIP);
	if(status == GROUP_MAN_GROUP_ALREADY_EXISTS)
	{
		return SERVER_MAN_GROUP_ALREADY_EXISTS;
	}
	else if(status == GROUP_MAN_ADDR_FAIL || status == GROUP_MAN_ALLOC_FAIL)
	{
		return SERVER_MAN_GROUP_CREATE_FAILED;
	}

	status = UserManAddGroupToUserGroupList(_userMan, userName, groupName, flag);
	if(status == USER_MAN_NOT_REGISTERED)
	{
		return SERVER_MAN_USER_NOT_REGISTERED;
	}
	else if(status == USER_MAN_ADD_GROUP_ERR)
	{
		return SERVER_MAN_USER_ADD_GROUP_ERR;
	}
	
	return SERVERMAN_SUCCESS;
}

static ChatServer_Result JoinToChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan, char* _groupIP)
{
	char groupName[MAX_LEN_NAME] = {0};
	char userName [MAX_LEN_PASSWORD] = {0};
	int status = 0;
	int flag = 1;
	
	ProtocolJoinGroupRequestUnPack(_recievedPack, groupName, userName);
	status = GroupManAddUser(_groupMan, groupName, _groupIP);
	if(status == GROUP_MAN_GROUP_DOESNT_EXISTS)
	{
		return SERVER_MAN_GROUP_DOESNT_EXISTS;
	}

	status = UserManAddGroupToUserGroupList(_userMan, userName, groupName, flag);
	if(status == USER_MAN_NOT_REGISTERED)
	{
		return SERVER_MAN_USER_NOT_REGISTERED;
	}
	else if(status == USER_MAN_ADD_GROUP_ERR)
	{
		return SERVER_MAN_USER_ADD_GROUP_ERR;
	}

	return SERVERMAN_SUCCESS;
}

static ChatServer_Result LeaveToChatGroup(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan)
{
	char groupName[MAX_LEN_NAME] = {0};
	char userName [MAX_LEN_PASSWORD] = {0};
	int status = 0;

	ProtocolLeaveGroupRequestUnPack(_recievedPack, groupName, userName);
	status = GroupManRemoveUser(_groupMan, groupName);
	if(status == GROUP_MAN_GROUP_DOESNT_EXISTS)
	{
		return SERVER_MAN_GROUP_DOESNT_EXISTS;
	}

	status = UserManRemoveGroupFromUsersGroupList(_userMan, userName, groupName);
	if(status == USER_MAN_GROUP_NOT_FOUND)
	{
		return SERVER_MAN_USER_GROUP_NOT_FOUND;
	}

	return SERVERMAN_SUCCESS;
}

static Vector* InsertAllNamesOfGroupsInVector(GroupMan* _groupMan)
{
	Vector* vec = NULL;
	if((vec = GroupManGetAllActiveGroups(_groupMan)) == NULL)
	{
		return NULL;
	}
	return vec;
}

/*static ChatServer_Result InsertAllNamesOfGroupsInVector(GroupMan* _groupMan, Vector* _vec)
{
	if((_vec = GroupManGetAllActiveGroups(_groupMan)) == NULL)
	{
		return SERVER_MAN_GROUP_VECTOR_ERR;
	}
	return SERVERMAN_SUCCESS;
}*/

static ChatServer_Result LogOutFromChat(char* _recievedPack, GroupMan* _groupMan, UserMan* _userMan)
{
	char userName [MAX_LEN_NAME] = {0};
	List* groupsList = NULL;
	ListItr* begin = NULL;
	ListItr* end = NULL;

	ProtocolLogOutRequestUnPack(_recievedPack, userName);
	groupsList = UserManGetUsersList(_userMan, userName);
	if(groupsList != NULL)
	{
		begin = ListItrBegin(groupsList);
		end = ListItrEnd(groupsList);
		ListItrForEach(begin, end, LogUserOut, (GroupMan*)_groupMan);
		UserManLogOut(_userMan, userName);
		return SERVERMAN_SUCCESS;
	}
	
	return SERVER_MAN_GROUP_DOESNT_EXISTS;
	
}

static int LogUserOut(void* _element, void* _context)
{
	GroupManRemoveUser((GroupMan*) _context, (char*) _element);
	return 1;
}

static size_t HashFuncServerMan(void* _userName)
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

static int EqualityFuncServerMan(const void* _userName1, const void* _userName2)
{
	if(strcmp((char*)_userName1, (char*)_userName2))
	{
		return 0;
	}
	return 1;
}

