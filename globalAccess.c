#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mainStructure.h"


static VARIABLE_T* pRoot = NULL;
static NEST_T* head = NULL;

VARIABLE_T * findPerson(PERSON_T* pCurrent,char name[])
    {
    VARIABLE_T* foundPerson = NULL;
    if(pCurrent != NULL)
        {
        if(strcmp(name,pCurrent->name) == 0)
            {
            foundPerson = pCurrent;
            }
        else if(strcmp(pCurrent->name,name) > 0)
            {
            foundPerson = findPerson(pCurrent->leftChild,name);
            }
        else
            {
            foundPerson = findPerson(pCurrent->rightChild,name);
            }
        }
    return foundPerson;
    }

VARIABLE_T * searchPerson(char name[])
	{
	VARIABLE_T* person = NULL;
	person = findPerson(pRoot,name);
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
       	newItem->pData = data;
       	newItem->pNext = head;
       	head = newItem;
		}
	return check;
}

int * pop(char postIn[])
	{
    NEST_T * top = head;
    if (top != NULL)
       	{
       	strcpy(postIn,top->pData);
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
void insertNode(PERSON_T* pRoot, PERSON_T* pNewNode)
    {
    if (compare(pNewNode,pRoot) == 0)
        {
        free(pNewNode->word);
        free(pNewNode->type);
        free(pNewNode->symbol);
        }
	else if (compare(pNewNode,pRoot) < 0)
        {
        if (pRoot->leftChild == NULL)
            {
            pRoot->leftChild = pNewNode;
            }
        else
            {
            insertNode(pRoot->leftChild,pNewNode);
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
            insertNode(pRoot->rightChild,pNewNode);
            }
        }
    }

void addVariable(char in_word[],char in_type[])
	{
	char input[32];
	char in_symbol[64];
	VARIABLE_T* in_variable = NULL;
	while(strcmp(input,"DONE") != 0)
		{

		if(strcmp(in_type),"int" == 0)
			{
			in_symbol = '%d';
			}
		else if(strcmp(in_type),"char" == 0)
			{
			in_symbol = '%c';
			}
		else if(strcmp(in_type),"string" == 0)
			{
			in_symbol = '%s';
			}
		in_variable = (PERSON_T*) calloc(1,sizeof(PERSON_T));
        if(in_variable) == NULL)
			{
			printf("ERROR, cannot allocate.");
			exit(0);
 			}
 		else
 			{
 			strcpy(in_variable->word,in_word);
 			strcpy(in_variable->type,in_type);
 			strcpy(in_variable->symbol,in_symbol);
 			if(pRoot == NULL)
 				{
 				pRoot = in_variable;
 				}
 			else
 				{
 				insertNode(pRoot,in_variable);
 				}
 			}
		}
	}