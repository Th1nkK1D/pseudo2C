/********************************************************
*		  <><><><><><><><><>			*
*		  <>    help.c    <>			*
*	   	  <><><><><><><><><>			*
*   This help.c is file that help people to know about	*
* Pseudo’s command					*
*	Created by Gittipat Ariyaprayoon ID:58070503440	*
*				   Section : D		*
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mainStructure.h"
#include "dbAccess.h"

/* This function for get help from the structure and ask user
 * and print the command that user wanna know how to use it.
 */
void getHelp()
	{
	char** help;
	RULE_T* command = NULL;
	int i=0;
	int count;
	int check;
	int num;
	char input[32];
	char pCheck[32];
	check = prepareDB();
	if(check == 0)
		{
		printf("ERROR, can not open database.\n");
		exit(0);
		}
	else if(check == -1)
		{
		printf("ERROR, can not read count.\n");
		exit(1);
		}
	else if(check == -2)
		{
		printf("Allocation error.\n");
		exit(2);
		}
	count = countRule();
	help = (char**) calloc(count,sizeof(char*));
	if(help == NULL)
		{
		printf("Cannot allocated.\n");
        exit(0);
		}
	for(i=0;i<count;i++)
		{
		help[i] = (char*) calloc(16,sizeof(char));
		}
	getAllRuleName(help);
	clearScr();
	while(strcasecmp(input,"DONE") != 0)
		{
		memset(input,'\0',sizeof(input));
		printf("********************************************************************************\n");
		printf("*                                   Help Menu                                  *\n");
		printf("********************************************************************************\n");
		for(i=0;i<count;i++)
			{
			printf("%d.)%s.\n",i+1,help[i]);
			}
		printf("********************************************************************************\n");
		printf("Please select command(type '0' if you want to exit) : ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(strlen(input) == 0)
			{
			printf("ERROR,plase enter the number between 1-15.\n");
			printf("Please press any key to continue : ");
			getchar();
			}
		for(i=0;i<strlen(input);i++)
			{
			if(!isdigit(input[i]))
				{
				strcpy(input,"error");
				break;
				}
			else
				{
				sscanf(input,"%d",&num);
				}	
			}
		if(strcmp(input,"error") == 0)
			{
			printf("ERROR,plase enter the number between 1-15.\n");
			printf("Please press any key to continue : ");
			getchar();;
			}
		else if(num == 0)
			{
			break;
			}
		else if(num>0 && num <= 15)
			{
			sscanf(input,"%d",&num);
			command = getRule('n',help[num-1]);
			if(command == NULL)
				{
				printf("Please press any key to continue : ");
				getchar();
				}
			clearScr();
			if(command != NULL)
				{
				printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
				printf("                              ***********************                  \n");
				printf("                              *  %11s        *\n",command->name);
				printf("                              ***********************                  \n");
				printf("    - %s",command->description);
				printf("--------------------------------------------------------------------------------\n");
				printf("    Example of %s.\n\n",command->name);
				printf("	%s %s\n",command->key,command->preIn);
				if(strlen(command->postKey) != 0)
					{
					printf("	   //statement\n");
					}
				printf("	%s %s\n",command->postKey,command->postIn);			
				printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
				printf("Please press any key to continue : ");
				fgets(pCheck,sizeof(pCheck),stdin);
				sscanf(pCheck,"%s",pCheck);
				clearScr();
				}
			}
		else
			{
			printf("ERROR,plase enter the number between 1-15.\n");
			printf("Please press any key to continue : ");
			getchar();
			}
		}
	freeDB();
	}