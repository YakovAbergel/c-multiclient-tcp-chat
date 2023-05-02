#ifndef __SERVERTCP_H__
#define __SERVERTCP_H__
#include <stddef.h> /*size_t*/

#define MIN_NUM_OF_PORT 1025
#define MAX_NUM_OF_PORT 64000
#define MAX_NUM_OF_CLIENT 1024

typedef struct Server Server;

typedef enum Server_Result {
	SERVER_SUCCESS = 0, 
	SERVER_SOCKET_ERROR, 			
	SERVER_REUSE_ERROR,		
	SERVER_BIND_ERROR, 		
	SERVER_LISTEN_ERROR,
	SERVER_SELECT_ERROR,
	SERVER_LIST_SIZE_ERROR, 
	SERVER_ACCEPT_ERROR, 
	SERVER_LIST_ITR_ERROR, 
	SERVER_POINTER_NOT_INITIALIZED_ERROR, 
	SERVER_CONNECTION_IS_CLOSED_SUCCESS, 
	SERVER_RECIEVED_ERROR,  
	SERVER_SEND_ERROR,
	SERVER_UNINITIALIZED_ERROR,
	SERVER_STOP_RUN, 
	SERVER_ALLOCATION_FAILED,
	SERVER_LIST_PUSH_ERROER,
	SERVER_INPUT_ERROR
} Server_Result;

typedef int (*NewClient)(const int _sock);
typedef int (*CloseClient)(const int _sock);
typedef int (*GotMessage)(int _clientSock, void *_msg, size_t _msgSize, void *_appServer);
typedef int (*Fail)(Server_Result _nameOfErr);

/**  
 * @brief initialization a new server.  
 * @return success or error code 
 * @retval SERVER_SUCCESS  on success
 * @retval SERVER_POINTER_NOT_INITIALIZED_ERROR  error, _listeningSock not initilized
 * @retval SERVER_SOCKET_ERROR error, if func socket failed 
 * @retval SERVER_NO_BLOCKING_ERROR error, if func NoBlocking failed 
 * @retval SERVER_BIND_ERROR error, if func bind failed
 * @retval SERVER_LISTEN_ERROR error, if func listen failed
 */
Server* InitServer(size_t _port, size_t _sizeBacklog, size_t _maxNumOfClient,
 					NewClient _newClient, CloseClient _closeClient, GotMessage _gotMsg, Fail _fail, void* _appServer);



/**  
 * @brief Checking if there is a new client, if so we will add it to the list if possible.  
 * @param[in] _list - The list that the new clients will enter
 * @param[in] _listeningSock - The sock we received from the InitServer function 
 * @return success or error code 
 * @retval SERVER_SUCCESS  on success
 * @retval LIST_UNINITIALIZED_ERROR  error, if _list not initilized
 * @retval SERVER_SOCKET_ERROR error, if _listeningSock < 0
 * @retval SERVER_LIST_SIZE_ERROR error, if ListSize(_list) == NUM_OF_CLIENT 
 * @retval SERVER_NO_BLOCKING_ERROR error, if func NoBlocking failed 
 * @retval SERVER_CLIENT_ACCEPT_ERROR error, if func accept failed
 * @retval SERVER_NO_BLOCKING_SUCCESS error, If we are in real no_blocking
 */
Server_Result RanServer(Server* _server);


/**  
 * @brief Go through the list of clients and check if they have sent information to the server and if so send them a reply back.  
 * @param[in] _list - The list of clients
 * @param[in] _data - The data we want the server to transfer to the client 
 * @return success or error code 
 * @retval SERVER_SUCCESS  on success
 * @retval LIST_UNINITIALIZED_ERROR  error, if _list not initilized
 * @retval SERVER_POINTER_NOT_INITIALIZED_ERROR error, if _listeningSock not initilized
 * @retval SERVER_LIST_ITR_ERROR error, if ListItrBegin(_list) or ListItrEnd(_list) = NULL
 */
Server_Result ServerSendMsg(int _clientSock, void* _data, int _sizeData);

size_t StopRun(Server* _server);


#endif /* __SERVERTCP_H__ */
