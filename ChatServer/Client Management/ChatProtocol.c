#include "ChatProtocol.h"
#include <string.h>

int ProtocolRequestSendMsg (char*_buffer, char* _userName, char* _message)
{
    int userNameLength, messageLength; 
    if (_buffer == NULL || _userName == NULL || _message == NULL)
    {
        return FAIL;
    }
    userNameLength = strlen (_userName);
    messageLength = strlen (_message);
    if (userNameLength > MAX_NAME_LENGTH || messageLength > MAX_MASSAGE_LENGTH)
    {
        return FAIL;
    }
    *_buffer = TAG_SEND_MSG_REQUEST;
    *(_buffer + 1) = userNameLength;
    strcpy ((_buffer + 2), _userName);
    *(_buffer + 2 + userNameLength) = messageLength;
    strcpy ((_buffer + 3 + userNameLength), _message);
    return (3 + userNameLength + messageLength);
}

int ProtocolReplySendMsg (char*_buffer, int* _status)
{
    int userNameLength, messageLength; 
    if (_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    *_buffer = TAG_SEND_MSG_REPLY;
    *_status = SUCCESS;
    return SUCCESS;
}

int ProtocolRequestReciveMsg (char*_buffer, char* _userName, char* _message)
{
    int userNameLength, messageLength; 
    if (_buffer == NULL || _userName == NULL || _message == NULL)
    {
        return FAIL;
    }
    userNameLength = *(_buffer + 1);
    messageLength = *(_buffer + 2 + userNameLength);
    strncpy (_userName, (_buffer + 2), userNameLength);
    _userName [userNameLength] = '\0';
    strncpy (_message, (_buffer + 3 + userNameLength), messageLength);
    _message [messageLength] = '\0';
    *_buffer = TAG_RECIEVE_MSG_REQUEST;
    return (3 + userNameLength + messageLength);
}

int ProtocolReplyReciveMsg (char*_buffer, int* _status)
{
    int userNameLength, messageLength; 
    if (_buffer == NULL || _status == NULL)
    {
        return FAIL;
    }
    *_status = SUCCESS;
    *_buffer = TAG_RECIEVE_MSG_REPLY;
    return SUCCESS;
}

Tag_Chat GetTag (char* _buffer)
{
    if (_buffer == NULL)
    {
        return FAIL;
    }
    return _buffer[0];
}
