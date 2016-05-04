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

/*this function for search the word*/
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

/*this function for search the files*/
FILE_T * searchFile(char name[])
    {
    FILE_T* word = NULL;
    word = fHead;
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

 /*this function for push a data item onto the stack
  return 1 if successful,0 if we have an overflow 
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

/* Removes and returns the top item on the stack.
 * Returns 0 if the queue is empty.
 */
int pop()
    {
    NEST_T * top = head;
    char * data = NULL;
    if (top != NULL)
        {
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

void addFile(char nameFile[32],char type[6])
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
        insertFile(inStruct);
        }
    }

/*This function for insert the people in the trees*/
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
/*this function for add the name of variable,type of variable and symbol*/
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