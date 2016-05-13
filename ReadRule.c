#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainStructure.h"

/*
* this function for print the rule of pseudo code
* and print the example of pseudo code if user 
*  wanna see it.
*/
void ReadRule()
	{
	char rule[512];								/*variable that get the rule in the text file.*/
	char input[32];				
	char pSudo[512];							/*variable that get the example of pseudo code.*/
	FILE* ruletxt = NULL;						/*Input rule file pointer,*/
	FILE* sudo = NULL;							/*Input example of pseudo code pointer*/
	ruletxt = fopen("basicRules.txt","r");		/*open basic rules of pseudo code file.*/
	if(ruletxt == NULL)							/*if file does not exist.*/
		{
		printf("ERROR,file does not exist.\n");
		}
	clearScr();
	while(fgets(rule,sizeof(rule),ruletxt) != NULL)		/*this*/
		{
		printf("%s",rule);
		}
	while(1)
		{
		printf("Do you want to see Pseudo Code example.(Y/N) :");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(strcasecmp(input,"Y") == 0 || strcasecmp(input,"N") == 0)
			{
			break;
			}
		printf("ERROR, please enter Y/N.\n\n");
		}
	if(strcasecmp(input,"Y") == 0)
		{
		clearScr();
		sudo = fopen("sudo.txt","r");
		while(fgets(pSudo,sizeof(pSudo),sudo) != 0)
			{
			printf("%s",pSudo);
			}
		fclose(sudo);
		}
	fclose(ruletxt);
	}