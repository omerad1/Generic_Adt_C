
#include "KeyValuePair.h"
/**
 * the KeyValuePair - stores key and value
 */
struct KeyValuePair_t{
    Element key;
    Element value;
    FreeFunction key_freeFunction; // free function for the key
    FreeFunction val_freeFunction; // free function for the value

    PrintFunction key_printFunction;// print function
    PrintFunction val_printFunction;// print function

    CopyFunction key_copyFunction;// copy function
    CopyFunction val_copyFunction;// copy function

    EqualFunction key_equalFunction; // equal function
};

/**
* allocates memory for the KeyValuePair and creates the pair
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
                                ){
    if
    (key_copyFunction == NULL || val_copyFunction == NULL ||
    key_printFunction == NULL || val_printFunction == NULL ||
    key_freeFunction == NULL || val_freeFunction == NULL ||
    key_equalFunction == NULL){
        return NULL;}

    KeyValuePair key_val = (KeyValuePair) malloc(sizeof (struct KeyValuePair_t)); //allocate memory for the pair
    if(key_val == NULL){
        free(key_val);
        return NULL;
       }

    key_val->key= key_copyFunction(key); // the key of the pair
    key_val->value= val_copyFunction(value);  // the value of the pair

    key_val->key_freeFunction = key_freeFunction; // free function for the key
    key_val->val_freeFunction = val_freeFunction; // free function for the value

    key_val->key_printFunction = key_printFunction;// print function for the key
    key_val->val_printFunction = val_printFunction;// print function for the value

    key_val->key_copyFunction = key_copyFunction;// copy function for the key
    key_val->val_copyFunction = val_copyFunction;// copy function for the value

    key_val->key_equalFunction = key_equalFunction; // equal function for the key


    return key_val;
}

/**
 * using the free function for the key and the free function for the value to free them, at the end free
 * the KeyValuePair
 * @param key_val : pointer to the KeyValuePair we want to delete
 * @return : status to inform if the deletion completed successfully
 */
status destroyKeyValuePair(KeyValuePair key_val){
    if(key_val == NULL){
        return failure;
    }

    key_val->key_freeFunction(key_val->key); // using the free function for the key in order to delete him
    key_val->key=NULL;
    key_val->val_freeFunction(key_val->value); // using the free function for the value in order to delete him
    if(key_val != NULL){
        free(key_val);
    }

}

/**
 * print the value in the KeyValuePair received
 * @param key_val : pointer to KeyValuePair
 * @return : status to inform if the print has  completed successfully
 */
status displayValue(KeyValuePair key_val){
    if(key_val == NULL){
        return failure;
    }
    return(key_val->val_printFunction(key_val->value));
}

/**
 * print the value in the KeyValuePair received
 * @param key_val : pointer to KeyValuePair
 * @return : status to inform if the print has  completed successfully
 */
status displayKey(KeyValuePair key_val){
    if(key_val == NULL){
        return failure;
    }
    return(key_val->key_printFunction(key_val->key));
}

/**
 * get the value in the KeyValuePair
 * @param key_val : pointer to KeyValuePair
 * @return : the value in the KeyValuePair
 */
Element getValue(KeyValuePair key_val){
    if(key_val == NULL){
        return NULL;
    }
    return key_val->value;
}


/**
 * get the key in the KeyValuePair
 * @param key_val : pointer to KeyValuePair
 * @return : the key in the KeyValuePair
 */
Element getKey(KeyValuePair key_val){
    if(key_val == NULL){
        return NULL;
    }
    return key_val->key;
}

/**
 * compare between the key in the KeyValuePair to received key
 * @param key_val : pointer to KeyValuePair
 * @param key : element to compare to
 * @return : true if the key in the KeyValuePair equal to the received key and false if not
 */
bool isEqualKey(KeyValuePair key_val , Element key){
    if(key_val == NULL || key == NULL){
        return false;
    }
    bool x = key_val->key_equalFunction(key_val->key,key);
    return x;
}

/**
 * creates copy of the key_val pair
 * @param key_val : the KeyValuePair we want to copy
 * @return pointer to the new pair
 */
KeyValuePair copyPair(KeyValuePair key_val){
    if(key_val == NULL){
        return NULL;
    }
    return key_val;
}

status displayPair(KeyValuePair key_val){
    if(key_val == NULL){
        return failure;
    }
    printf("Key: ");
    displayKey(key_val);
    printf("\nValue: \n");
    displayValue(key_val);
}
