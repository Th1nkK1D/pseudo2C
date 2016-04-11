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


/* Function Declaration */
void writeStdFunction(FILE* pOut);
void writeIndent(FILE* pOut);
void processLine(char buffer[],FILE* pOut,int line);

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

	/* Key = first word */
	sscanf(buffer,"%s",key);

	pRule = getRule('k',key);

	if(pRule == NULL)
		{
		printf("Error: Key not found at line %d\n",line);
		printf(">>> %s\n",buffer);

		return 0;
		}

	return 1;
	}
