
#makefile ClientManagement

TARGET = clientMan.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = clientManagement.o testClientManagement.o clientNet.o protocol.o UI.o ChatOpen.o

CLIENT_NET_PASS = ../ClientNetGen/
PROTOCOL_PASS = ../Protocol/
LIST_PASS = ../../GenericDataStructures+DynamicLibrary/
GEN_LIB_PASS = ../../GenericDataStructures+DynamicLibrary/DaynamicLib/

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(GEN_LIB_PASS)libGen.so

testClientManagement.o:testClientManagement.c clientManagment.h 
	$(CC) $(CFLAGS) -c testClientManagement.c 

clientManagement.o:clientManagement.c clientManagment.h $(CLIENT_NET_PASS)clientNet.h $(PROTOCOL_PASS)protocol.h $(LIST_PASS)ListGen/listGen.h $(LIST_PASS)ListItr/listItr.h 
	$(CC) $(CFLAGS) -c clientManagement.c 

clientNet.o:$(CLIENT_NET_PASS)clientNet.c $(CLIENT_NET_PASS)clientNet.h 
	$(CC) $(CFLAGS) -c $(CLIENT_NET_PASS)clientNet.c 

protocol.o:$(PROTOCOL_PASS)protocol.c $(PROTOCOL_PASS)protocol.h 
	$(CC) $(CFLAGS) -c $(PROTOCOL_PASS)protocol.c
	
UI.o:UI.c UI.h 
	$(CC) $(CFLAGS) -c UI.c
	
ChatOpen.o:ChatOpen.c ChatOpen.h 
	$(CC) $(CFLAGS) -c ChatOpen.c 
valgrind:
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes -s ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) 
