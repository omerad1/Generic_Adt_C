all: JerryBoree
JerryBoree: JerryBoreeMain.o Jerry.o HashTable.o LinkedList.o KeyValuePair.o MultiValueHashTable.o
	gcc JerryBoreeMain.o Jerry.o HashTable.o LinkedList.o KeyValuePair.o MultiValueHashTable.o -o JerryBoree


Jerry.o:Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
	
KeyValuePair.o:LinkedList.c LinkedList.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o:LinkedList.h 
	gcc -c LinkedList.c

HashTable.o:HashTable.c HashTable.h Defs.h KeyValuePair.c KeyValuePair.h LinkedList.c LinkedList.h
	gcc -c HashTable.c

MultiValueHashTable.o:MultiValueHashTable.c MultiValueHashTable.h HashTable.c HashTable.h Defs.h KeyValuePair.c KeyValuePair.h LinkedList.c LinkedList.h
	gcc -c MultiValueHashTable.c
	
JerryBoreeMain.o: JerryBoreeMain.c MultiValueHashTable.c MultiValueHashTable.h HashTable.c HashTable.h Defs.h KeyValuePair.c KeyValuePair.h LinkedList.c LinkedList.h Jerry.h
	gcc -c JerryBoreeMain.c

clean :
	rm -f *.o
