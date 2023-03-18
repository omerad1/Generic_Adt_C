//
// Created by omer on 11/25/22.
//
#include "Jerry.h"

/** -------------------------------------------------------------------------------------------------------------------
                                            Structures Creation                                                        */

/**
 * this function initiates a jerry with the details received about him.
 * in the function, there is call to create origin function in order to create the specific Jerry's Origin.
 * memory allocation is performed in order to store Jerry's id, the jerry himself and inside "create origin" the
 * Jerry's origin
 * when a jerry is created he created without a physical characteristics and the field specify how many
 * physical characteristics Jerry have initialized to 0
 * if there as problem in the function creation of any object she will return NULL
 */
Jerry* CreateJerry(char *id, int happiness, Planet* pln, char* dm_name){

    if(id == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;
    }
    if(dm_name == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;}

    if(pln == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;}

    Jerry *j;

    j = (Jerry*) malloc(sizeof(Jerry));

    if (j == NULL) { // memory allocation failed
        free(j);
        return NULL;
    }

    j->id = (char*) malloc(strlen(id)*(sizeof (char))+1); // the length of the id * the size of char = the length of the id

    if (j->id == NULL) { // memory allocation failed
        free(j->id);
        free(j);
        return NULL;
    }


    strcpy(j->id,id);
    j->happiness = happiness;
    j->origin = CreateOrigin(pln,dm_name); // need to be created before
    if(j->origin == NULL){ // the creation of origin has been failed
        return NULL;
    }
    j->pc = NULL; // dynamic array initiates to null value until pc will be added
    j->pc_size = 0;
    return j;
}

/**
 * this function initiates a Planet with received name and coordinates in the space
 * in the function, memory allocation is performed in order to store the planet name
 * and the planet structure itself.
 */
Planet* CreatePlanet(char *name,float x, float y , float z){

    if(name == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;
    }
    Planet  *p;
    p = (Planet*) malloc(sizeof (Planet));
    if(p == NULL){ // memory allocation failed
        free(p);
        return NULL;
    }
    p->name = (char*) malloc(strlen(name)+1);
    if(p->name == NULL){ // memory allocation failed
        free(p->name);
        free(p);
        return NULL;
    }


    strcpy(p->name,name);
    p->x = x; // x coordinate
    p->y= y; // y coordinate
    p->z = z; // z coordinate
    return p;
}
/**
 * this function initiates a physical characteristic with received name and value.
 * in the function, memory allocation is performed in order to store the physical characteristic name
 * and the physical characteristic structure itself.
 */
Characteristics* Createpc(char *name , float value){

    if(name == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;}
    Characteristics *pc;
    pc = (Characteristics*) malloc((sizeof (Characteristics)));

    if(pc == NULL){ // memory allocation failed
        free(pc);
        return NULL;
    }
    pc->name = (char*) malloc(strlen(name)+1);

    if(pc->name == NULL){ // memory allocation failed
        free(pc->name);
        free(pc);
        return NULL;
    }

    strcpy(pc->name,name);
    pc->value = value;
    return pc;
}
/**
 * this function initiates a Origin with received pointer to Planet and Dimension name.
 * in the function, memory allocation is performed in order to store the Origin Dimension name
 * and the Origin structure itself.
 */
Origin* CreateOrigin(Planet* pln , char* dm_name){

    if(pln == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;}

    if(dm_name == NULL){ // checks if the pointer is not damaged and equal null
        return NULL;}

    Origin *o;
    o = (Origin*) malloc(sizeof (Origin));
    if(o == NULL){ // memory allocation failed
        free(o);
        return NULL;
    }
    o->dimension = (char*) malloc(strlen(dm_name)+1);

    if(o->dimension == NULL){ // memory allocation failed
        free(o->dimension);
        free(o);
        return NULL;
    }
    o->planet = pln;
    strcpy(o->dimension,dm_name);
    return o;

}
/**-------------------------------------------------------------------------------------------------------------------*/

/**
 * this function receives jerry and pc
 * the function checks if jerry already have the pc, if he does she will do nothing.
 * if not she will increase the size of the array
 * and will add the new physical characteristic of jerry.
 */
status Addpc(Jerry* j ,Characteristics* pc) {

    if(j == NULL) { // checks if the pointer is not damaged and equal null
        return failure;
    }

    if(pc == NULL) { // checks if the pointer is not damaged and equal null
        return failure;
    }

    if (!Searchpc(j, pc->name)) {
        j->pc_size += 1;
        j->pc = realloc(j->pc, j->pc_size * sizeof(Characteristics));
        if(!j->pc){
            free(j->pc);
            j->pc = NULL;
            return failure;
        }
        j->pc[j->pc_size - 1] = pc;

    }
    else { // cant add the pc
        return failure;
    }
    return success;
}

/** --------------------------------------------------------------------------------------------------------------------
                                             Searching functions */
/**
 * this function search in the jerry's pc array for unique name that is equal to the name received
 * if the name is the same in both size it will exit the function and return true, if the function finished the loop
 * it means that there is no correlation and the function will return false
 */
bool Searchpc(Jerry* j ,char name[]){

    if(j == NULL) { // checks if the pointer is not damaged and equal null
        return false;
    }
    if(name == NULL) { // checks if the pointer is not damaged and equal null
        return false;
    }
    for(int i=0 ; i < j->pc_size ; i++){
        if (!strcmp(j->pc[i]->name,name)){
            return true;
        }
    }
    return false;
}

/**
 * this function search in the jerry's pc array for unique name that is equal to the name received
 * if the name is the same in both size it will exit the function and return true, if the function finished the loop
 * it means that there is no correlation and the function will return false
 */
Characteristics* FullSearchpc(Jerry* j ,char name[]){

    if(j == NULL) { // checks if the pointer is not damaged and equal null
        return NULL;
    }
    if(name == NULL) { // checks if the pointer is not damaged and equal null
        return NULL;
    }
    for(int i=0 ; i < j->pc_size ; i++){
        if (!strcmp(j->pc[i]->name,name)){
            return j->pc[i];
        }
    }
    return NULL;
}


/** --------------------------------------------------------------------------------------------------------------------
                                             Printing functions */

/**
 * prints the name and the value of pc
 */
status PrintPc(Characteristics **pc , int size){

    if(pc==NULL){// checks if the pointer is not damaged and equal null
        return failure;
    }

    printf("\t");
    for(int i =0 ; i<size-1 ; i++){
        printf("%s : %.2f , ", pc[i]->name , pc[i]->value);
    }
    printf("%s : %.2f \n", pc[size-1]->name , pc[size-1]->value);
}

/**
 * prints jerry, the function receives a jerry and prints all his data
 */
status PrintJerry(Element x){
    Jerry* j =(Jerry *) x;

    printf("Jerry , ID - %s : \n",j->id); // id
    printf("Happiness level : %d \n", j->happiness); // happiness level
    printf("Origin : %s \n", j->origin->dimension); // dimension
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",j->origin->planet->name,j->origin->planet->x,j->origin->planet->y,j->origin->planet->z); // planet
    if(j->pc_size>0) {
        printf("Jerry's physical Characteristics available : \n");
        PrintPc(j->pc, j->pc_size);
    }
}

/**
 * prints a planet
 */
status PrintPlanet(Element x){
    Planet* p =(Planet*) x;
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",p->name,p->x,p->y,p->z);
    return success; // tells the planet has been printed successfully
}

/**
 * print function for the jerry's id
 * @param jerry : pointer to the jerry we want to print his id
 * @return : status to inform the user the print succeed
 */
status printJerryID(Element jid){
    if(jid == NULL){
        return failure;
    }
    printf("%s",(char*) jid);
}

/**
 * print the Physical characteristic name
 * @param pc : Physical characteristic name we want to display
 * @return : status to inform the user if the print succeed
 */
status displayPcName(Element pc){
    if(pc == NULL){
        return failure;
    }
    printf("%s : \n", (char*)pc);
    return success;
}
/** --------------------------------------------------------------------------------------------------------------------
                                        Destroying/Deleting functions */
/**
 * function to delete Jerry structer. the function receives the structure and first she free his id,
 * his origin and then loop over his physical characteristics and by using "DeletePc" deletes all of them
 * at the end she free the structure himself from the heap.
 */
void DeleteJerry(Jerry* j){

    if(j->id != NULL){
        free(j->id); // delete id

    j->id = NULL; // to check its freed successful
}

    for(int i=0; i<j->pc_size ; i++){
        if(j->pc[i] != NULL){
            DeletePc(j->pc[i]); // delete the pc array}
        }
    }
    free(j->pc);
    if(j->origin->dimension !=NULL){
    free(j->origin->dimension);
    j->origin->dimension = NULL;
    }

    if(j->origin!=NULL) {
        free(j->origin);
        j->origin = NULL;
    }

    if(j!= NULL){
        free(j); //deletes jerry
        j= NULL;}

}

/**
 * function to delete Characteristics structure. the function receives the structure and first she free his name
 * and then she free the structure himself from the heap.
 */
void DeletePc(Characteristics* pc){

    if(pc->name != NULL){
    free(pc->name); // delete the pc name
    pc->name= NULL; // to check its freed successful
    }
    if(pc != NULL){
    free(pc); // deletes  pc
    pc= NULL; // to check its freed successful
}
}

/**
 * function to delete Origin structure. the function receives the structure and first she free his dimension
 * and then she free the structure himself from the heap.
 */
void DeleteOrigin(Origin* o){

    if(o->dimension != NULL){
        free(o->dimension);
        o->dimension = NULL;
    }

    if(o->planet != NULL) {
        DeletePlanet(o->planet);
        free(o);
        o = NULL;
    }
}

void DeletePlanet(Planet* p ){
    /**
     * function to delete Planet structure. the function receives the structure and first she free his name
     * and then she free the structure himself from the heap.
     */

    if(p->name != NULL){
        free(p->name);} // deletes the planet name
    p->name = NULL;
    if(p!=NULL){
        free(p);} // deletes the planet himself
    p = NULL;
}

/**
 * this function receives jerry and name physical characteristic
 * the function checks is the name is in jerry's physical characteristics
 * if he is the function will use memmove in order to move all the
 * values to the correct new spot
 */
status DeletePcByName(Jerry* j, char * name) {

    if(j == NULL) { // checks if the pointer is not damaged and equal null
        return failure;
    }
    if(name == NULL) { // checks if the pointer is not damaged and equal null
        return failure;
    }

    if (Searchpc(j, name)) {

        for (int i = 0; i < j->pc_size; i++) {
            int ans = strcmp(j->pc[i]->name, name);
            if (ans == 0) {   // we want to delete the pc in the i th index
                j->pc_size --;   // reduce size by one
                Characteristics *storer = j->pc[i]; // creates pointer to the pc we want to delete in order to free him later
                memmove(j->pc + i, j->pc + i + 1, (j->pc_size - i) * sizeof(Characteristics));
                DeletePc(storer);
                j->pc = (Characteristics**) realloc(j->pc,j->pc_size*(sizeof(Characteristics)));
                if(j->pc == 0 && j->pc_size!= 0){ // reallocation failed
                    return failure;
                }
                return success;
            }
        }
    }
    return failure;
}

/**
 * deletes pc name and free his memory
 * @param pc : pointer to the physical characteristic we want to delete
 * @return :status to inform the user if the deletion succeed
 */
status DeletePcName(Element pc){
    if(pc != NULL){
        free(pc);
        pc = NULL;
        return success;
    }

    return failure;
}
/** --------------------------------------------------------------------------------------------------------------------
                                                    copy functions */
/**
 * only shallow copy for the jerry received
 * @param j element we want to shallow copy
 * @return element we recevied
 */
Element ShallowCopyElement(Element j){
    if(j == NULL)
        return NULL;
    return j;
}

/**
 * deep copy function for Physical characteristic name
 * @param pc : pointer to the Physical characteristic name we want to copy
 * @return : pointer to the Physical characteristic created
 */
Element copyPcname(Element pc){
    if(pc == NULL){
        return NULL;
    }
    char* c = (char*)malloc(strlen(pc) + 1) ;
    if(c == NULL){ // memory allocation failed
        return NULL;
    }
    strcpy(c,(char*)pc);
    return c;
}

/** --------------------------------------------------------------------------------------------------------------------
                                                 Compare functions */

/**
 * compare between 2 jerries based on the assumption there can be only one jerry with an specific id
 * @param j : pointer to jerry's id
 * @param o : pointer to jerry's id
 * @return : true if the jerries ids are the same
 */
bool compareJerry(Element j, Element o){
    if(j == NULL || o == NULL)
        return false;
    char* x = (char*) j;
    char* y = (char*) o;
    int res = strcmp(x,y);
    if(res == 0){
        return true;
    }
    else{
        return false;
    }
}

/**
* compare between 2 jerries based on the assumption there can be only one jerry with an specific id
* @param j : pointer to jerry
* @param o : pointer to jerry
* @return : true if the jerry is the same
*/
bool compareJerry2(Element j, Element o){
    if(j == NULL || o == NULL)
        return false;
    Jerry * x = (Jerry *) j;
    Jerry * y = (Jerry *) o;
    int res = strcmp(x->id,y->id);
    if(res == 0){
        return true;
    }
    else{
        return false;
    }
}


/**
 * compare between planet and a name of planet
 * based on the assumption there can be only one planet with an specific name
 * @param p : pointer to planet
 * @param o : pointer to planet name
 * @return : true if the planets is the same either - false.
 */
bool comparePlanet(Element p, Element o){
    if(p == NULL || o == NULL)
        return false;
    Planet* x = (Planet*) p;
    char* y = (char*) o;
    int res = strcmp(x->name,y);
    if(res == 0){
        return true;
    }
    else{
        return false;
    }
}
/**
 * compare 2 elements represents planets by their unique name
 * @param p : element represents planet
 * @param o : element represents planet
 * @return : true if the names are the same and false if not
 */
bool comparePlanet2(Element p, Element o){
    if(p == NULL || o == NULL)
        return false;
    Planet* x = (Planet*) p;
    Planet* y = (Planet*) o;

    int res = strcmp(x->name,y->name);
    if(res == 0){
        return true;
    }
    else{
        return false;
    }
}
/**
 * compare 2 Physical characteristic based on their name
 * @param pc : pointer to Physical characteristic name
 * @param other : pointer to Physical characteristic name
 * @return : true if the Physical characteristics is the same either - false.
 */
bool comparePc(Element pc , Element other){
    if(pc == NULL || other == NULL)
        return false;

    int res = strcmp(pc,other);
    if (res == 0){
        return true;
    }
    else{
        return false;
    }
}

