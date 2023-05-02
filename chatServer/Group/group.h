#ifndef __GROUP_H__
#define __GROUP_H__

typedef struct Group Group;

Group *GroupCreate(char *_name, void *_address);

void GroupDestroy(Group **_group);

int GroupIsEqual(Group *_group1, Group *_group2);

void UserAddedToGroup(Group *_group);

int RemovingUserFromGroup(Group *_group);

char *GetGroupName(Group *_group);

void *GetGroupAddress(Group *_group);

size_t GetNumOfUsersInGroup(Group *_group);

#endif /*__GROUP_H__*/
