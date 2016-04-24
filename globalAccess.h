/*this function for search the word
 *return NULL if word does not exist.
*/
VARIABLE_T * searchWord(char name[]);

FILE_T * searchFile(char name[]);

/*this function for free the tree*/
void freeVariableTree();

void freeFileTree();

void insertFile(FILE_T* pRoot, FILE_T* pNewNode);

void addFile(char nameFile[32],char type[6]);

 /*this function for push a data item onto the stack
  *return 1 if successful,0 if we have an overflow 
 */
int push(char data[]);

/* Removes and returns the top item on the stack.
 * Returns 0 if the queue is empty.
 */
int * pop(char postIn[]);

/*This function for insert the people in the trees*/
void insertVariable(VARIABLE_T* pRoot, VARIABLE_T* pNewNode);

/*this function for add the name of variable,type of variable and symbol*/
void addVariable(char in_word[],char in_type[]);



