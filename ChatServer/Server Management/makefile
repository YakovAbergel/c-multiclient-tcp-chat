#makefile ServerManagement

TARGET = serverMan.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = serverManagement.o testServerMan.o serverNetGen.o protocol.o user.o userManagment.o group.o groupManagement.o

SERVER_NET_PASS = ../ServerNetGen/
PROTOCOL_PASS = ../Protocol/
USER_PASS = ../User/
GROUP_PASS = ../Group/
GenericDataStructures+DynamicLibrary_PASS = ../../GenericDataStructures+DynamicLibrary/
GEN_LIB_PASS = ../../GenericDataStructures+DynamicLibrary/DaynamicLib/

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(GEN_LIB_PASS)libGen.so

testServerMan.o:testServerMan.c serverManagement.h 
	$(CC) $(CFLAGS) -c testServerMan.c 

serverManagement.o:serverManagement.c serverManagement.h $(SERVER_NET_PASS)serverNetGen.h $(PROTOCOL_PASS)protocol.h 
	$(CC) $(CFLAGS) -c serverManagement.c 

serverNetGen.o:$(SERVER_NET_PASS)serverNetGen.c $(SERVER_NET_PASS)serverNetGen.h $(GenericDataStructures+DynamicLibrary_PASS)ListGen/listGen.h $(GenericDataStructures+DynamicLibrary_PASS)ListItr/listItr.h 
	$(CC) $(CFLAGS) -c $(SERVER_NET_PASS)serverNetGen.c 

protocol.o:$(PROTOCOL_PASS)protocol.c $(PROTOCOL_PASS)protocol.h 
	$(CC) $(CFLAGS) -c $(PROTOCOL_PASS)protocol.c
	
user.o:$(USER_PASS)user.c $(USER_PASS)user.h $(GenericDataStructures+DynamicLibrary_PASS)ListGen/listGen.h $(GenericDataStructures+DynamicLibrary_PASS)ListItr/listItr.h $(GenericDataStructures+DynamicLibrary_PASS)ListFunc/listFunc.h
	$(CC) $(CFLAGS) -c $(USER_PASS)user.c 
	
userManagment.o:$(USER_PASS)userManagment.c $(USER_PASS)userManagment.h $(USER_PASS)user.h $(GenericDataStructures+DynamicLibrary_PASS)HashMapGen/hashMap.h
	$(CC) $(CFLAGS) -c $(USER_PASS)userManagment.c
	
group.o:$(GROUP_PASS)group.c $(GROUP_PASS)group.h
	$(CC) $(CFLAGS) -c $(GROUP_PASS)group.c 
	
groupManagement.o:$(GROUP_PASS)groupManagement.c $(GROUP_PASS)groupManagement.h $(GROUP_PASS)group.h $(GenericDataStructures+DynamicLibrary_PASS)HashMapGen/hashMap.h $(GenericDataStructures+DynamicLibrary_PASS)VectorGen/vectorGen.h $(GenericDataStructures+DynamicLibrary_PASS)QueueGen/QueueGen.h
	$(CC) $(CFLAGS) -c $(GROUP_PASS)groupManagement.c 
	
valgrind:
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes -s ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) 
