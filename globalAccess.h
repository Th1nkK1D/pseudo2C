/*this function for search the word
 *return NULL if word does not exist.
*/
VARIABLE_T * searchWord(char name[]);

/*this function for search the file
 *return NULL if file does not exist.
*/
FILE_T * searchFile(char name[]);

/*this function for free the linked list of variable*/
void freeVariable();

/*this function for free the linked list of file's name*/
void freeFile();

/*This function for add the file's name,file's path and file's mode*/
void addFile(char nameFile[32],char type[6]);

 /*this function for push a data item onto the stack
  *return 1 if successful,0 if we have an overflow 
 */
int push(char data[]);

/* Removes and returns the top item on the stack.
 * Returns 0 if the queue is empty.
 */
int * pop(char postIn[]);

/*this function for add the name of variable,type of variable and symbol*/
void addVariable(char in_word[],char in_type[]);



