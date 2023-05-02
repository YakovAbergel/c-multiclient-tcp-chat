#ifndef __UI_H__
#define __UI_H__
#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 

void UI_OpeningScreen(char* _name, char* _password, int* _status);
void UI_ScreenAfterLogin(char* _groupName, int* _status);
void UI_ShowAllExistingGroups(Vector* _vec, int* _index);





#endif /* __UI_H__ */
