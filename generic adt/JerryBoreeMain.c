
#include <stdio.h>
#include "Jerry.h"
#include <string.h>
#include "LinkedList.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "Defs.h"
#include <math.h>


int p_index = 0; // index to keep tracking the planets
LinkedList Planets; // linked list to store planets
LinkedList Jerry_FH; // linked list to store jerries
hashTable Jerries; // hashtable to store jerries, key = id , value = struct jerry
MultiValueHashTable Phyisical_c; // multivaluehashtable to store physical characteristics where key = the name of
// the pc and value = jerry that own this characteristic


/**
 * function that iterate over the received string and sum his ascii value
 * @param s: the string we want to sum his ascii value
 * @return : the sum of the ascii values of all the chars
 */
int TransformSToNumber(Element e){
    if(e == NULL){
        return -1;
    }
    char* s = (char*) e;
    int sum = 0;

    for(int i =0 ; i< strlen(s) ; i ++){
        sum+= s[i];
    }
    return sum;

}


/**
 * destroy the structures hold the data of the program and clean all the memory allocated
 */
static void Cleaner(){
    if(Planets != NULL)
        destroyList(Planets);

    if(Jerry_FH != NULL)
        destroyList(Jerry_FH);

    if(Phyisical_c != NULL)
        destroyMultiValueHashTable(Phyisical_c);

    if(Jerries != NULL)
        destroyHashTable(Jerries);
}


/**
 * compare 2 floats and return their difference in absolute value
 * @param a:float
 * @param b:float
 * @return: difference between a and b in abs
 */
double PcAbs(float a, float b)
{
    double x = a-b;
    return (fabs(x));
}


/**
 * the function gets buffer :planetName,x,y,z and split it to tokens by ",".
 * then it uses the function "searchByKeyInList" to check if there is planet like this in the planet linked list already
 * end by adding the planet to the planets linked list and increase the p_index that represents the planets entered by 1.
 * @param b : buffer with details about the planet we want to add
 */
static void BtoP ( char b [] ){
    char pname[300];
    float x,y,z;
    strcpy(pname, strtok(b , ",")); // planet name
    x = atof(strtok(NULL, ",")); // x
    y = atof(strtok(NULL, ",")); // y
    z = atof(strtok(NULL, ",")); // z
    if(searchByKeyInList(Planets, pname) == NULL) {// looking
        // for a planet in the planet linked list, if its new planet we will insert him into the linked list of planets
        Planet *p = CreatePlanet(pname, x, y, z); // creates new planet
        if (p == NULL) { // problem in the creation
            printf("Memory Problem\n");
            Cleaner();
            exit(0) ;
        }
        else {
            if(appendNode(Planets, p) == failure){
                printf("Memory Problem\n");
                Cleaner();
                exit(0) ;
            } // insert the planet to the array
            p_index++;

        }
    }
}

/**
* this function receives buffer with line specify
* physical characteristic and add it to the jerry in the right
* place based on the j_index
 * @param jerry
 * @param b
 */
static void addpctoj(Jerry* jerry ,char b []) {
    if(jerry == NULL){
        return;
    }
    char name[300];
    float value;
    strcpy(name, strtok(b, ":")); // coping the token into char name
    value = atof(strtok(NULL, "")); // coping the value into float value
    Characteristics *pc = Createpc(name, value); // creates pc
    if(pc == NULL){
        printf("Memory Problem\n");
        Cleaner();
        exit(0) ;
    }
    if (Addpc(jerry, pc) == failure) {
        printf("Memory Problem\n");
        Cleaner();
        exit(0) ;
    }

    if(addToMultiValueHashTable(Phyisical_c,pc->name,jerry) == failure){
        printf("Memory Problem\n");
        Cleaner();
        exit(0) ;
    }

}

//
static Jerry* MakingJerry(char* id, int happiness, char* planet_name , char* dimension){
    Planet* p = searchByKeyInList(Planets,planet_name);
    // perform search in the linked list of planets to the planet of origin of the jerry received from the buffer
    if(p != NULL){

        Jerry *j = CreateJerry(id, happiness, p,dimension); // create new jerry

        if(j == NULL){ // there is memory problem, exit from the program
            printf("Memory Problem\n");
            Cleaner();
            exit(0) ;
        }
        /// add jerry to the linked list
        if(searchByKeyInList(Jerry_FH, j->id) == NULL){
            if(appendNode(Jerry_FH,j) == failure){
                printf("Memory Problem\n");
                Cleaner();
                exit(0) ;
            }
            /// add jerry to the hash table
            if(addToHashTable(Jerries,j->id,j) == failure){
                printf("Memory Problem\n");
                Cleaner();
                exit(0) ;
            }
        }
        return j;

    }
}

/**
 * the function gets buffer and split it to tokens (id, dimension, planet_name, happiness_level) by ",".
 * then the function calls @MakingJerry to create jerry and add him to structures need to hold him
 * @param b : buffer with line from the text holding details about an jerry
 * @return : pointer to new jerry created
 */
static Jerry* BtoJ (char b [] ) {
    char id[300], pname[300], dimen[300];
    int happiness;
    strcpy(id, strtok(b, ",")); // id
    strcpy(dimen, strtok(NULL, ",")); // dimension
    strcpy(pname, strtok(NULL, ",")); // planet name
    happiness = atoi(strtok(NULL, ",")); // happiness level
    return MakingJerry(id,happiness,pname,dimen);


/**
 * this function is used in order to be sent to structs who request delete function but we dont want to delete
 * the element from the entire program
 */
}
status deleting_bekeilu(Element element){
    return success;
}


/**
 * function that checks if the number is prime
 * @param x : int we want to check if he is prime number
 * @return true i x prime number and false if not
 */
bool is_prime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

/**
 * Function to find the closest prime number to a given number
 * @param x : int we want to find his closest prime number
 * @return  : closest prime number to given argument
 */
int FindPrime(int x) {
    // Check if the given number is prime
    if (is_prime(x)) return x;
    // If the given number is not prime, search for the closest prime
    int i = x;
    while (true) {
        if (is_prime(i)) return i;
        if (is_prime(x - i)) return x - i;
        i++;
    }
}

int main(int argc, char *arguments[]) {
    /// received arguments
    int n = argc;
    int pnum = atoi(arguments[1]); // number of planets received
    char *path = arguments[2];


    /// count the number of jerries
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("unable to open file!");
        Cleaner();
        exit(0);
    }
    // Initialize the line counter
    int line_count = 0;
    // Read the file line by line
    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Increment the line counter
        if(line[0] == '\t'){ // we do not want to count the physical characteristics
            continue;}
        else{
            line_count++;}
    }
    // Close the file
    fclose(fp);
    line_count = line_count - pnum - 2; // the number of the jerries in the file
/** -------------------------------------------------------------------------------------------------------------------
                                            initializations                                                           */

    int hushnumber_a = FindPrime(2*line_count); //find the closest prime number
    int hushnumber_b = FindPrime(3*line_count); //find the closest prime number
    /// creation of linkedlist we will store jerries inside, will be used to pick jerry by happiness level
    Jerry_FH = LinkedList_Create(ShallowCopyElement, PrintJerry,
                                 deleting_bekeilu,  compareJerry2,compareJerry);

    /// creation of linkedlist we will store the planets inside
    Planets = LinkedList_Create(ShallowCopyElement, PrintPlanet,
                                (FreeFunction) DeletePlanet, comparePlanet2,comparePlanet);

    /// creation of hashtable we will store jerries inside when key = id and value = jerry
    Jerries = createHashTable(ShallowCopyElement, (FreeFunction) deleting_bekeilu,
                              (PrintFunction) printJerryID, ShallowCopyElement,
                              (FreeFunction) DeleteJerry, PrintJerry,
                              (EqualFunction) compareJerry,
                              TransformSToNumber, hushnumber_a);

    /// creation of Multivalue - hashtable we will store jerries inside when key = PhysicalCharacteristic name and
    /// value = jerry
    Phyisical_c = createMultiValueHashTable(copyPcname, DeletePcName,
                                            displayPcName,
                                            ShallowCopyElement,
                                            (FreeFunction) deleting_bekeilu,
                                            PrintJerry, (EqualFunction) comparePc,
                                            TransformSToNumber,
                                            hushnumber_b);
/** -------------------------------------------------------------------------------------------------------------------
                                            File reading                                                              */
    Jerry *jer;
    FILE *pF = fopen(path, "r");
    char buffer[512]; // holds one line at a time
    if (pF == NULL) {
        printf("unable to open file!");
        Cleaner();
        exit(0);
    }
    while (fgets(buffer, 512, pF) != NULL) {// will read a single line of text
        int p = strcmp(buffer, "Planets\n");
        if (p == 0) {

            for (int i = 0; i < pnum; i++) {  // creating planets
                fgets(buffer, 512, pF);
                BtoP(buffer); // creates planet
            }
        }

        int j = strcmp(buffer, "Jerries\n"); // we in the jerries part
        if (j == 0) {
            while (fgets(buffer, 512, pF) != NULL) { // to add jerry Characteristics
                if (buffer[0] == '\t') {
                    addpctoj(jer, buffer + 1);
                } else {
                    jer = BtoJ(buffer); // creates new jerry
                }
            }


        }
    }

    fclose(pF); // closing the file

/** -------------------------------------------------------------------------------------------------------------------
                                            Menu and user's input                                                     */
    int ans = 1; // for user's input
    char id[300]; // id of jerry
    char planet_name[30]; // planet name
    char dimension[300]; // dimension name
    int happiness_level; // happiness level
    float pc_val; // physical characteristic value
    char a_pcname[300];
    char ch[300];

    while (ans > 0 && ans < 10) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%s", ch);
        if (strcmp(ch, "1") == 0 || strcmp(ch, "2") == 0 || strcmp(ch, "3") == 0 ||
            strcmp(ch, "4") == 0 || strcmp(ch, "5") == 0 || strcmp(ch, "6") == 0 || strcmp(ch, "7") == 0 ||
            strcmp(ch, "8") == 0 ||
            strcmp(ch, "9") == 0) { // to check valid input
            ans = atoi(ch); // the value of the input
        } else {
            printf("Rick this option is not known to the daycare ! \n");
            continue; // try again
        }
        switch (ans) {

            case 1: /// choose this option will allow rick to add new jerry to the system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                if (lookupInHashTable(Jerries, id) != NULL) { // the jerry is already in the system
                    printf("Rick did you forgot ? you already left him here ! \n");
                } else { // creat new jerry !
                    printf("What planet is your Jerry from ? \n");
                    scanf("%s", planet_name);
                    if (searchByKeyInList(Planets, planet_name) != NULL) {
                        printf("What is your Jerry's dimension ? \n");
                        scanf("%s", dimension);
                        printf("How happy is your Jerry now ? \n");
                        scanf("%d", &happiness_level);
                        Jerry *ji = MakingJerry(id, happiness_level, planet_name, dimension);
                        PrintJerry(ji);
                    } else {
                        printf("%s is not a known planet ! \n", planet_name);
                    }
                }
                continue;
            case 2: /// add Physical characteristic to specified jerry
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *jerry_picked = lookupInHashTable(Jerries, id); // search for the jerry in the hastable
                if (lookupInHashTable(Jerries, id) == NULL) { // the jerry is not in the system
                    printf("Rick this Jerry is not in the daycare ! \n");
                } else {
                    printf("What physical characteristic can you add to Jerry - %s ? \n", id);
                    scanf("%s", a_pcname); // store the physical characteristic received
                    if (Searchpc(jerry_picked, a_pcname) == true) // jerry have this physical characteristic already
                    {
                        printf("The information about his %s already available to the daycare ! \n", a_pcname);
                    } else { // the jerry do not have this physical characteristic
                        printf("What is the value of his %s ? \n", a_pcname);
                        scanf("%f", &pc_val);

                        Characteristics *pc = Createpc( a_pcname, pc_val); // creates pc
                        if(pc == NULL){
                            printf("Memory Problem\n");
                            Cleaner();
                            exit(0) ;
                        }
                        if (Addpc(jerry_picked, pc) == failure) {
                            printf("Memory Problem\n");
                            Cleaner();
                            exit(0) ;
                        }

                        addToMultiValueHashTable(Phyisical_c,pc->name,jerry_picked);
                        displayMultiValueHashElementsByKey(Phyisical_c, a_pcname);
                    }
                }

                continue;
            case 3: /// deletes physical characteristic from jerry
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *jering = lookupInHashTable(Jerries, id); // search for the jerry in the hastable
                if (lookupInHashTable(Jerries, id) == NULL) { // the jerry is already in the system
                    printf("Rick this Jerry is not in the daycare ! \n");
                } else {
                    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", id);
                    scanf("%s", a_pcname);
                    if (Searchpc(jering, a_pcname) == true) { // jerry own this physical characteristic
                        if(DeletePcByName(jering, a_pcname) == failure){// delete the physical characteristic from the jerry specified
                            printf("Memory Problem\n");
                            Cleaner();
                            exit(0) ;
                        }
                        removeFromMultiValueHashTable(Phyisical_c, a_pcname, jering);// remove the jerry from the
                        // cell in the hash table
                        PrintJerry(jering); // print the jerry
                    } else { // this jerry doesn't own the wanted Physical characteristic
                        printf("The information about his %s not available to the daycare ! \n",a_pcname);
                    }
                }


                continue;
            case 4:  /// deletes jerry from the system
                printf("What is your Jerry's ID ? \n");
                scanf("%s", id);
                Jerry *jerry4 = lookupInHashTable(Jerries, id); // search for the jerry in the hastable
                if (lookupInHashTable(Jerries, id) == NULL) { // the jerry is already in the system
                    printf("Rick this Jerry is not in the daycare ! \n");
                } else {
                    deleteNode(Jerry_FH, jerry4);
                    for (int i = 0; i < jerry4->pc_size; i++) {
                        removeFromMultiValueHashTable(Phyisical_c, jerry4->pc[i]->name, jerry4);

                    }
                    removeFromHashTable(Jerries, jerry4->id);
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                }
                continue;
            case 5:/// compare all the jerries with the same Physical characteristic and returns the jerry with the closest
                /// absolut value to the received one.
                printf("What do you remember about your Jerry ? \n");
                scanf("%s",a_pcname);
                LinkedList case5 = lookupInMultiValueHashTable(Phyisical_c,a_pcname);
                if(case5 == NULL || getLengthList(case5)<=0){
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n",a_pcname);

                }
                else{
                    printf("What do you remember about the value of his %s ? \n",a_pcname);
                    scanf("%f", &pc_val); // store the value in this var
                    printf("Rick this is the most suitable Jerry we found : \n");// will print the most suitable ↓
                    double min = INFINITY;
                    Element will_returned = NULL; // will hold the jerry we will print
                    for(int i=0 ; i<getLengthList(case5) ; i++){ // iterate over the jerries with the Physical
                        //Characteristic specified

                        Jerry* temp = getDataByIndex(case5, i);
                        Characteristics* c = FullSearchpc(temp,a_pcname); // the physical characteristic we want
                        // to check right now
                        double x = PcAbs(c->value, pc_val);
                        if(x<min){
                            min = x;
                            will_returned = temp;
                        }
                    }
                    Jerry* will = (Jerry*)will_returned;
                    PrintJerry(will_returned);
                    deleteNode(Jerry_FH, will_returned);
                    for (int i = 0; i < will->pc_size; i++) {
                        removeFromMultiValueHashTable(Phyisical_c, will->pc[i]->name, will);
                    }
                    removeFromHashTable(Jerries, will->id);
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                }

                continue;

            case 6: /// iterate over all the jerries in the system and find the saddest jerry
                if( Jerry_FH == NULL|| getLengthList(Jerry_FH) == 0 ) // there is no jerries in the system
                {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");

                }
                else{ // there is at least one jerry in the system
                    Element will_printed = NULL;
                    int min = 101;
                    for(int i = 0 ; i<getLengthList(Jerry_FH) ; i++){
                        Jerry* temp_j =getDataByIndex(Jerry_FH,i);
                        if(temp_j->happiness<min){
                            min = temp_j->happiness;
                            will_printed = temp_j;
                        }
                    }
                    printf("Rick this is the most suitable Jerry we found : \n");
                    PrintJerry(will_printed);
                    Jerry* will = (Jerry*) will_printed;
                    deleteNode(Jerry_FH, will);

                    for (int i = 0; i < will->pc_size; i++) {
                        removeFromMultiValueHashTable(Phyisical_c, will->pc[i]->name, will);

                    }
                    removeFromHashTable(Jerries, will->id);
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");



                }
                continue;
            case 7: /// will print data about the jerries and the system by demand
                printf("What information do you want to know ? \n");
                printf("1 : All Jerries \n");
                printf("2 : All Jerries by physical characteristics \n");
                printf("3 : All known planets \n");
                scanf("%s", ch);
                if (strcmp(ch, "1") == 0 || strcmp(ch, "2") == 0 || strcmp(ch, "3") == 0) { // to check valid input
                    ans = atoi(ch); // the value of the input
                }
                else {
                    printf("Rick this option is not known to the daycare ! \n");
                    continue; // try again
                }
                switch (ans) {
                    case 1: /// print all jerries in the system
                        if(Jerry_FH == NULL || getLengthList(Jerry_FH)==0){
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                        }
                        else{
                            displayList(Jerry_FH);
                        }
                        continue;
                    case 2:/// will print all the jerries with specific (by user request) physical characteristic
                        printf("What physical characteristics ? \n");
                        scanf("%s",a_pcname);
                        LinkedList t = lookupInMultiValueHashTable(Phyisical_c,a_pcname);
                        if(t == NULL || getLengthList(t) == 0){
                            printf("Rick we can not help you - we do not know any Jerry's %s ! \n",a_pcname);

                        }
                        else{
                            displayMultiValueHashElementsByKey(Phyisical_c,a_pcname);
                        }
                        continue;
                    case 3: /// print all known planets
                        displayList(Planets);
                        continue;
                }

            case 8:
                if( Jerry_FH == NULL|| getLengthList(Jerry_FH) == 0 ) // there is no jerries in the system
                {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    continue;


                }
                printf("What activity do you want the Jerries to partake in ? \n");
                printf("1 : Interact with fake Beth \n");
                printf("2 : Play golf \n");
                printf("3 : Adjust the picture settings on the TV \n");
                scanf("%s", ch);
                if (strcmp(ch, "1") == 0 || strcmp(ch, "2") == 0 || strcmp(ch, "3") == 0) { // to check valid input
                    ans = atoi(ch); // the value of the input
                }
                else {
                    printf("Rick this option is not known to the daycare ! \n");
                    continue; // try again
                }
                switch (ans) {
                    case 1: /// will add 15 happiness points to if the jerry have happiness_level >= 20 and
                        /// will sub 5 happiness points if else
                        for(int i = 0 ; i<getLengthList(Jerry_FH) ; i++){
                            Jerry* tempo = getDataByIndex(Jerry_FH,i);
                            if (tempo->happiness >= 20){ // need to increase
                                tempo->happiness += 15;
                                if(tempo->happiness >100){
                                    tempo->happiness = 100;}
                            }
                            else{ // need to decrease
                                tempo->happiness -=5;
                                if(tempo->happiness <0){
                                    tempo->happiness=0;
                                }
                            }
                        }
                        printf("The activity is now over ! \n");
                        displayList(Jerry_FH); // display jerries after the change
                        continue;
                    case 2: // if jerry have happiness level of 50 and above he get + 10 happiness level and if not he get
                        // - 10 happiness level
                        for(int i = 0 ; i<getLengthList(Jerry_FH) ; i++){
                            Jerry* tempo = getDataByIndex(Jerry_FH,i);
                            if (tempo->happiness >= 50){ // need to increase
                                tempo->happiness += 10;
                                if(tempo->happiness >100){
                                    tempo->happiness = 100;}
                            }
                            else{ // need to decrease
                                tempo->happiness -=10;
                                if(tempo->happiness <0){
                                    tempo->happiness=0;
                                }
                            }
                        }
                        printf("The activity is now over ! \n");
                        displayList(Jerry_FH); // display jerries after the change
                        continue;


                    case 3:// add 20 points to all the jerries happiness level
                        for(int i = 0 ; i<getLengthList(Jerry_FH) ; i++){
                            Jerry* tempo = getDataByIndex(Jerry_FH,i);
                            tempo->happiness += 20;
                            if(tempo->happiness >100){
                                tempo->happiness = 100;}
                        }
                        printf("The activity is now over ! \n");
                        displayList(Jerry_FH); // display jerries after the change

                        continue;

                }
            case 9: /// exit from the system
                Cleaner(); // clean the memory
                printf("The daycare is now clean and close ! \n");
                exit(0);



        }







    }
    return 0;
}
