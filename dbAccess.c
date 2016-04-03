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
int extractProperty(char* target,char* buffer);

/* Import rules to array from rules file */
int prepareDB()
	{
	char buffer[128];
	int i = 0;
	char* token;
	RULE_T* pRule;

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

		/* Allocate struct */
		rulesArray[i] = (RULE_T*) calloc(1,sizeof(RULE_T));

		if(rulesArray[i] == NULL)
			{
			return -2;
			}

		/* Extraxt rule properties */
			token = strtok(buffer,",");
			printf("token = %s\n",token);
			strcpy(pRule->name,token);
			strcpy(pRule->key,strtok(NULL,","));
			strcpy(pRule->preIn,strtok(NULL,","));
			strcpy(pRule->preOut,strtok(NULL,","));
			strcpy(pRule->preVar,strtok(NULL,","));
			strcpy(pRule->postIn,strtok(NULL,","));
			strcpy(pRule->postOut,strtok(NULL,","));
			strcpy(pRule->postVar,strtok(NULL,","));
			strcpy(pRule->fChild,strtok(NULL,","));
			strcpy(pRule->description,strtok(NULL,","));

		/*if(	extractProperty(rulesArray[i]->name,buffer) == 0 ||
			extractProperty(rulesArray[i]->key,NULL) == 0 ||
			extractProperty(rulesArray[i]->preIn,NULL) == 0 ||
			extractProperty(rulesArray[i]->preOut,NULL) == 0 ||
			extractProperty(rulesArray[i]->preVar,NULL) == 0 ||
			extractProperty(rulesArray[i]->postIn,NULL) == 0 ||
			extractProperty(rulesArray[i]->postOut,NULL) == 0 ||
			extractProperty(rulesArray[i]->postVar,NULL) == 0 ||
			extractProperty(rulesArray[i]->fChild,NULL) == 0 ||
			extractProperty(rulesArray[i]->description,NULL) == 0)
			{
			return -3;
			}*/


			printf("test: %s\n",rulesArray[i]->name);
		break;
		i++;
		}

	return 1;
	}

int extractProperty(char* target,char* buffer)
	{
	printf("extractProperty\n");
	char* token;

	//printf("buffer = %s\n",buffer);
	//printf("pos = %d\n",*pos);

	if(buffer != NULL)
		{
		token = strtok(buffer,",");
		}
	else
		{
		token = strtok(NULL,",");
		}

	//printf("target = %s\n",target);
	//printf("token = %s\n",token);

	//pDelim = strpbrk(buffer,bSym);

	//printf("got pDelim\n");
	/*
	while(*pos < size)
		{
		if(buffer[*pos] == ',')
			{
			printf("found pos at %d\n",*pos);
			buffer[*pos] = '\0';
			target = strdup(buffer);
			printf("data imported = %s\n",target);
			*pos = *pos+1;
			return 1;
			}
		*pos = *pos+1;
		}
	return 0;

	*/

		//*pDelim = '\0';
		strcpy(target,token);
		printf("data imported = %s\n",target);
	}

int main()
	{
	prepareDB();

	}