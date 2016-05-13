#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mainStructure.h"

static VARIABLE_T* pHead = NULL;
static VARIABLE_T* pTail = NULL;
static FILE_T* fHead = NULL;
static FILE_T* fTail = NULL;
static NEST_T * head = NULL;
static int i = 1;

/* this function for search the word
 * Argument : name --> name of the word that 
 *                     user wanna search
 * return the structure of that name if the name
 * that user input can found
 * return NULL if can not found.
 */
VARIABLE_T * searchWord(char name[])
    {
    VARIABLE_T* word = NULL;
    word = pHead;
    while(word != NULL)
        {
        if(strcmp(name,word->name) == 0)
            {
            return word;
            }
        else
            {
            word = word->pNext;
            }
        }
    return NULL;
    }

/*this function for search the files
 * Argument : name --> name of file that 
 *                     user wanna search
 * return the structure of that name if the name
 * that user input can found
 * return NULL if can not found.
 */
FILE_T * searchFile(char name[])
    {
    FILE_T* word = NULL;
    word = fHead;
    while(word != NULL)
        {
        if(strcmp(name,word->path) == 0)
            {
            return word;
            }
        else
            {
            word = word->pNext;
            }
        }
    return NULL;
    }
/* this function for delete the structure's file that user
 * wanna to delete
 * Argument : fileName -> name of file that user wanna delete
 */
void deleteFile(char fileName[])
    {  
    FILE_T* found = NULL;
    FILE_T* pFound = NULL;
    found = fHead;
    while(found != NULL)
        {
        if(strcmp(fileName,fHead->path) == 0)
            {
            fHead = found->pNext;
            free(found);
            break;
            }
        else
            {
            if(strcmp(fileName,found->path) == 0)
                {
                if(found == fTail)
                    {
                    free(found);
                    fTail = pFound;
                    break;
                    }
                else
                    {
                    pFound->pNext = found->pNext;
                    free(found);
                    break;
                    }
                }
            else
                {
                pFound = found;
                found = found->pNext;
                }
            }
        }
    }

/*This function for free the memory of linked list of Variable*/
void freeVariable()
    {
    VARIABLE_T* pEntry = NULL;
    pEntry = pHead;
    while(pEntry != NULL)
        {
        free(pEntry);
        pEntry = pEntry->pNext;
        }
    pHead = NULL;
    pTail = NULL;
    }

/* This function for free the memory of linked list of file's name*/
void freeFile()
    {
    FILE_T* pEntry = NULL;
    pEntry = fHead;
    while(pEntry != NULL)
        {
        free(pEntry);
        pEntry = pEntry->pNext;
        }
    fHead = NULL;
    fTail = NULL;
    }

/* this function for push a data item onto the stack
 * Argumant : data --> Pointer to generic data we 
 *                     want to add to queue  
 * return 1 if successful,0 if we have an overflow 
 */

int push(char data[])
    {
    int check = 1;
    NEST_T *newItem = (NEST_T *)calloc(1,sizeof(NEST_T));
    if (newItem == NULL)
        {
        check = 0;
        }
    else
        {
        newItem->pNext = head;
        strcpy(newItem->postIn,data);
        head = newItem;
        }
    return check;
}

/* This function for Removes and returns the top item on the stack.
 * Argument : postIn --> this is the structure that will store the top
 *                       item on the stack
 * Returns 0 if the queue is empty and return 1 and the structure on the top.
 */
int pop(char postIn[])
    {
    NEST_T * top = head;
    char * data = NULL;
    if (top != NULL)
        {
        strcpy(postIn,top->postIn); 
        data = top->postIn;
        head = top->pNext;
        free(top);
        return 1;
        }
    else
        {
        return 0;
        }
    }
/* This function for insert the Name of pointer file handle
 * file type and symbol of that file into linked-list and 
 * set the top and tail of linked list.
 * Arguments : pNewNode --> the structure of file
 */
void insertFile(FILE_T* pNewNode)
    {
    FILE_T* Entry = NULL;
    Entry = (FILE_T*) calloc(1,sizeof(FILE_T));
    if (Entry == NULL)
        {
        printf("Cannot allocated files\n");
        exit(0);
        }
    strcpy(Entry->handle,pNewNode->handle);
    strcpy(Entry->path,pNewNode->path);
    strcpy(Entry->mode,pNewNode->mode);
    if(fHead == NULL)
        {
        fHead = Entry;
        fTail = Entry;
        }
    else
        {
        fTail->pNext = Entry;
        fTail = Entry;
        }
    }
/* This function for set the Name of pointer file handle
 * and sent the structure of file to insertFile function
 * Arguments : nameFile --> name of file
 *             type     --> file type
 */
void addFile(char nameFile[],char type[],char pointer[])
    {
    FILE_T* inStruct = NULL;
    char name[32];
    sprintf(name,"file%d",i);
    i++;
    inStruct = (FILE_T*) calloc(1,sizeof(FILE_T));
    if(inStruct == NULL)
        {
        printf("ERROR, cannot allocate.");
        exit(0);
        }
    else
        {
        strcpy(inStruct->handle,name);
        strcpy(inStruct->path,nameFile);
        strcpy(inStruct->mode,type);
        strcpy(pointer,name);
        insertFile(inStruct);
        }
    }

/* This function for insert the name,type and symbol of variable
 * into linked-list and set the top and tail of linked list.
 * Arguments : pNewNode --> the structure of variable that 
 *                          user want to insert.
 */
void insertVariable(VARIABLE_T* pNewNode)
    {
    VARIABLE_T* Entry = NULL;
    Entry = (VARIABLE_T*) calloc(1,sizeof(VARIABLE_T));
    if (Entry == NULL)
        {
        printf("Cannot allocated files\n");
        exit(0);
        }
    strcpy(Entry->name,pNewNode->name);
    strcpy(Entry->type,pNewNode->type);
    strcpy(Entry->symbol,pNewNode->symbol);
    if(pHead == NULL)
        {
        pHead = Entry;
        pTail = Entry;
        }
    else
        {
        pTail->pNext = Entry;
        pTail = Entry;
        }
    }

/* This function for set the symbol of variable
 * and sent the structure of variable  to 
 * insertVariable function.
 * Arguments : nameFile --> name of variable
 *             type     --> variable type
 */
void addVariable(char in_word[],char in_type[])
    {
    char in_symbol;
    VARIABLE_T* Entry = NULL;
    VARIABLE_T* in_variable = NULL;
    if(strcmp(in_type,"int") == 0)
        {
        in_symbol = 'd';
        }
    else if(strcmp(in_type,"char") == 0)
        {
        in_symbol = 'c';
        }
    else if(strcmp(in_type,"string") == 0)
        {
        in_symbol = 's';
        }
    in_variable = (VARIABLE_T*) calloc(1,sizeof(VARIABLE_T));
    if(in_variable == NULL)
        {
        printf("ERROR, cannot allocate.");
        exit(0);
        }
    else
        {
        strcpy(in_variable->name,in_word);
        strcpy(in_variable->type,in_type);
        sscanf(&in_symbol,"%c",in_variable->symbol);
        insertVariable(in_variable);
        }
    }