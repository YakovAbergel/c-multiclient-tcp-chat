#include <stdio.h> /*print, scan*/ 
#include "UI.h"
#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 

static int PrintVec(void* _element, size_t _index, void* _context);

void UI_OpeningScreen(char* _userName, char* _password, int* _status)
{
	int status = 0;
	printf("\n===========================Welcome to the chat server===========================\n");
	printf("\nPlease choose one of the options from the menu!\n");
	printf("\n(1) To register for the server\n(2) To connect to the server\n(3) To exit the server\n");
	scanf("%d",_status);
	if(*_status >= 1 && *_status <= 3)
	{
		if(*_status != 3)
		{
			printf ("please insert user name\n");
			scanf("%s",_userName);
			getchar();
			printf ("please insert password\n");
			scanf("%s",_password);
		}
	}
	else
	{
		*_status = 0;
	}
	printf("\n================================================================================\n");
}

void UI_ScreenAfterLogin(char* _groupName, int* _status)
{
    printf("\nPlease choose one of the options from the menu!\n");
	printf("\n(1) To create a new group\n(2) To join the group\n(3) To leave a group\n(4) To log out of the server\n");
	scanf("%d",_status);
	if(*_status >= 1 && *_status <= 4)
	{
		if(*_status != 4 && *_status != 3)
		{
			printf ("please insert group name\n");
			scanf("%s",_groupName);
		}
	}
	else
	{
		*_status = 0;
	}
	printf("\n================================================================================\n");
}

void UI_ShowAllExistingGroups(Vector* _vec, int* _index)
{
    size_t i;

    if(_vec == NULL)
    {
        return;
    }
	
    printf("\n\nThis is the list of active groups\n\n");
    VectorForEach(_vec, PrintVec, NULL);
    printf("\nSelect a group number that you would like to join\n");
    scanf("%d",_index);
    printf("index = %d\n", *_index);
}

static int PrintVec(void* _element, size_t _index, void* _context)
{
	if(_context == NULL)
	{
		printf("(%ld: %s)   ",_index+1, ((char*)_element));
		return 1;
	}
}
