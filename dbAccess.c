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

/* Import rules to array from rules file 
 *	Return:	1 = Success
 *			0 = Can't open input file
 *			-1 = Can't read count
 *			-2 = Allocattion error
 */
int prepareDB()
	{
	char buffer[512];
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
		extractProperty(rulesArray[i]->postKey,NULL);
		extractProperty(rulesArray[i]->postIn,NULL);
		extractProperty(rulesArray[i]->postOut,NULL);
		extractProperty(rulesArray[i]->postVar,NULL);
		extractProperty(rulesArray[i]->varType,NULL);
		extractProperty(rulesArray[i]->fChild,NULL);
		extractProperty(rulesArray[i]->description,NULL);
		/*
		printf("i = %d\n",i);
		printf("\nname: %s\n",rulesArray[i]->name);
		printf("key: %s\n",rulesArray[i]->key);
		printf("preIn: %s\n",rulesArray[i]->preIn);
		printf("preOut: %s\n",rulesArray[i]->preOut);
		printf("preVar: %s\n",rulesArray[i]->preVar);
		printf("preVar: %s\n",rulesArray[i]->postKey);
		printf("postIn: %s\n",rulesArray[i]->postIn);
		printf("postOut: %s\n",rulesArray[i]->postOut);
		printf("postVar: %s\n",rulesArray[i]->postVar);
		printf("varType: %s\n",rulesArray[i]->varType);
		printf("fChild: %s\n",rulesArray[i]->fChild);
		printf("description: %s\n",rulesArray[i]->description);
		*/
		i++;
		}

	return 1;
	}

/* Extract property from each rule into a structure
 *	Argument:	target = Name of property in structure
 *				buffer = line buffer
 */
void extractProperty(char* target,char* buffer)
	{
	char* token;

	token = strtok(buffer,"|");

	if(token[0] != '-')
		{
		strcpy(target,token);
		}
	}

/* Get rule structure pointer from keyword
 *	Argument:	target = Name of property to search
 *				keyword = Keyword to search
 *	Return:	Matched RULE_T structure pointer if keyword found, NULL if not
 */
RULE_T* getRule(char target,char keyword[])
	{
	int i = 0;

	if(target == 'k')
		{
		/* Search by key */
		while(i < rulesCount)
			{
			//printf("%d > %s\n",i,rulesArray[i]->key);
			if(strcasecmp(rulesArray[i]->key,keyword) == 0)
				{
				return rulesArray[i];
				}
			i++;
			}
		}
	else if(target == 'n')
		{
		/* Search by name */
		while(i < rulesCount)
			{
			if(strcasecmp(rulesArray[i]->name,keyword) == 0)
				{
				return rulesArray[i];
				}
			i++;
			}
		}
		printf("Key not found\n");
		return NULL;
	}

/* Get number of rules 
 * Return: number of rule in array 
 */
int countRule()
	{
	return rulesCount;
	}

/* Get number of rules 
 * Argument:	nameList = array to store each rule name
 * Return: total rule name that added to array
 */
int getAllRuleName(char** nameList)
	{
	int i;

	for(i = 0; i < rulesCount; i++)
		{
		strcpy(nameList[i],rulesArray[i]->name);
		printf("%s\n",nameList[i]);
		}

	return i+1;
	}

/* Free the rules database
 */
void freeDB()
	{
	int i;

	for(i = 0; i < rulesCount; i++)
		{
		free(rulesArray[i]);
		}

	free(rulesArray);
	}