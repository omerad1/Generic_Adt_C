Create : When structure created there is memory allocated for him in the head and we set pointer to it,
in the creation functions we check if memory allocation is succeed or not and if not, we will return to the user in the
main the information he needed to know there was a problem.

Search : In the search function, search is performed by name/id on ADT'S that hold data of structures, the functions will return
boolean value or status that tells if the search failed or not. the second type of  search function if when the function
will return pointer to the struct that has been searched .
when file path is received and we want to create new structure, the search function will help us to know if there is
structure like this already or not.

JerryBoreeMain : we create 4 data structures to hold the data we will read from the file:
1. Planets Linked List - will store the planet structure received from the file
2. Jerries Linked List - will store the jerry structure received from the file, this is for find jerry by happiness level
3. Jerries Hash Table - will store jerries inside him, when key = jerry.id and value = the jerry itself
4. Physical Characteristic MultiValue Hash Table - will store jerries inside him , when key = name of physical characteristic
and value = list of the jerries shares this physical characteristic

Reading file: In this part, there is a buffer filled with one line each time, and there is 2 functions:
BtoJ - transform text line to Jerry structure and add the jerry to the
BtpP - transform text line to Planet structure
in while loop we check if we at the jerries information or in the planets information and perform the transformation
based on the answer.

Hash Number: first, before adding elements to the structures we check for the number of jerries in the file.
after getting the number of jerries, for the hash number in the jerries hash table
we will multiply their number by two because a good "rule of thumb" is that
the hash table should be an array with length about 1.3 times the maximum number of keys that will actually be in the table
we "overestimate" the number and multiply by two because after this action we send the number to function found the closest prime number
and for the physical characteristics multi value hash table we will go by the assumption that there is in average and
by overestimation 3 different physical characteristics to each jerry, this number is also sent to the function
to found the closest prime number.

Menu: In this part, there is switch case and actions performed based on the user's input, at the exit from the program
all the memory is freed and then we return.

Exit + Cleaner: when we want to get out of the program(if its because of memory allocation fail or another problem and
if It's because we've done) we will call Cleaner function that will free all the memory we allocated and will exit from
the program
