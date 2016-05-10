#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainStructure.h"

void ReadRule()
	{
	char rule[512];
	char input[32];
	char pSudo[512];
	FILE* ruletxt = NULL;
	FILE* sudo = NULL;
	ruletxt = fopen("basicRules.txt","r");
	if(ruletxt == NULL)
		{
		printf("ERROR,file does not exist.\n");
		}
	clearScr();
	while(fgets(rule,sizeof(rule),ruletxt) != NULL)
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

int main()
{
	ReadRule();
	return 0;
}