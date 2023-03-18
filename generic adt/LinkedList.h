
#ifndef HW3_LINKEDLIST_H
#define HW3_LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"


/** Linked list structure */
typedef struct LinkedList_t* LinkedList;

/** possible return values to allow the user handel situations */
typedef enum {
    LINKEDLIST_SUCCESS, LINKEDLIST_BAD_ARGUMENT,LINKEDLIST_FAILURE
}LinkedListResult;

/**
 * * create and allocates new linked list
 * @param copyFunction : copy function
 * @param freeFunction : free function to delete the list if the creation process failed or if needed to be deleted
 * @param printFunction : print function to print the list elements
 * @param equalFunction : function to compare 2 elements in the linked list
 * @return pointer to the new linked list created
 */
LinkedList LinkedList_Create(CopyFunction copyFunction ,PrintFunction printFunction, FreeFunction freeFunction
                           ,EqualFunction equalFunction,EqualFunction insideEqualFunction);


 /**
  * destroy, receives linked list we want to destroy and the function will delete the linked list
  * and take care of the memory needed to be freed
  * @param l_list : pointer to linked list which we want to destroy
  * @return : status to inform if the deletion completed successfully
  */
 status destroyList(LinkedList l_list );


/**
 * appends node to the received linked list
 * @param l_list : pointer to linked list we want to add node to her
 * @param element : element we want to add
 * @return : linked list result for the user to inform him if the action succeed
 */
LinkedListResult appendNode(LinkedList l_list, Element element);


/**
 * deletes node from the received linked list and free his memory
 * @param l_list : pointer to linked list we want to delete the node from
 * @param element : the element we want to delete
 * @return : status that tell us i the node is in the list or not or if the action succeeded
 */
status deleteNode(LinkedList l_list, Element element);

/**
 * prints the linked list values from the first to the last using the print function of the linked list
 * @param l_list : pointer to linked list we want to print her values
 */
status displayList(LinkedList l_list );

/**
 * returns the value of the node that is in the linked list in the place of the index
 * @param l_list : pointer to linked list which we want to return the value from
 * @param index : the index the node that holds the value is at
 * @return the function will return the value store in the index / null if the index is invalid
 */
Element getDataByIndex(LinkedList l_list , int index);

/**
 * returns the number of the elements in the linked list
 * @param l_list : pointer to linked list which we want to count her elements
 * @return number of elements in the list
 */
int getLengthList(LinkedList l_list);


/**
 * the function checks if there is node that contains the element received
 * @param l_list : pointer to linked list
 * @param element : pointer to information that is part of elements stored in the list.
 * @return the element we looked for(if there is more then one, the first one we found will be returned),
 * if we didnt find element that contains the received element we will return null
 */
Element searchByKeyInList(LinkedList l_list , Element element);


/**
 * shallow copy linked list
 * @param l_list : the linked list we want to copy
 * @return : pointer to the linked list
 */
LinkedList copyLinkedList(LinkedList l_list);



#endif //HW3_LINKEDLIST_H
