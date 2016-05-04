#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainStructure.h"
#include "dbAccess.h"

void getHelp()
	{
	char** help;
	RULE_T* command = NULL;
	int i=0;
	int count;
	int check;
	char input[32];
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
	for(i=0;i<count;i++)
		{
		help[i] = (char*) calloc(16,sizeof(char));
		}
	getAllRuleName(help);/**/
	for(i=0;i<count;i++)
		{
		printf("%s.\n",help[i]);
		}
	while(strcasecmp(input,"DONE") != 0)
		{
		printf("Please select command(type 'DONE' if you want to exit) : ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(strcasecmp(input,"DONE") == 0)
			{
			break;
			}
		command = getRule('n',input);
		if(command != NULL)
			{
			printf("%s : %s\n",command->name,command->description);
			printf("%s %s\n",command->key,command->preIn);
			if(strlen(command->postKey) != 0)
				{
				printf("	//statement\n");
				}
			printf("%s %s\n",command->postKey,command->postIn);
			}	
		}
	freeDB();
	}
