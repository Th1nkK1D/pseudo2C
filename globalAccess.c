#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mainStructure.h"


static VARIABLE_T* pRoot = NULL;
static NEST_T* head = NULL;

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

VARIABLE_T * searchWord(char name[])
	{
	VARIABLE_T* person = NULL;
	person = findWord(pRoot,name);
	return person;
	}

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

int push(char data[])
	{
	int check = 1;
	NEST_T * newItem = (NEST_T *)calloc(1,sizeof(NEST_T));
	if (newItem == NULL)
		{
		check = 0;
		}
	else
		{
        strcpy(newItem->postIn,data);
        strcpy(newItem->pNext,head);
       	head = newItem;
		}
	return check;
}

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
