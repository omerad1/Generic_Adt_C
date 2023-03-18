//
// Created by omer on 12/20/22.
//
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"
struct MuliValueHashTable_t{
    hashTable hash_table;

    int hashNumber;
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
    EqualFunction equalKey;
    ///transforms key to number
    TransformIntoNumberFunction transformIntoNumber;

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
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                              CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                              EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber,
                                              int hashNumber ){

    if      (copyKey == NULL || freeKey == NULL ||
             printKey == NULL || copyValue == NULL ||
             freeValue == NULL || printValue == NULL ||
             equalKey == NULL || transformIntoNumber == NULL){
        return NULL;}


    MultiValueHashTable mv_hashtable = (MultiValueHashTable)malloc(sizeof(struct MuliValueHashTable_t)); // allocates memory for the hash table
    if(mv_hashtable == NULL){
        return NULL;
    }

    mv_hashtable->hash_table = createHashTable(copyKey, freeKey, printKey, (CopyFunction) copyLinkedList,
                                               (FreeFunction) destroyList, (PrintFunction) displayList, equalKey,
                                               transformIntoNumber, hashNumber ); // hash table for the MultiValueHashTable
    if(mv_hashtable->hash_table == NULL){ // creation failed
        return NULL;
    }


    /// copy
    mv_hashtable-> copyKey = copyKey;
    mv_hashtable-> copyValue = copyValue;
    /// free
    mv_hashtable-> freeKey = freeKey;
    mv_hashtable-> freeValue = freeValue;
    /// print
    mv_hashtable-> printKey = printKey;
    mv_hashtable-> printValue = printValue;
    /// compare
    mv_hashtable-> equalKey = equalKey;
    ///transforms key to number
    mv_hashtable->transformIntoNumber = transformIntoNumber;

    mv_hashtable->hashNumber=hashNumber;

    return mv_hashtable;
}

/**
 * deletes and frees the hash table cells and then the hash table itself
 * @param hash : pointer to the hash table we want to delete
 * @return : status to inform if the deletion completed successfully
 */
status destroyMultiValueHashTable(MultiValueHashTable mv_hash){
    if(mv_hash == NULL){
        return failure;
    }
    status res;
    res = destroyHashTable(mv_hash->hash_table); // keep the result of the hash_table deletion
    free(mv_hash);
    return res;
}



/**
 * function add to the hash table mapping between the value and the key, if the key already exists in the hash table
 * she will add the value to the other values share the same key.
 * @param mv_hash : MultiValueHashTable to add the value to based on the mapping of received key
 * @param key : element represents key to map the value to the hash table
 * @param value : value to add to the hash table
 * @return : status to inform if the insertion completed successfully
 */
status addToMultiValueHashTable(MultiValueHashTable mv_hash,Element key,Element value) {
    if(mv_hash == NULL || key == NULL || value == NULL)
        return failure;


    status s;

    // will check if there is value from type linked list
    // already in the hash table that shares the same key as received value
    LinkedList check = lookupInHashTable(mv_hash->hash_table,key);

    /// add to existing linked list in the hashtable
    if (check != NULL) // there is value with this key already - we want to insert this linked list the value
    {
        LinkedListResult ls = appendNode(check, value); // add the value to the desired linked list
        if (ls == LINKEDLIST_SUCCESS) {
            s = success;
        } else {
            s = failure;
        }
    }
    else {
        LinkedList All_Values = LinkedList_Create(mv_hash->copyValue,
                                                  mv_hash->printValue,// linked list store the values
                                                  mv_hash->freeValue, mv_hash->equalKey,(EqualFunction) isEqualKey);
        if(All_Values == NULL){ // creation failed
            return failure;
        }
        LinkedListResult ls = appendNode(All_Values, value); // add the new value to the linked list
        if (ls != LINKEDLIST_SUCCESS) {
            return failure;
        }

        /// adding the pair to the hashtable
        s = addToHashTable(mv_hash->hash_table, key, All_Values); // keep the status of addition

    }
    return s;
}



/**
 * return all the values mapped to the received key
 * @param mv_hash : MultiValueHashTable to search values in
 * @param key : key to search values with
 * @return : list of the values mapped to the key in the hash table
 */
Element lookupInMultiValueHashTable(MultiValueHashTable mv_hash,Element key){
    if(mv_hash == NULL || key == NULL){
        return NULL;
    }
    return lookupInHashTable(mv_hash->hash_table,key);
}



/**
 * receives value/part of a value that we want to delete from the hashtable, the function checks if the key exists
 * if yes she will look for the value we want to delete, if found she will delete him and if there is not values mapped
 * for the recevied key she will delete the key also from the MultiValueHashTable.
 * @param mv_hash : MultiValueHashTable we want to delete the value from
 * @param key : key to search by
 * @param value : value / part of the value we want to delete
 * @return : status to inform the user if the deletion succeed
 */
status removeFromMultiValueHashTable(MultiValueHashTable mv_hash, Element key, Element value){
    if(mv_hash == NULL || key == NULL || value == NULL){
        return failure;
    }
    LinkedList res_pair  = lookupInMultiValueHashTable(mv_hash, key); // returned pair from the lookup if found/null
    if(res_pair == NULL) {
        return failure; // search failed
    }
    status s =deleteNode(res_pair,value);
    if(s==failure) return failure;
    if (getLengthList(res_pair) == 0) // there is no values - need te delete the key
    {
    key = mv_hash->copyKey(key); // to handle the situation we do not want to delete the whole key
    mv_hash->freeKey(key);
    key = NULL;
    }
    return success;

}

/**
 * prints the key and all the values mapped to received key in the MultiValueHashTable
 * @param mv_hash : MultiValueHashTable to print values from
 * @param key : key to print and print his values
 * @return status to inform the user if the display succeed
 */
status displayMultiValueHashElementsByKey(MultiValueHashTable mv_hash, Element key){
    if(mv_hash == NULL || key == NULL){
        return failure;
    }

    Element res_pair  = lookupInMultiValueHashTable(mv_hash, key); // returned pair from the lookup if found/null
    if(res_pair == NULL) {
        return failure; // search failed
    }
    mv_hash->printKey(key);

    return displayList(res_pair);


}

