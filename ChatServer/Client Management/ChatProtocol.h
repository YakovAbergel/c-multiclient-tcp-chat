#ifndef __CHAT_PROTOCOL_H__
#define __CHAT_PROTOCOL_H__

#define FAIL 0
#define SUCCESS 1
#define MAX_NAME_LENGTH 20
#define MAX_MASSAGE_LENGTH 233 /*256 - name length - 3*/

typedef enum Tag_Chat
{
    TAG_SEND_MSG_REQUEST = 1,
    TAG_SEND_MSG_REPLY,
    TAG_RECIEVE_MSG_REQUEST,
    TAG_RECIEVE_MSG_REPLY
}Tag_Chat;

int ProtocolRequestSendMsg (char*_buffer, char* _userName, char* _message);
int ProtocolReplySendMsg (char*_buffer, int* _status);
int ProtocolRequestReciveMsg (char*_buffer, char* _userName, char* _message);
int ProtocolReplyReciveMsg (char*_buffer, int* _status);
Tag_Chat GetTag (char* _buffer);

#endif /*_CHAT_PROTOCL__*/
