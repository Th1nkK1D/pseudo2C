/*  Mathematicala statement validator Header File - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survive 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mainStructure.h"
#include "globalAccess.h"

/* Check if mathematical statement id valid 
 *	Argument:	stm = Statement to check
 *				length = Length of statement
 *	Return:	1 if statement is valid, 0 if not
 */
int checkMath(char stm[],int length)
	{
	/* Variable declaration */
	int i = 0;				/* Counter 1 */
	int j = 0;				/* Counter 2 */
	char ops[] = "+-*/%%";	/* Allowed operator string */
	char prt[] = "()";		/* Allowed parenthesis string */
	int allowOps = 0;		/* Allowed operator status */
	int prtCount = 0;		/* Parenthesis counter */
	char var[64];			/* Variable name */

	/* Looping in statement */
	while(i < length)
		{
		/* Proceed if is is not a space */
		if(stm[i] != ' ')
			{
			if(strchr(prt,stm[i]) != NULL)
				{
				/* Found parenthesis */
				if(stm[i] == '(')
					{
					prtCount++;
					}
				else
					{
					prtCount--;
					}

				if(prtCount < 0)
					{
					printf("Invalid Parenthesis\n");
					return 0;
					}
				}

			else if(strchr(ops,stm[i]) != NULL)
				{
				/* Found operator */
				if(allowOps == 1 || (i == 0 && stm[i] == '-'))
					{
					printf("Found Operator: %c\n",stm[i]);
					allowOps = 0;
					}
				else
					{
					printf("Operator %c is not allowed here\n",stm[i]);
					return 0;
					}
				}

			else if((stm[i] >= 'a' && stm[i] <= 'z') || (stm[i] >= 'A' && stm[i] <= 'Z'))
				{
				/* Found variable name */
				j = i;
				memset(var,0,sizeof(var));

				while(j+1 < length && stm[j+1] != ' ' && strchr(ops,stm[j+1]) == NULL && strchr(prt,stm[j+1]) == NULL)
					{
					j++;
					}

				strncpy(var,stm+i,j+1-i);

				/* Check if variable is valid */
				if(searchWord(var) == NULL)
					{
					printf("Variable %s not found\n",var);
					return 0;
					}

				i = j;
				allowOps = 1;
				}

			else if(isdigit(stm[i]) != 0 || stm[i] == '.')
				{
				/* Found a digit */
				allowOps = 1;
				}
			else
				{
				/* Found unallowed special charactor */
				printf("Invalid operator or %c is not allowed\n",stm[i]);
				return 0;
				}
			}

		i++;
		}

	if(prtCount != 0)
		{
		printf("Invalid Parenthesis\n");
		return 0;
		}

	return 1;
	}