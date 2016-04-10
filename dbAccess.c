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
void extractProperty(char* target,char* buffer);

/* Import rules to array from rules file */
int prepareDB()
	{
	char buffer[128];
	int i = 0;
	char* token;

	/* Open rules file */
	pFile = fopen(rulesFile,"r");

	if (pFile == NULL)
		{
		return 0;
		}

	/* Get count from first line */
	if(fgets(buffer,sizeof(buffer),pFile) == NULL || isdigit(buffer[0] == 0))
		{
		return -1;
		}

	sscanf(buffer,"%d",&rulesCount);

	/* Allocate array */
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
		/* Allocate struct */
		rulesArray[i] = (RULE_T*) calloc(1,sizeof(RULE_T));

		if(rulesArray[i] == NULL)
			{
			return -2;
			}

		/* Extraxt rule properties */	
		extractProperty(rulesArray[i]->name,buffer);
		extractProperty(rulesArray[i]->key,NULL);
		extractProperty(rulesArray[i]->preIn,NULL);
		extractProperty(rulesArray[i]->preOut,NULL);
		extractProperty(rulesArray[i]->preVar,NULL);
		extractProperty(rulesArray[i]->postIn,NULL);
		extractProperty(rulesArray[i]->postOut,NULL);
		extractProperty(rulesArray[i]->postVar,NULL);
		extractProperty(rulesArray[i]->fChild,NULL);
		extractProperty(rulesArray[i]->description,NULL);
		i++;
		}

	return 1;
	}

void extractProperty(char* target,char* buffer)
	{
	char* token;

	token = strtok(buffer,",");

	if(token[0] != '-')
		{
		strcpy(target,token);
		}
	}

RULE_T* getRule(char field,char keyword[])
	{
	int i = 0;

	if(field == 'k')
		{
		/* Search by key */
		while(i < rulesCount)
			{
			printf("%s\n",rulesArray[i]->key);
			if(strcmp(rulesArray[i]->key,keyword) == 0)
				{
				return rulesArray[i];
				}
			i++;
			}
		}
	else
		{
		/* Search by name */
		while(i < rulesCount)
			{
			if(strcmp(rulesArray[i]->name,keyword) == 0)
				{
				return rulesArray[i];
				}
			i++;
			}
		}

		return NULL;
	}

void freeDB()
	{
	int i;
	for(i = 0; i < rulesCount; i++)
		{
		free(rulesArray[i]);
		}
	free(rulesArray);
	}

int main()
	{
	printf("dbAccess start\n");
	prepareDB();
	printf("prepareDB completed\n");
	RULE_T* get = getRule('k',"IF");
	if (get == NULL)
	{
		printf("Error not found\n");
	}
	printf("test: %s\n",get->preIn);

	freeDB();
	}