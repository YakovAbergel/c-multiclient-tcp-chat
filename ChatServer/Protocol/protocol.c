#include "protocol.h"
#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 
#include <string.h>
#include <stdio.h>
#include <stdlib.h> /*malloc*/


int ProtocolRegRequestPack(char* _buffer, char* _userName, char* _password)
{
    int nameLength, passwordLength, length = 0;
    if(_userName == NULL || _password == NULL || _buffer == NULL)
    {
        return FAIL;
    }
    nameLength = strlen (_userName);
    passwordLength = strlen (_password);
    length = nameLength + passwordLength + 2;
    *_buffer = TAG_REGESTRESTION_REQUEST;
    *(_buffer + 1) = length;
    *(_buffer + 2) = nameLength;
    strcpy ((_buffer + 3), _userName);
    *(_buffer + 3 + nameLength) = passwordLength;
    strcpy ((_buffer + 4 + nameLength), _password);
    return length+2;
}     

int ProtocolRegRequestUnPack(char* _buffer, char* _userName, char* _password)
{
    int nameLength = 0, passwordLength = 0;
    if(_userName == NULL || _password == NULL || _buffer == NULL)
    {
        return FAIL;
    }
    nameLength  = _buffer[2];
    passwordLength  = _buffer[nameLength + 3];
    strncpy( _userName,&(_buffer[3]),nameLength);
    _userName[nameLength] = '\0';
    strncpy(_password ,&(_buffer[ nameLength + 4]),passwordLength);
    _password[passwordLength]  = '\0';

    return SUCCESS; 
}

int ProtocolRegReplyPack(char* _buffer, int _status)
{
    int len;
    if(_buffer == NULL)
    {
        return FAIL;
    }
    
    len = 2;
    *_buffer = TAG_REGESTRESTION_REPLY;
    *(_buffer + 1) = len;
    *(_buffer + 2) = 1;
    *(_buffer + 3) = _status;
    return len + 2;
}

int ProtocolRegReplyUnPack(char* _buffer, int* _status)
{
    if (_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    *_status =_buffer[3];
     return SUCCESS;
}

int ProtocolLogRequestPack(char* _buffer, char* _userName, char* _password)
{
    int nameLength, passwordLength, length = 0;
    if(_userName == NULL || _password == NULL || _buffer == NULL)
    {
        return FAIL;
    }
    nameLength = strlen (_userName);
    passwordLength = strlen (_password);
    length = nameLength + passwordLength + 2;
    *_buffer = TAG_LOG_IN_REQUEST;
    *(_buffer + 1) = length;
    *(_buffer + 2) = nameLength;
    strcpy ((_buffer + 3), _userName);
    *(_buffer + 3 + nameLength) = passwordLength;
    strcpy ((_buffer + 4 + nameLength), _password);
    return length + 2;
}     

int ProtocolLogRequestUnPack(char* _buffer, char* _userName, char* _password)
{
    int nameLength, passwordLength;
    if(_userName == NULL || _password == NULL || _buffer == NULL)
    {
        return FAIL;
    }

    nameLength = *(_buffer+2);
    passwordLength = *(_buffer +3 + nameLength);
    strncpy (_userName, (_buffer + 3), nameLength);
    *(_userName +nameLength) ='\0';
    strncpy (_password, (_buffer + 4 + nameLength), passwordLength);
    *(_password + passwordLength) = '\0';

    return SUCCESS; 
}

int ProtocolLogReplyPack(char* _buffer, int _status)
{
    int len;

    if(_buffer == NULL )
    {
        return FAIL;
    }

    len = 2;
    *_buffer = TAG_LOG_IN_REPLY;
    *(_buffer + 1) = len;
    *(_buffer + 2) = 1;
    *(_buffer + 3) = _status;
    return len + 2;
}

int ProtocolLogReplyUnPack(char* _buffer, int* _status)
{
    if (_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    *_status =_buffer[3];
     return SUCCESS;
}

int ProtocolCreateGroupRequestPack(char* _buffer, char * _groupName,char* _userName)
{
    int userNameLength, groupNameLength, length = 0;
    if(_userName == NULL || _groupName == NULL || _buffer == NULL)
    {
        return FAIL;
    }
    userNameLength = strlen (_userName);
    groupNameLength = strlen (_groupName);
    length = userNameLength + groupNameLength + 2;
    *_buffer = TAG_CREAT_GROUP_REQUEST;
    *(_buffer + 1) = length;
    *(_buffer + 2) = groupNameLength;
    strcpy((_buffer + 3), _groupName);
    *(_buffer + 3 + groupNameLength) = userNameLength;
    strcpy ((_buffer + 4 + groupNameLength), _userName);
    return length + 2;
}

int ProtocolCreateGroupRequestUnPack(char* _buffer, char* _groupName, char* _userName)
{
    int userNameLength, groupNameLength;
    if(_userName == NULL || _groupName == NULL || _buffer == NULL)
    {
        return FAIL;
    }

    groupNameLength = *(_buffer+2);
    userNameLength = *(_buffer +3 + groupNameLength);
    strncpy (_groupName, (_buffer + 3), groupNameLength);
    *(_groupName + groupNameLength) ='\0';
    strncpy (_userName, (_buffer + 4 + groupNameLength), userNameLength);
    *(_userName + userNameLength) = '\0';

    return SUCCESS; 
}

int ProtocolCreateGroupReplyPack(char* _buffer, char* _ip, char* _port, int _status)
{   
    int ipLen, portLen, len;

    if(_buffer == NULL)
    {
        return FAIL;
    }
    
	ipLen = strlen(_ip);
	portLen = strlen(_port);
    len = ipLen + portLen + 4;
    *_buffer = TAG_CREAT_GROUP_REPLY;
    *(_buffer + 1) = len;
    *(_buffer + 2) = 1;
    *(_buffer + 3) = _status;
    *(_buffer + 4) = ipLen;
    strcpy((_buffer + 5),_ip);
    *(_buffer + 5 + ipLen) = portLen;
    strcpy((_buffer + 6 + ipLen),_port);
    return len + 2;
}

int ProtocolCreateGroupReplyUnPack(char* _buffer, char* _ip, char* _port, int* _status)
{
    int ipLen  = 0;
    int portLen  = 0;
    
    if (_buffer  == NULL ||_status == NULL)
    {
        return FAIL;
    }
    
    ipLen  = _buffer[4];
    portLen  = _buffer[ipLen + 5];
    strncpy( _ip,&(_buffer[5]),ipLen);
    _ip[ipLen] = '\0';
    strncpy(_port ,&(_buffer[ipLen + 6]),portLen);
    _port[portLen]  = '\0';
    *_status =_buffer[3];
    
    return SUCCESS;  
}

int ProtocolJoinGroupRequestPack(char* _buffer, char * _groupName,char* _userName)
{
    int groupNameLen = 0;
    int userNameLen = 0;
    char len = 0;
     if (_buffer  == NULL || _groupName == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    groupNameLen = strlen(_groupName);
    userNameLen = strlen(_userName);
    len = groupNameLen + userNameLen + 2;
    *_buffer = TAG_JOIN_GROUP_REQUEST;
     _buffer++;
    *_buffer =  len;
    _buffer++;
    *_buffer =  groupNameLen;
    _buffer++;
    strcpy(_buffer,_groupName);
    _buffer += groupNameLen;
    *_buffer =  userNameLen;
    _buffer ++;
    strcpy(_buffer,_userName);
    return len + 2;  
}

int ProtocolJoinGroupRequestUnPack( char* _buffer,char * _groupName,char* _userName)
{
    int len = 0;
    int groupNameLen  = 0;
    int userNameLen = 0;
    
    if (_buffer  == NULL || _groupName == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    len =  _buffer[1];
    groupNameLen  = _buffer[2];
    userNameLen = _buffer[groupNameLen + 3];
    strncpy( _groupName,&(_buffer[3]),groupNameLen);
    _groupName[groupNameLen] = '\0';
     strncpy(_userName,&(_buffer[ groupNameLen + 4]),userNameLen);
    _userName[userNameLen]  = '\0';
    return SUCCESS;  
    
}

int ProtocolJoinGroupReplyPack(char* _buffer, char* _ip, char* _port, int _status)
{
    int ipLen = strlen(_ip);
    int portLen = strlen(_port);
    int len = ipLen +  portLen + 4;
  
    if (_buffer  == NULL )
    {
        return 0;
    }
    *_buffer = TAG_JOIN_GROUP_REPLY;
    _buffer++;
    *_buffer = len;
    _buffer++;
    *_buffer = 1;
    _buffer++;
    *_buffer = _status;
    _buffer++;
    *_buffer = ipLen;
    _buffer++;
    strcpy(_buffer,_ip);
    _buffer += ipLen;
    *_buffer = portLen;
    _buffer++;
    strcpy(_buffer ,_port);

    return len + 2;
}

int ProtocolJoinGroupReplyUnPack( char* _buffer, char* _ip ,char* _port , int* _status)
{
    int ipLen  = 0;
    int portLen  = 0;
    
    if (_buffer  == NULL ||_status == NULL)
    {
        return FAIL;
    }
    
    *_status =_buffer[3];
    ipLen  = _buffer[4];
    portLen  = _buffer[ipLen + 5];
    strncpy( _ip,&(_buffer[5]),ipLen);
    _ip[ipLen] = '\0';
    strncpy(_port ,&(_buffer[ipLen + 6]),portLen);
    _port[portLen]  = '\0';
    
    return SUCCESS;  
}

int ProtocolShowAllExistingGroupsRequestPack(char* _buffer)
{
    if (_buffer == NULL)
    {
        return FAIL;
    }
    *_buffer = TAG_SHOW_ALL_EXISTING_GROUPS_REQUEST;
    return 1;
}

int ProtocolShowAllExistingGroupsReplyPack(char* _buffer, Vector* _vector)
{
    int len = 0;
    int vectorLen;
    int groupNameLen = 0;
    char* currentGroupName = NULL;
    size_t i = 0;
    if (_buffer  == NULL || _vector == NULL)
    {
        return FAIL;
    }
    vectorLen = VectorSize(_vector);
    *_buffer = TAG_SHOW_ALL_EXISTING_GROUPS_REPLY;
    _buffer +=3;
    for ( i = 0; i < vectorLen; i++)
    {
        VectorGet(_vector, i, (void*)&currentGroupName);
        groupNameLen =  strlen(currentGroupName);
        *_buffer = groupNameLen;
        len += groupNameLen;
        _buffer++;
        strcpy(_buffer, currentGroupName);
        _buffer+= (groupNameLen + 1);
    }
    
    _buffer[1] =  len;
    _buffer[2] = vectorLen;
    return len +2;
}

int ProtocolShowAllExistingGroupsReplyUnPack(char* _buffer, Vector* _vector)
{
    int len = 0;
    char* currGroup = NULL;
    int currGroupSize = 0;
    int size = 0;
    size_t i = 0;
    
     if (_buffer  == NULL || _vector == NULL)
    {
        return FAIL;
    }
    
    len = _buffer[1];
    size = _buffer[2];
    for (i = 3; i < size; i++)
    {
        
         currGroupSize = _buffer[i];
         currGroup = (char*) malloc(sizeof(char) * currGroupSize + 1);
        if (currGroup == NULL)
        {
            return FAIL;
        }
        strncpy( currGroup,&(_buffer[i + 1]),currGroupSize );
        currGroup[currGroupSize] = '\0';
        if(VectorAppend(_vector, currGroup) != VECTOR_SUCCESS)
        {
            return  FAIL;
        }
    }
    return SUCCESS; 
}

/*int ProtocolShowAllExistingGroupsRequestPack(char* _buffer)
{
    int len = 1;
    
    if (_buffer == NULL)
    {
        return FAIL;
    }
    
    *_buffer = TAG_SHOW_ALL_EXISTING_GROUPS_REQUEST;
    return len;
}

int ProtocolShowAllExistingGroupsReplyPack(char* _buffer, Vector* _vector)
{
    int len = 0;
    int vectorLen = 0;
    int groupNameLen = 0;
    char* currGroup = NULL;
    size_t i = 0, j = 3;
    
    if(_buffer  == NULL || _vector == NULL)
    {
        return FAIL;
    }
    
    vectorLen = (int)(vectorLen(_vector));
    _buffer[0] = TAG_SHOW_ALL_EXISTING_GROUPS_REPLY;
    
    for(i = 0; i < vectorLen; i++)
    {
        VectorGet(_vector, i, (void*)&currGroup);
        groupNameLen =  strlen(currGroup);
        _buffer[j] = groupNameLen;
        len += (groupNameLen + 1);
        j++;
        strcpy(&_buffer[j], currGroup);
        j += (groupNameLen + 1); /*groupNameLen*
    }
    ++len;
    _buffer[1] =  len;
    _buffer[2] = vectorLen;
    return len + 2;
}

int ProtocolShowAllExistingGroupsReplyUnPack(char* _buffer, Vector* _vector)
{
    int len = 0;
    char* currGroup = NULL;
    int currGroupLen = 0;
    int lenVec = 0;
    size_t i = 0, j = 3;
    
    if (_buffer  == NULL || _vector == NULL)
    {
        return FAIL;
    }
    
    lenVec = _buffer[2];
    for (i; i < lenVec; i++) /*i = i + currGroupLen + 1*
    {
        
        currGroupLen = _buffer[j];
        if((currGroup = (char*)malloc(sizeof(char) * currGroupLen + 1)) == NULL)
        {
            return FAIL;
        }
        strncpy(currGroup,&(_buffer[j + 1]),currGroupLen);
        currGroup[currGroupLen] = '\0';
        if(VectorAppend(_vector, currGroup) != VECTOR_SUCCESS)
        {
            return FAIL;
        }
        j = j + currGroupLen + 1;
    }
    return SUCCESS; 
}*/

int ProtocolLeaveGroupRequestPack(char* _buffer, char * _groupName,char* _userName)
{
    int groupNameLen = 0;
    int userNameLen = 0;
    int len = 0;
    
    if (_buffer  == NULL || _groupName == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    groupNameLen = strlen(_groupName);
    userNameLen = strlen(_userName);
    len = groupNameLen + userNameLen + 2;
    _buffer = _buffer;
    *_buffer = TAG_LEAVE_GROUP_REQUEST;
    _buffer++;
    *_buffer = len;
    _buffer++;
    *_buffer = groupNameLen;
    _buffer++;
    strcpy(_buffer,_groupName);
    _buffer += groupNameLen;
    *_buffer = userNameLen;
    _buffer ++;
    strcpy(_buffer,_userName);
    return len + 2;  
}

int ProtocolLeaveGroupRequestUnPack(char* _buffer,char * _groupName,char* _userName)
{
    int len = 0;
    int groupNameLen  = 0;
    int userNameLen = 0;
    
    if (_buffer  == NULL || _groupName == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    len =  _buffer[1];
    groupNameLen  = _buffer[2];
    userNameLen = _buffer[groupNameLen + 3];
    strncpy( _groupName,&(_buffer[3]),groupNameLen);
    _groupName[groupNameLen] = '\0';
     strncpy(_userName,&(_buffer[ groupNameLen + 4]),userNameLen);
    _userName[userNameLen]  = '\0';
    return SUCCESS;  
}

int ProtocolLeaveGroupReplyPack(char* _buffer, int _status)
{
    int len = 2;
    
    if (_buffer == NULL)
    {
        return FAIL;
    }
    
    *_buffer = TAG_LEAVE_GROUP_REPLY;
    _buffer++;
    *_buffer = len;
    _buffer++;
    *_buffer = 1;
    _buffer++;
    *_buffer = _status;
    return len + 2;
}

int ProtocolLeaveGroupReplyUnPack(char* _buffer, int* _status)
{
    if (_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    
    *_status =_buffer[3];
    return SUCCESS;
}

int ProtocolLogOutRequestPack(char* _buffer, char *_userName)
{
    int userNameLen = 0;
    int len = 0;
  
    if (_buffer  == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    userNameLen = strlen(_userName);
    len = userNameLen;
    *_buffer = TAG_LOG_OUT_REQUEST;
    _buffer++;
    *_buffer = len;
    _buffer++;
    strcpy(_buffer,_userName);
    return len +2;
}

int ProtocolLogOutRequestUnPack(char* _buffer, char *_userName)
{
    int len = 0;
    int userNameLen  = 0;
    
    if (_buffer == NULL || _userName == NULL)
    {
        return FAIL;
    }
    
    len =  _buffer[1];
    userNameLen = len;
    strncpy( _userName,&(_buffer[2]),userNameLen);
    _userName[userNameLen] = '\0';
    return SUCCESS;  
}

int ProtocolLogOutReplyPack(char* _buffer, int _status)
{
   
    if (_buffer == NULL)
    {
        return FAIL;
    }

    *_buffer = TAG_LOG_OUT_REPLY;
    _buffer++;
    *_buffer = 2;
    _buffer++;
    *_buffer = 1;
    _buffer++;
    *_buffer = _status;
    return 4;
}

int ProtocolLogOutReplyUnPack(char* _buffer, int* _status)
{
    if(_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    *_status =_buffer[3];
     return SUCCESS;
}

Tag_Protocol ProtocolGetTag (char* _buffer)
{
    if (_buffer == NULL)
    {
        return FAIL;
    }
    return _buffer[0];
}


