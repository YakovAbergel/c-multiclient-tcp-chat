#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 

#define FAIL 0
#define SUCCESS 1

typedef enum Tag_Protocol
{
    TAG_REGESTRESTION_REQUEST = 1,
    TAG_REGESTRESTION_REPLY,
    TAG_LOG_IN_REQUEST,
    TAG_LOG_IN_REPLY,
    TAG_EXIT_REQUEST,
    TAG_EXIT_REPLY,
    TAG_JOIN_GROUP_REQUEST,
    TAG_JOIN_GROUP_REPLY,
    TAG_LEAVE_GROUP_REQUEST,
    TAG_LEAVE_GROUP_REPLY,
    TAG_CREAT_GROUP_REQUEST,
    TAG_CREAT_GROUP_REPLY,
    TAG_LOG_OUT_REQUEST,
    TAG_LOG_OUT_REPLY,
    TAG_SHOW_ALL_EXISTING_GROUPS_REQUEST,
    TAG_SHOW_ALL_EXISTING_GROUPS_REPLY
}Tag_Protocol;

int ProtocolRegRequestPack(char* _buffer, char* _userName, char* _password);
int ProtocolRegRequestUnPack(char* _buffer, char* _userName, char* _password);
int ProtocolRegReplyPack(char* _buffer, int _status);
int ProtocolRegReplyUnPack(char* _buffer, int* _status);

int ProtocolLogRequestPack(char* _buffer, char* _userName, char* _password);
int ProtocolLogRequestUnPack(char* _buffer, char* _userName, char* _password);
int ProtocolLogReplyPack(char* _buffer, int _status);
int ProtocolLogReplyUnPack(char* _buffer, int* _status);

int ProtocolCreateGroupRequestPack(char* _buffer, char * _groupName,char* _userName);
int ProtocolCreateGroupRequestUnPack(char* _buffer, char* _groupName, char* _userName);
int ProtocolCreateGroupReplyPack(char* _buffer, char* _ip, char* _port, int _status);
int ProtocolCreateGroupReplyUnPack(char* _buffer, char* _ip, char* _port, int* _status);

int ProtocolJoinGroupRequestPack(char* _buffer, char * _groupName,char* _userName);
int ProtocolJoinGroupRequestUnPack( char* _buffer,char * _groupName,char* _userName);
int ProtocolJoinGroupReplyPack(char* _buffer, char* _ip, char* _port, int _status);
int ProtocolJoinGroupReplyUnPack( char* _buffer, char* _ip ,char* _port , int* _status);

int ProtocolLeaveGroupRequestPack(char* _buffer, char * _groupName,char* _userName);
int ProtocolLeaveGroupRequestUnPack(char* _buffer,char * _groupName,char* _userName);
int ProtocolLeaveGroupReplyPack(char* _buffer, int _status);
int ProtocolLeaveGroupReplyUnPack(char* _buffer, int* _status);

int ProtocolShowAllExistingGroupsRequestPack(char* _buffer);
int ProtocolShowAllExistingGroupsReplyPack(char* _buffer, Vector* _vector);
int ProtocolShowAllExistingGroupsReplyUnPack(char* _buffer, Vector* _vector);

int ProtocolLogOutRequestPack(char* _buffer, char *_userName);
int ProtocolLogOutRequestUnPack(char* _buffer, char *_userName);
int ProtocolLogOutReplyPack(char* _buffer, int _status);
int ProtocolLogOutReplyUnPack(char* _buffer, int* _status);


#endif /* __PROTOCOL_H__ */
