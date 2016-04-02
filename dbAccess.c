/* DB Accessing Module - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survived */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mainStructure.h"

/* Define constant */
const char rulesFile[] = "actionRules.csv";

/* Global Static Variable */
static FILE* pFile = NULL;
static RULE_T** rulesArray = NULL;
static int rulesCount;

/* Private function declaration */
int extractProperty(char* target,char* input);

/* Import rules to array from rules file */
int prepareDB()
	{
	char buffer[128];
	int i = 0;
	char *token = NULL;
	char bSym[] = ",";

	/* Open rules file */
	printf("Open file\n");
	pFile = fopen(rulesFile,"r");

	if (pFile == NULL)
		{
		return 0;
		}

	/* Get count from first line */
	printf("Get count\n");
	if(fgets(buffer,sizeof(buffer),pFile) == NULL || isdigit(buffer[0] == 0))
		{
		return -1;
		}

	sscanf(buffer,"%d",&rulesCount);

	/* Allocate array */
	printf("Allocate Array\n");
	rulesArray = (RULE_T**) calloc(rulesCount,sizeof(RULE_T*));

	if(rulesArray == NULL)
		{
		return -2;
		}

	/* Skip Header line */
	fgets(buffer,sizeof(buffer),pFile);

	/* Get rule from each line */
	while(fgets(buffer,sizeof(buffer),pFile) != NULL)
		{
		printf("Get Rule: %d\n",i);
		printf("%s",buffer);

		
		if(	extractProperty(rulesArray[i]->name,buffer) == 0 ||
			extractProperty(rulesArray[i]->key,NULL) == 0 ||
			extractProperty(rulesArray[i]->preIn,NULL) == 0 ||
			extractProperty(rulesArray[i]->preOut,NULL) == 0 ||
			extractProperty(rulesArray[i]->preVar,NULL) == 0 ||
			extractProperty(rulesArray[i]->postIn,NULL) == 0 ||
			extractProperty(rulesArray[i]->postOut,NULL) == 0 ||
			extractProperty(rulesArray[i]->postVar,NULL) == 0 ||
			extractProperty(rulesArray[i]->fChild,NULL) == 0)
			{
			return -3;
			}
		i++;
		}

	return 1;
	}

int extractProperty(char target[],char input[])
	{
	printf("extractProperty\n");
	char *pDelim = NULL;
	char bSym[] = ",";

	printf("input = %s\n",input);

	if(input != NULL)
		{
		token = strtok(input,bSym);
		}
	else
		{
		token = strtok(NULL,bSym);
		}

	printf("target = %s\n",target);
	printf("token = %s\n",token);

	if(token != NULL)
		{
		target = strdup(token);
		printf("data imported = %s\n",target);
		return 1;
		}
	else
		{
		return 0;
		}
	}

int main()
	{
	prepareDB();

	printf("test: %s\n",rulesArray[0]->name);
	}