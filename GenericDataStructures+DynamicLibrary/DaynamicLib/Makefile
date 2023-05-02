#makefile GenLib

TARGET = libGen.so

COMMAND = gcc

FLAGS= -g -ansi -pedantic -c -fPIC 

OBJS = vectorGen.o QueueGen.o listGen.o listItr.o listFunc.o heapGen.o hashMap.o

PASS = ~/Desktop/C/Generic/
 
$(TARGET): $(OBJS)
	$(COMMAND) -shared -o $(TARGET) $(OBJS) -lm
	
	
vectorGen.o: $(PASS)VectorGen/vectorGen.c $(PASS)VectorGen/vectorGen.h
	$(COMMAND)  $(FLAGS) $(PASS)VectorGen/vectorGen.c
	
QueueGen.o: $(PASS)QueueGen/QueueGen.c $(PASS)QueueGen/QueueGen.h
	$(COMMAND)  $(FLAGS) $(PASS)QueueGen/QueueGen.c
	
heapGen.o: $(PASS)HeapGen/heapGen.c $(PASS)HeapGen/heapGen.h $(PASS)VectorGen/vectorGen.h
	$(COMMAND)  $(FLAGS) $(PASS)HeapGen/heapGen.c
	
listGen.o: $(PASS)ListGen/listGen.c $(PASS)ListGen/listGen.h $(PASS)ListGen/listInternal.h
	$(COMMAND)  $(FLAGS) $(PASS)ListGen/listGen.c
	
listItr.o: $(PASS)ListGen/listGen.h $(PASS)ListGen/listInternal.h $(PASS)ListItr/listItr.c $(PASS)ListItr/listItr.h 
	$(COMMAND)  $(FLAGS) $(PASS)ListItr/listItr.c
	
listFunc.o: $(PASS)ListFunc/listFunc.c $(PASS)ListFunc/listFunc.h $(PASS)ListItr/listItr.h
	$(COMMAND)  $(FLAGS) $(PASS)ListFunc/listFunc.c
	
hashMap.o: $(PASS)HashMapGen/hashMap.c $(PASS)HashMapGen/hashMap.h $(PASS)ListGen/listGen.h $(PASS)ListItr/listItr.h $(PASS)ListFunc/listFunc.h
	$(COMMAND)  $(FLAGS) $(PASS)HashMapGen/hashMap.c -lm
	
	
valgrind:
	valgrind --log-file=valgrind.log --leak-check=full --track-origins=yes -s ./$(TARGET)
clean:
	rm -f $(TARGET) &(OBJS)

