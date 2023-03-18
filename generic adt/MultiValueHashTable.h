//
// Created by omer on 12/20/22.
//

#ifndef HW3_MULTIVALUEHASHTABLE_H
#define HW3_MULTIVALUEHASHTABLE_H

#include "Defs.h"
typedef struct MuliValueHashTable_t *MultiValueHashTable;


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
                                              int hashNumber );



/**
 * deletes and frees the hash table cells and then the hash table itself
 * @param hash : pointer to the hash table we want to delete
 * @return : status to inform if the deletion completed successfully
 */
status destroyMultiValueHashTable(MultiValueHashTable mv_hash);



/**
 * function add to the hash table mapping between the value and the key, if the key already exists in the hash table
 * she will add the value to the other values share the same key.
 * @param mv_hash : MultiValueHashTable to add the value to based on the mapping of received key
 * @param key : element represents key to map the value to the hash table
 * @param value : value to add to the hash table
 * @return : status to inform if the insertion completed successfully
 */
status addToMultiValueHashTable(MultiValueHashTable mv_hash,Element key,Element value);



/**
 * return all the values mapped to the received key
 * @param mv_hash : MultiValueHashTable to search values in
 * @param key : key to search values with
 * @return : list of the values mapped to the key in the hash table
 */
Element lookupInMultiValueHashTable(MultiValueHashTable mv_hash,Element key);



/**
 * receives value/part of a value that we want to delete from the hashtable, the function checks if the key exists
 * if yes she will look for the value we want to delete, if found she will delete him and if there is not values mapped
 * for the recevied key she will delete the key also from the MultiValueHashTable.
 * @param mv_hash : MultiValueHashTable we want to delete the value from
 * @param key : key to search by
 * @param value : value / part of the value we want to delete
 * @return : status to inform the user if the deletion succeed
 */
status removeFromMultiValueHashTable(MultiValueHashTable mv_hash, Element key, Element value);



/**
 * prints the key and all the values mapped to received key in the MultiValueHashTable
 * @param mv_hash : MultiValueHashTable to print values from
 * @param key : key to print and print his values
 * @return status to inform the user if the display succeed
 */
status displayMultiValueHashElementsByKey(MultiValueHashTable mv_hash, Element key);



#endif //HW3_MULTIVALUEHASHTABLE_H
