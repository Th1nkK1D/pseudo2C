/* Psudocode translator - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survived */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mainStructure.h"
#include "dbAccess.h"
#include "dataUpdate.h"


/* Function Declaration */
void writeStdFunction(FILE* pOut);
void writeIndent(FILE* pOut);
int processLine(char buffer[],FILE* pOut,int line);
int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData);
int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut);

int translator()
	{
	FILE* pIn = NULL;
	FILE* pOut = NULL;
	char buffer[256];
	char inName[32];
	char outName[32];
	int line = 0;

	/* Prepare input file name */
	printf("Input pseudocode file name : ");
	fgets(buffer,sizeof(buffer),stdin);
	sscanf(buffer,"%s",inName);

	pIn = fopen(inName,"r");

	if(pIn == NULL)
		{
		printf("Can't open pseudo code file: \"%s\"\n",inName);
		return 0;
		}

	/* Prepare output file name */
	printf("Output C file name : ");
	fgets(buffer,sizeof(buffer),stdin);
	sscanf(buffer,"%s",outName);

	pIn = fopen(outName,"w");

	if(pIn == NULL)
		{
		printf("Can't create C file: \"%s\"\n",outName);
		return 0;
		}

	/* Write standard function */
	writeStdFunction(pOut);

	//push main

	/* Read each line */
	while(fgets(buffer,sizeof(buffer),pIn) != NULL)
		{
		line++;

		if(buffer[0] == '\n')
			{
			fprintf(pOut,"\n");
			}
		else
			{
			if(buffer[strlen(buffer)-1] == '\n')
				{
				buffer[strlen(buffer)-1] = '\0';
				}

			processLine(buffer,pOut,line);
			}
		}



	return 1;
	}

void writeStdFunction(FILE* pOut)
	{
	fprintf(pOut,"#include <stdio.h>\n");
	fprintf(pOut,"#include <stdlib.h>\n");
	fprintf(pOut,"#include <string.h>\n");
	fprintf(pOut,"\n");
	//To-Do : custom function
	}

void writeIndent(FILE* pOut)
	{
	int indent; //= countStack()
	int i;

	for (int i = 0; i < indent; i++)
		{
		fprintf(pOut,"\t");
		}
	}

int processLine(char buffer[],FILE* pOut,int line)
	{
	char key[8];
	RULE_T* pRule = NULL;
	char currentStack[64];
	int target;
	TEMP_T tempData;
	char arg[4][12];
	char varSet[64];
	char printSet[64];

	/* Key = first word */
	sscanf(buffer,"%s",key);

	pRule = getRule('k',key);

	if(pRule == NULL)
		{
		printf("Error: Key not found at line %d\n",line);
		printf(">>> %s\n",buffer);

		return -1;
		}

	strcpy(currentStack,"TO_DO");

	/* Check if end stack found */
	if (strcmp(buffer,currentStack) == 0)
		{
		//--Pop stack
		writeIndent(pOut);
		target = 1;
		}
	else
		{
		target = 2;
		}

	/* Update temp data */
	if(dataUpdate(pRule,buffer,&tempData) == 0)
		{
		printf("dataUpdate Error");
		return 0;
		}

	/* Detemine pre/post fot variable/print set */
	if(target == 1)
		{
		strcpy(varSet,pRule->preVar);
		strcpy(printSet,pRule->preOut);
		}
	else
		{
		strcpy(varSet,pRule->postVar);
		strcpy(printSet,pRule->postOut);
		}

	/* Prepare Argument */
	prepareArg(arg,varSet,tempData);
	//printOut()


	return 1;
	}

int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData)
	{
	int i = 0;
	char* var = NULL;

	/* Get each variable */
	var = strtok(var,",");

	if(var != NULL)
		{
		/* Push data from tempData to arg array */
		if(strcmp(var,"$con") == 0)
			{
			strcpy(arg[i],tempData.$con);
			}
		else if(strcmp(var,"$value") == 0)
			{
			strcpy(arg[i],tempData.$value);
			}
		else if(strcmp(var,"$v_name") == 0)
			{
			strcpy(arg[i],tempData.$v_name);
			}
		else if(strcmp(var,"$v_symbol") == 0)
			{
			strcpy(arg[i],tempData.$v_symbol);
			}
		else if(strcmp(var,"$v_type") == 0)
			{
			strcpy(arg[i],tempData.$v_type);
			}
		else if(strcmp(var,"$increm") == 0)
			{
			strcpy(arg[i],tempData.$increm);
			}
		else if(strcmp(var,"$f_pointer") == 0)
			{
			strcpy(arg[i],tempData.$f_pointer);
			}
		else if(strcmp(var,"$f_path") == 0)
			{
			strcpy(arg[i],tempData.$f_path);
			}
		else if(strcmp(var,"$f_mode") == 0)
			{
			strcpy(arg[i],tempData.$f_mode);
			}
		else 
			{
			return -1;
			}

		i++;
		strtok(NULL,",");
		}

	return i;
	}

int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut)
	{
	if(count == 1)
		{
		fprintf(pOut,printSet,arg[1]);
		}
	else if(count == 2)
		{
		fprintf(pOut,printSet,arg[1],arg[2]);
		}
	else if(count == 3)
		{
		fprintf(pOut,printSet,arg[1],arg[2],arg[3]);
		}
	else if(count == 4)
		{
		fprintf(pOut,printSet,arg[1],arg[2],arg[3],arg[4]);
		}
	else
		{
		return 0;
		}

	fprintf(pOut, "\n");

	return 1;
	}
