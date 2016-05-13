/* this function for search the word
 * Argument : name --> name of the word that 
 *                     user wanna search
 * return the structure of that name if the name
 * that user input can found
 * return NULL if can not found.
 */
VARIABLE_T * searchWord(char name[]);

/*this function for search the files
 * Argument : name --> name of file that 
 *                     user wanna search
 * return the structure of that name if the name
 * that user input can found
 * return NULL if can not found.
 */
FILE_T * searchFile(char name[]);

/* this function for delete the structure's file that user
 * wanna to delete
 * Argument : fileName -> name of file that user wanna delete
 */
void deleteFile(char fileName[]);

/*This function for free the memory of linked list of Variable*/
void freeVariable();

/* This function for free the memory of linked list of file's name*/
void freeFile();

/* this function for push a data item onto the stack
 * Argumant : data --> Pointer to generic data we 
 *                     want to add to queue  
 * return 1 if successful,0 if we have an overflow 
 */
int push(char data[]);

/* This function for Removes and returns the top item on the stack.
 * Argument : postIn --> this is the structure that will store the top
 *                       item on the stack
 * Returns 0 if the queue is empty and return 1 and the structure on the top.
 */
int pop(char postIn[]);


/* This function for set the Name of pointer file handle
 * and sent the structure of file to insertFile function
 * Arguments : nameFile --> name of file
 *             type     --> file type
 */
void addFile(char nameFile[32],char type[6],char pointer[]);

/* This function for set the symbol of variable
 * and sent the structure of variable  to 
 * insertVariable function.
 * Arguments : nameFile --> name of variable
 *             type     --> variable type
 */
void addVariable(char in_word[],char in_type[]);