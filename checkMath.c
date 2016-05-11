#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int checkMath(char stm[],int length)
	{
	int i = 0;
	int j = 0;
	char ops[] = "+-*/%%";
	char prt[] = "()";
	int allowOps = 0;
	int prtCount = 0;
	char var[64];

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

				//Check if variable is valid

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

int main()
	{
	char buffer[128];

	do
		{
		printf("Enter statement (leave blank to exit): ");
		fgets(buffer,sizeof(buffer),stdin);

		if(buffer[0] != '\n')
				{
			if(buffer[strlen(buffer)-1] == '\n')
				{
				buffer[strlen(buffer)-1] = '\0';
				}

			if(checkMath(buffer,strlen(buffer)) == 1)
				{
				printf("Statement is valid\n");
				}
			else
				{
				printf("Statement is invalid\n");
				}
			}
		}
	while(buffer[0] != '\n');
	}