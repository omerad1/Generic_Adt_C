
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

struct hashTable_s{
    /// copy
    CopyFunction copyKey;
    CopyFunction copyValue;
    /// free
    FreeFunction freeKey;
    FreeFunction freeValue;
    /// print
    PrintFunction printKey;
    PrintFunction printValue;
    /// compare
    EqualFunction CompareKeyToPair;
    ///transforms key to number
    TransformIntoNumberFunction transformIntoNumber;

    LinkedList* table;


    int hashNumber; // number to create the hash table
};

/**
 * allocates memory for the hash table, creates an array in size @hashNumber in order to store
 * the hashtable elements, in each cell in the array there is going to be linked list to support chaining in case of
 * collision
 * @param copyKey : copy function for key element
 * @param freeKey : free function to delete the key if the creation process failed or if needed to be deleted
 * @param printKey : print function supports the key type
 * @param copyValue : copy function for value element
 * @param freeValue : free function to delete the value if the creation process failed or if needed to be deleted
 * @param printValue : print function supports the value type
 * @param equalKey : function to compare two elements represents key
 * @param transformIntoNumber : function to transform key to number in order to assign him to cell in the hash table
 * @param hashNumber : number that the hash table initialized with
 * @return : pointer to the hash table created
 */


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                          CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                          EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if      (copyKey == NULL || freeKey == NULL ||
            printKey == NULL || copyValue == NULL ||
            freeValue == NULL || printValue == NULL ||
            equalKey == NULL || transformIntoNumber == NULL){
        return NULL;}

    hashTable hash = (hashTable)malloc(sizeof(struct hashTable_s)); // allocates memory for the hash table
    if(hash == NULL){
        free(hash);
        return NULL;
    }

    hash->table = (LinkedList*)malloc(hashNumber*sizeof(LinkedList)); // creates the table for the hashtable
    if(hash->table == NULL){
        free(hash->table);
        free(hash);
        return NULL;
    }
    for(int i =0 ; i<hashNumber; i++){
        hash->table[i] =LinkedList_Create((CopyFunction) copyPair, (PrintFunction)displayPair,
                                          (FreeFunction) destroyKeyValuePair,(EqualFunction) equalKey,(EqualFunction) isEqualKey);
        if(hash->table[i] == NULL)//creation failed
            return NULL;
    }


    /// copy
    hash-> copyKey = copyKey;
    hash-> copyValue = copyValue;
    /// free
    hash-> freeKey = freeKey;
    hash-> freeValue = freeValue;
    /// print
    hash-> printKey = printKey;
    hash-> printValue = printValue;
    /// compare
    hash-> CompareKeyToPair = (EqualFunction)equalKey;
    ///transforms key to number
    hash-> transformIntoNumber = transformIntoNumber;
    hash->hashNumber=hashNumber;

    return hash;
}

/**
 * hash function that compute X % n when n is output of the transformIntoNumber function of the
 * received hashtable
 * @param hash : hash table we want to compute the place to insert inside him
 * @param key : received key of the desired element we want to insert
 * @return : the place to insert to
 */
int hashFunc(hashTable hash, Element key){
    if(hash == NULL || key == NULL){
        return -1;
    }
    int num; // where to insert the pair
    num = hash->transformIntoNumber(key); // transforms the key into number
    int k =hash->hashNumber; // the place we want to insert the new pair into the hashtable
    int place= num % k;
    return place;
}

/**
 * deletes and frees the hash table cells and then the hash table itself
 * @param hash : pointer to the hash table we want to delete
 * @return : status to inform if the deletion completed successfully
 */
status destroyHashTable(hashTable hash){
    if(hash == NULL){
        return failure;
    }
    int c = 0;
    for(int i = 0 ; i<hash->hashNumber ; i++){
       if(destroyList(hash->table[i]) == failure)
       {
           c++;
       }
    }
    free(hash->table);
    free(hash);
    if(c >0){
        return failure;
    }
    return success;
}

/**
 * first the function creates pair of type KeyValuePair of the key and value received
 * then compute the right place we want to insert the pair to in the hash table
 * finish by trying to insert him and informs the user if the addition succeed;
 * @param hash : pointer to the hash table we want to add the Key and Value to
 * @param key : element to represent the key in the pair
 * @param value : element  to represent the value in the pair
 * @return : status to inform the user if the addition of the pair completed successfully
 */
status addToHashTable(hashTable hash , Element key,Element value){
    if(hash == NULL || key == NULL || value == NULL)
        return failure;

    KeyValuePair new = createKeyValuePair(key,hash->copyValue(value),hash->copyKey,hash->copyValue,hash->printKey,hash->printValue,
                                          hash->freeKey,hash->freeValue,hash->CompareKeyToPair); // creates a new pair of key and value

    if(new == NULL) // creation on keyvaluepair failed
        return failure;

    int place = hashFunc(hash,key);
    if(place == -1){
        return failure;
    }

    LinkedListResult res = appendNode(hash->table[place],new);
    if(res != LINKEDLIST_BAD_ARGUMENT){ // the addition succeed
    return success;
    }

    return failure; // addition failed

}

/**
 * the function using the hashFunc in order to find the currect place in the table to looking for the key
 * then use searchByKeyInList to find item in the list with the same key as given key
 * @param hash : pointer to the hash table we want to search inside
 * @param key : element represents key we want to look for
 * @return : the value that mapped to the key in the pair if found or NULL if not found
 */
Element lookupInHashTable(hashTable hash, Element key){
    if(hash == NULL || key == NULL){
        return NULL;
    }

    int place = hashFunc(hash,key); // the place to look up his list

    if(place == -1){
        return NULL;
    }

    KeyValuePair te = searchByKeyInList(hash->table[place], key);// the result of the search
    if(te == NULL){
        return NULL;
    }

    return getValue(te);

}

/**
 * the function searches by the received key in the correct place of the hash table
 * when found uses the function deleteNode to remove the element from the hash table
 * @param hash : pointer to the hash table we want to remove from
 * @param key : the element represents key in the pair we want to delete
 * @return : status to inform the user if the deletion created successfully
 */
status removeFromHashTable(hashTable hash, Element key){
    if(hash == NULL || key == NULL)
        return failure;

    int place = hashFunc(hash,key); // the place to remove from
    if(place == -1){
        return failure;
    }

    KeyValuePair te = searchByKeyInList(hash->table[place],key);// the result of the search
    if(te == NULL){
        return failure;
    }
    return deleteNode(hash->table[place],te); // return the status from the deleteNode function

}
/**
 * iterate over the hash linekd lists and display each list using displayList Function
 * @param hash : pointer to the hash table we want to display
 * @return : status to inform if the display succeed;
 */
status displayHashElements(hashTable hash){
    if(hash == NULL)
        return failure;

    for(int i = 0 ; i <hash->hashNumber ; i++){ // iterate over the hash linked lists
        if(displayList(hash->table[i]) != success){
            return failure;
        }
    }
    return success;

}