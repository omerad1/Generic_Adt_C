
#ifndef HW2_JERRY_H
#define HW2_JERRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
/** ----------------------------------------------------------------------------------------------------------------
                                                Structures                                                        */
typedef struct {
    // planet structure: the name of the planet and the space coordinates
    // every planet with unique name is always in the same coordinates

    char *name; // pointer to the name of the planet
    float x,y,z; // rational numbers of the coordinates

} Planet;

typedef struct {
    // origin structure: every one comes from an origin and the origin contains the planet the one arrvied from and his
    // dimension name.

    Planet *planet; // the planet of origin
    char *dimension; // dimension name where the planet is in
} Origin;

typedef struct {
    // physical characteristics structure: every one has phyisical chracteristsics that represents them, the object
    // contains unique name and rational number value for every characteristic

    char *name; // characteristic name
    float value; // the value of the physical characteristic

}Characteristics;

typedef struct {
    //jerry structure: represents a jerry with his parameters and characteristics array that will be dynamic array

    char *id;
    int happiness;
    Origin  *origin;
    Characteristics  **pc; // array of pointers
    int pc_size;
}Jerry;

/** ----------------------------------------------------------------------------------------------------------------
                                            Create structures                                                     */
Jerry* CreateJerry(char *id, int happiness, Planet* plt , char* dm_name); // jerry creation

Planet* CreatePlanet(char *name,float x, float y , float z); // planet creation

Characteristics* Createpc(char *name , float value); // pc creation

Origin* CreateOrigin(Planet*, char*); // origin creation


/** -----------------------------------------------------------------------------------------------------------------*/


bool Searchpc(Jerry*,char*); // function to search for physical characteristic

status Addpc(Jerry*,Characteristics*); // add physical characteristic to jerry

status DeletePcByName(Jerry*, char *); // delete physical characteristic by name

status PrintJerry(Element); // prints Jerry's information

status PrintPlanet(Element); // print planet information

status PrintPc(Characteristics**,int ); // print physical characteristic


/** ----------------------------------------------------------------------------------------------------------------
                              Destroying functions for structs */

void DeleteJerry(Jerry*); // deletes jerry structure

void DeletePc(Characteristics*); // deletes physical characteristic  structure

void DeleteOrigin(Origin*); // deletes origin structure

void DeletePlanet(Planet*); // deletes planet structure



/**
 * print function for the jerry's id
 * @param jerry : pointer to the jerry we want to print his id
 * @return : status to inform the user the print succeed
 */
status printJerryID(Element jid);


/** ----------------------------------------------------------------------------------------------------------------
                              copy + compare functions */

/**
 * only shallow copy for the jerry received
 * @param j element we want to shallow copy
 * @return element we recevied
 */
Element ShallowCopyElement(Element j);


/**
 * compare between 2 jerries based on the assumption there can be only one jerry with an specific id
 * @param j : pointer to jerry
 * @param o : pointer to jerry
 * @return : true if the jerry is the same
 */
bool compareJerry(Element j, Element o);


/**
 * compare between 2 planets based on the assumption there can be only one planet with an specific name
 * @param p : pointer to planet
 * @param o : pointer to planet
 * @return : true if the planets is the same either - false.
 */
bool comparePlanet(Element p, Element o);


/**
 * compare 2 Physical characteristic based on their name and value
 */
bool comparePc(Element pc , Element other);

/**
 * prints the pc name
 * @param pc : pointer to the physical characteristic we want to print
 * @return status to inform the user if the deletion succeed
 */
status displayPcName(Element pc);

/**
* compare between 2 jerries based on the assumption there can be only one jerry with an specific id
* @param j : pointer to jerry
* @param o : pointer to jerry
* @return : true if the jerry is the same
*/
bool compareJerry2(Element j, Element o);

/**
 * copy function for Physical characteristic
 * @param pc : pointer to the Physical characteristic name we want to copy
 * @return : pointer to the Physical characteristic created
 */
Element copyPcname(Element pc);

/**
 * deletes pc name and free his memory
 * @param pc
 * @return
 */
status DeletePcName(Element pc);

/**
 * this function search in the jerry's pc array for unique name that is equal to the name received
 * if the name is the same in both size it will exit the function and return the Physical Characteristic
 * if the function finished the loop
 * it means that there is no correlation and the function will return NULL
 */
Characteristics* FullSearchpc(Jerry* j ,char name[]);

/**
 * compare 2 elements represents planets by their unique name
 */
bool comparePlanet2(Element p, Element o);

#endif //HW2_JERRY_H