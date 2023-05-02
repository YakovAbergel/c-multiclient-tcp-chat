#ifndef __GROUPMANAGEMENT_H__
#define __GROUPMANAGEMENT_H__

#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 

typedef struct GroupAddress GroupAddress;
typedef struct GroupMan GroupMan;
typedef enum GroupMan_result
{
	GROUP_MAN_SUCCESS,
	GROUP_MAN_GROUP_ALREADY_EXISTS,
	GROUP_MAN_GROUP_DOESNT_EXISTS,
	GROUP_MAN_ADDR_FAIL,
	GROUP_MAN_ALLOC_FAIL,
	GROUP_MAN_GROUP_ALLOC_FAIL,
	GROUP_MAN_GROUP_ADDR_ALLOC_FAIL,
	GROUP_MAN_BUF_NOT_INITIAILIZED,
	GROUP_MAN_QUEUE_INSERT_ERROR
	
}GroupMan_result;

GroupMan *GroupManCreate();

void GroupManDestroy(GroupMan **_gManager);

GroupMan_result GroupManCreateGroup(GroupMan *_groups, char *_groupName, char* _groupAddrIP);

GroupMan_result GroupManAddUser(GroupMan *_groups, char *_groupName, char* _groupAddrIP);

GroupMan_result GroupManRemoveUser(GroupMan *_groups, char *_groupName);

Vector* GroupManGetAllActiveGroups(GroupMan* _groups);

#endif /*__GROUPMANAGEMENT__H__*/
