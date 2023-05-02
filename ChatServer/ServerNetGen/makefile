#makefile ServerNetGen

TARGET = server.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = serverNetGen.o mainServerNetGen.o

LIST_PASS =~/Desktop/C/GenericDataStructures+DynamicLibrary/
GEN_LIB_PASS = ~/Desktop/C/GenericDataStructures+DynamicLibrary/DaynamicLib/

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(GEN_LIB_PASS)libGen.so

mainServerNetGen.o:mainServerNetGen.c serverNetGen.h $(LIST_PASS)ListGen/listGen.h $(LIST_PASS)ListItr/listItr.h 
	$(CC) $(CFLAGS) -c mainServerNetGen.c 

serverNetGen.o:serverNetGen.c $(LIST_PASS)ListGen/listGen.h $(LIST_PASS)ListItr/listItr.h 
	$(CC) $(CFLAGS) -c serverNetGen.c 

valgrind:
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes -s ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) 
