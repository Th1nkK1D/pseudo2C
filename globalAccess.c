#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _node	
	{
	char word[16];
	char type[8];
	char symbol[64];
	struct _node * leftChild;
	struct _node * rightChild;
	} VARIABLE_T;
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
	VARIABLE_T* pRoot = NULL;
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
