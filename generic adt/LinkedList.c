#include "LinkedList.h"


/** Node structure.
 * the node have pointer to next node and stores data
 */
typedef struct Node_t* Node;
struct Node_t{
    Node next ; // pointer to next node
    Element data ; // the data the node stores - any data can be stored in this node

};

/** Linked List structure.
 * @head : pointer to the Node placed in the head of the linked list
 * @tail : pointer to the Node placed in the end of the linked list
 */
struct LinkedList_t{
    Node head;  // pointer to the head of the list
    Node tail; // pointer to the end of the list
    int size; // the amount of elements currently in the list
    CopyFunction copyFunction;
    PrintFunction printFunction;
    FreeFunction  freeFunction;
    EqualFunction equalFunction;
    EqualFunction insideEqualFunction;
};

/**
 * create and allocates new linked list
 * @param copyFunction : copy function
 * @param freeFunction : free function to delete the list if the creation process failed
 * @param printFunction : print function to print the list elements
 * @param equalFunction : function to compare 2 elements in the linked list
 * @param insideEqualFunction: function to compare half of the object or the whole object by user request
 * @return pointer to the new linked list created
 */
LinkedList LinkedList_Create(CopyFunction copyFunction ,PrintFunction printFunction, FreeFunction freeFunction
        ,EqualFunction equalFunction,EqualFunction insideEqualFunction){
    if (copyFunction == NULL || freeFunction == NULL || printFunction == NULL ||equalFunction == NULL){
        return NULL;
    }
    LinkedList linkedList = (LinkedList)malloc(sizeof(struct LinkedList_t)); // allocates memory for the list
    if(linkedList == NULL){
        return NULL;
    }

    linkedList->size = 0;
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->freeFunction = freeFunction; // free function
    linkedList->printFunction = printFunction;// print function
    linkedList->copyFunction = copyFunction;// copy function
    linkedList->equalFunction = equalFunction; // equal function
    linkedList->insideEqualFunction = insideEqualFunction; // inside equal function
    return linkedList;
}


/**
 * add new node to the end of the list.
 * first the function checks if the list is empty, if yes she will set tail and head pointers to point to the new element
 * if not the node that is in the tail right now will point to the new node as his next and the tail pointer will point
 * at new
 * @param l_list : pointer to the linked list we want to add the node to
 * @param element : element we want to store at the list
 * @return : status to inform the user
 */
LinkedListResult appendNode(LinkedList l_list, Element element){
    if(l_list == NULL || element == NULL){
        return LINKEDLIST_BAD_ARGUMENT;
    }
    Node new=(Node)malloc(sizeof(struct Node_t)); // allocates memory for the new node

    if(new == NULL){ // memory failure
        return LINKEDLIST_FAILURE;
    }

    new->next = NULL;
    new->data = l_list->copyFunction(element);
    if(l_list->size == 0){ // list is empty

        l_list->head = new; // points to new
    }
    else{ // list is not empty

        l_list->tail->next = new; //set the last node to point to the new node
    }
    l_list->tail=new; //set the tail pointer to point new
    l_list->size++; // increase the size by 1

    return LINKEDLIST_SUCCESS;
}

/**
 * the function first validates that the list isn't empty, then on loop over the list, using the compare function
 * of the linked list the function checks if the element received is in the linked list, if there is she will delete him
 * the function also checks that the element is or is not the head or the tail of the list and set head/tail to ponint the
 * right values.
 * @param l_list : pointer to the linked lst we want to delete the element from
 * @param element : the element we want to delete
 * @return : status of success if the deletion happened and failed if not.
 */
status deleteNode(LinkedList l_list, Element element) {
    if (l_list == NULL || element == NULL) {
        return failure;
    }
    if (l_list->size == 0) {
        return failure;
    }

    if (l_list->equalFunction(l_list->head->data, element)) { // the node is the head of the linked list
        Node temp = l_list->head;
        l_list->head = l_list->head->next;
        l_list->size--;
        if (l_list->freeFunction(temp->data) == failure) { // deletes the node and checks there is no memory problem
            free(temp);
            return failure;
        }
        free(temp);
        return success;
    }
    else { //search for the node we want to delete
        Node dummy = l_list->head;
        while(dummy->next != NULL){

            if(l_list->equalFunction(dummy->next->data,element)){
                Node temp = dummy->next;

                if(l_list->tail == temp) // check if the tail points to the node we want to delete
                    l_list->tail=dummy;

                dummy->next = dummy->next->next;
                l_list->freeFunction(temp->data);
                free(temp);
                l_list->size--;

                return success;
            }

            dummy = dummy->next;
        }
    }
        return failure;
}

/**
 * the function loop over the elements in the linked list and use the free function in order to handle the
 * memory needed to be freed. at the end the function frees the memory of the list itself.
 * @param l_list : pointer to linked list which we want to destroy
 * @return : status to inform if the deletion completed successfully
 */
status destroyList(LinkedList l_list){
    if(l_list == NULL){
        return failure;
    }
    int c = 0; // this counter will check if some element in the linked list failed to be freed, the use in counter
    // is from the need to free all the other elements before returning failure status
    Node dummy = l_list->head;
    Node temp;
    while(dummy != NULL){
        temp = dummy;
        dummy = dummy->next;
        if(l_list->freeFunction(temp->data) != success){ // deletion failed
            free(temp);
            c++;
        }
        else{
            free(temp);
        }
    }
    if(l_list != NULL){
        free(l_list);}
    if(c >0)
        return failure;
    return success;
}

/**
 * iterate over the linked list nodes and print each node value from the beginning to the end of the list
 * @param l_list : pointer to the linked list we want to print her values
 */
status displayList(LinkedList l_list){
    if(l_list == NULL){
        return failure;
    }
    if(l_list->size == 0){
        return success;
    }
    Node dummy = l_list->head;
    while(dummy != NULL){
        l_list->printFunction(dummy->data);
        dummy=dummy->next;
    }
    return success;
}
/**
 * first, the function checks the validation of the index (not out of bounds),
 * and then iterates the linked list until arriving to the desired index, then return the value in that index
 * @param l_list : pointer to the linked list
 * @param index : the index we want to return value from
 * @return : element in the received index of the linked list
 */
Element getDataByIndex(LinkedList l_list , int index) {
    if (l_list == NULL) {
        return NULL;
    }
    if (index > l_list->size || index < 0) { // invalid index
        return NULL;
    }
    Node dummy = l_list->head;
    for (int i = 0; i < index; i++) {
        dummy = dummy->next;
    }
    if (dummy!= NULL) {
        return l_list->copyFunction(dummy->data);
    }
    return NULL;
}
/**
 * returns the size of the linked list
 * @param l_list : the linked list we want to get size of
 * @return : number of elements in the linked list
 */
int getLengthList(LinkedList l_list){
    if(l_list == NULL){
        return 0;
    }
    return l_list->size;
}
/***
 * search in the linked list for element that contains the received element inside him using equal function made for the
 * specific element
 * @param l_list : pointer to the linked list
 * @param element : part of bigger element we want to look for
 * @param insideEqualFunction : function received from the user to compare element from the linked list with his part
 * received
 * @return : element that contains the received element if found, null if didnt found
 */
Element searchByKeyInList(LinkedList l_list , Element element ){
    if(element == NULL || l_list == NULL){
        return NULL;
    }
    Node dummy = l_list->head;
    for(int i=0 ; i<l_list->size; i++){
        if(l_list->insideEqualFunction(dummy->data,element)){
            return l_list->copyFunction(dummy->data);
        }
        dummy = dummy->next;
    }
    return NULL;


}
/**
 * shallow copy linked list
 * @param l_list : the linked list we want to copy
 * @return : pointer to the linked list
 */
LinkedList copyLinkedList(LinkedList l_list){
    if(l_list == NULL){
        return NULL;
    }
    return l_list;
}