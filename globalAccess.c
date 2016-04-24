#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mainStructure.h"

static FILE_T* pFile = NULL;
static VARIABLE_T* pRoot = NULL;
static NEST_T * head = NULL;
static int i = 1;

/*this function for find the word that user enter*/
VARIABLE_T * findWord(VARIABLE_T* pCurrent,char name[])
    {
    VARIABLE_T* foundWord = NULL;
    if(pCurrent != NULL)
        {
        if(strcmp(name,pCurrent->name) == 0)
            {
            foundWord = pCurrent;
            }
        else if(strcmp(pCurrent->name,name) > 0)
            {
            foundWord = findWord(pCurrent->leftChild,name);
            }
        else
            {
            foundWord = findWord(pCurrent->rightChild,name);
            }
        }
    return foundWord;
    }

/*this function for search the word*/
VARIABLE_T * searchWord(char name[])
	{
	VARIABLE_T* word = NULL;
	word = findWord(pRoot,name);
	return word;
	}

FILE_T * findFile(FILE_T* pCurrent,char name[])
    {
    FILE_T* foundWord = NULL;
    if(pCurrent != NULL)
        {
        if(strcmp(name,pCurrent->handle) == 0)
            {
            foundWord = pCurrent;
            }
        else if(strcmp(pCurrent->handle,name) > 0)
            {
            foundWord = findFile(pCurrent->pleft,name);
            }
        else
            {
            foundWord = findFile(pCurrent->pright,name);
            }
        }
    return foundWord;
    }

FILE_T * searchFile(char name[])
    {
    FILE_T* nameFile = NULL;
    nameFile = findFile(pFile,name);
    return nameFile;
    }

void insertFile(FILE_T* pRoot, FILE_T* pNewNode)
    {
    if (strcmp(pNewNode->handle, pRoot->handle) == 0)
        {
        free(pNewNode->handle);
        free(pNewNode->path);
        free(pNewNode->mode);
        }
    else if (strcmp(pNewNode->handle, pRoot->handle) < 0)
        {
        if (pRoot->pleft == NULL)
            {
            pRoot->pleft = pNewNode;
            }
        else
            {
            insertFile(pRoot->pleft,pNewNode);
            }
        }
    else
        {
        if (pRoot->pright == NULL)
            {
            pRoot->pright = pNewNode;
            }
        else
            {
            insertFile(pRoot->pright,pNewNode);
            }
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
        if(pFile == NULL)
            {
            pFile = inStruct;
            }
        else
            {
            insertFile(pFile,inStruct);
            }
        }
    }

/*this function for free the tree*/
void freeTree()
    {
    if (pRoot->leftChild != NULL)
        {
        freeTree(pRoot->leftChild);
        }
    if (pRoot->rightChild != NULL)
        {
        freeTree(pRoot->rightChild);
        }
    free(pRoot->name);
    free(pRoot->type);
    free(pRoot->symbol);
    free(pRoot);
    }

 /*this function for push a data item onto the stack
  *return 1 if successful,0 if we have an overflow 
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

/*This function for insert the people in the trees*/
void insertVariable(VARIABLE_T* pRoot, VARIABLE_T* pNewNode)
    {
    if (strcmp(pNewNode->name, pRoot->name) == 0)
        {
        free(pNewNode->name);
        free(pNewNode->type);
        free(pNewNode->symbol);
        }
	else if (strcmp(pNewNode->name, pRoot->name) < 0)
        {
        if (pRoot->leftChild == NULL)
            {
            pRoot->leftChild = pNewNode;
            }
        else
            {
            insertVariable(pRoot->leftChild,pNewNode);
            }
        }
    else
        {
        if (pRoot->rightChild == NULL)
            {
            pRoot->rightChild = pNewNode;
            }
        else
        	{
            insertVariable(pRoot->rightChild,pNewNode);
            }
        }
    }
/*this function for add the name of variable,type of variable and symbol*/
void addVariable(char in_word[],char in_type[])
	{
	char input[32];
	char in_symbol;
	VARIABLE_T* in_variable = NULL;
	while(strcmp(input,"DONE") != 0)
		{

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
 			strcpy(in_variable->symbol,&in_symbol);
 			if(pRoot == NULL)
 				{
 				pRoot = in_variable;
 				}
 			else
 				{
 				insertVariable(pRoot,in_variable);
 				}
 			}
		}
	}
