//
// Created by omer on 12/19/22.
//

#ifndef HW3_KEYVALUEPAIR_H
#define HW3_KEYVALUEPAIR_H
#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"
/** pointer to KeyValuePair structure*/
typedef struct KeyValuePair_t* KeyValuePair;

/**
* creates pair of key and value
* @param key : element that represents key
* @param value : element as value
* @param key_copyFunction : copy function for key element
* @param val_copyFunction : copy function for value element
* @param key_printFunction : print function supports the key type
* @param val_printFunction : print function supports the value type
* @param key_freeFunction : free function to delete the key if the creation process failed or if needed to be deleted
* @param val_freeFunction : free function to delete the val if the creation process failed or if needed to be deleted
* @param key_equalFunction : function to compare two elements represents key
* @return : pointer to KeyValuePair created
*/
KeyValuePair createKeyValuePair(Element key, Element value,
    CopyFunction key_copyFunction,CopyFunction val_copyFunction,
    PrintFunction key_printFunction, PrintFunction val_printFunction,
    FreeFunction key_freeFunction, FreeFunction val_freeFunction ,
    EqualFunction key_equalFunction
);


/**
 * the function responsible to delete the pair and free his allocated memory
 * @param key_val : pointer to KeyValuePair
 * @return : status to inform if the deletion completed successfully
 */
status destroyKeyValuePair(KeyValuePair key_val);


/**
 * print the value in the KeyValuePair received
 * @param key_val : pointer to KeyValuePair
 * @return : status to inform if the print has  completed successfully
 */
status displayValue(KeyValuePair key_val);


/**
 * print the value in the KeyValuePair received
 * @param key_val : pointer to KeyValuePair
 * @return : status to inform if the print has  completed successfully
 */
status displayKey(KeyValuePair key_val);


/**
 * get the value in the KeyValuePair
 * @param key_val : pointer to KeyValuePair
 * @return : the value in the KeyValuePair
 */
Element getValue(KeyValuePair key_val);


/**
 * get the key in the KeyValuePair
 * @param key_val : pointer to KeyValuePair
 * @return : the key in the KeyValuePair
 */
Element getKey(KeyValuePair key_val);

/**
 * compare between the key in the KeyValuePair to received key
 * @param key_val : pointer to KeyValuePair
 * @param key : element to compare to
 * @return : true if the key in the KeyValuePair equal to the received key and false if not
 */
bool isEqualKey(KeyValuePair key_val , Element key);


/**
 * creates copy of the key_val pair
 * @param key_val : the KeyValuePair we want to copy
 * @return pointer to the new pair
 */
KeyValuePair copyPair(KeyValuePair key_val);


status displayPair(KeyValuePair key_val);



#endif //HW3_KEYVALUEPAIR_H
