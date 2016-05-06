/* Pseudo to C Translator Module - Pseudo2C Project
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
#include "globalAccess.h"

/* Function Declaration */
int writeStdFunction(FILE* pOut);
void writeIndent(FILE* pOut,int indentCount);
int processLine(char buffer[],FILE* pOut,int line, char currentStack[], int* indentCount);
int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData);
int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut);
void cleanBuffer(char buffer[]);

/* Static Variable */
const char stdHeaderFile[] = "stdHeader.in";

/* Translator from Pseudocode to C
 *	Return:	1 = Success
 *			0 = Failed
 */
int translator()
	{
	/* Variable Declaration */
	FILE* pIn = NULL; 
	FILE* pOut = NULL;
	char buffer[256];
	char inName[32];
	char outName[32];
	int line = 0;
	char currentStack[16] = "main";
	int indentCount = 0;

	printf("Translator started\n");

	/* Prepare rule file */
	if(prepareDB() != 1)
		{
		printf("Error preparing rule database\n");
		return 0;
		}

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

	printf("Open input completed\n");

	pOut = fopen(outName,"w");

	if(pOut == NULL)
		{
		printf("Can't create C file: \"%s\"\n",outName);
		return 0;
		}

	printf("Open output completed\n");

	/* Write standard function */
	if(writeStdFunction(pOut) == 0)
		{
		printf("Error: Writing standard header and function failed\n");
		return 0;
		}

	/* Open main function */
	fprintf(pOut,"/* Main function */\n");
	fprintf(pOut,"int main()\n");
	fprintf(pOut,"\t{\n");
	indentCount++;

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
			cleanBuffer(buffer);
			printf("clean buffer = %s\n",buffer);
			/* Process the line */
			if(processLine(buffer,pOut,line,currentStack,&indentCount) != 1)
				{
				printf("Translation abort\n");
				return 0;
				}
			}
		}


	printf("Finished read all the lines\n");

	/* Check if all stack was end */
	if(strcmp(currentStack,"main") != 0)
		{
		printf("Error: Missing END sign at line %d\n",line);
		printf(">>> -> %s\n",currentStack);
		}

	/* Close main function */
	writeIndent(pOut,indentCount);
	fprintf(pOut,"}");
	indentCount--;

	/* Close file */
	fclose(pIn);
	fclose(pOut);

	freeDB();

	printf("Translation Completed!\n");

	return 1;
	}

/* Translate a single line of pseudo code
 *	Argument:	buffer = Output file pointer
 *				pOut = Output file pointer
 *				line = number of input file current line
 *	Return:	1 = Success	
 *			0 = Key not found
 *			-1 = Data update error, invalid systax
 *			-2 = Invalid rule argument
 */
int processLine(char buffer[],FILE* pOut,int line, char currentStack[], int* indentCount)
	{
	char key[16];
	char keyChild[16];
	RULE_T* pRule = NULL;
	char target;
	TEMP_T tempData;
	char arg[4][12];
	char varSet[64];
	char printSet[64];
	char inSet[64];
	int varCount;

	printf("\nprocessLine at line %d\n",line);

	/* Scan line for key and childKey */
	sscanf(buffer,"%s %s",key,keyChild);

	printf("Key read: %s\n",key);

	printf("Current stack = %s Indent = %d\n",currentStack,*indentCount);

	/* Check if end nested found */
	if (strncmp(buffer,"END",3) == 0)
		{
		/* Check if postKey match with currentStack */
		if(strcmp(buffer,currentStack) == 0)
			{
			/* Get rule by end key */
			printf("*stack matched\n");
			target = 'e';
			pRule = getRule(target,key);
	
			if(pRule == NULL)
				{
				printf("Error: postKey not found at line %d\n",line);
				printf(">>> %s\n --> %s?",buffer,key);
	
				return 0;
				}
	
			printf("Rule got: %s\n",pRule->name);
	
			/* End nested (close function) */
			writeIndent(pOut,*indentCount);
			fprintf(pOut,"}");
			
			/* Update Stack */
			*indentCount = *indentCount-1;
			pop(currentStack);
			printf("**newStack = %s newIndent = %d\n",currentStack,*indentCount);
			
			
	
			printf("Target = Post\n");
			printf("preVar: %s\n",pRule->preVar);
			printf("preOut: %s\n",pRule->preOut);
	
			/* Set data */
			strcpy(inSet,pRule->postIn);
			strcpy(varSet,pRule->postVar);
			strcpy(printSet,pRule->postOut);
			}
		else
			{
			/* postKey doesn't match with currentStack */
			printf("Error: Invalid postKey at line %d\n",line);
			printf(">>> %s\n --> %s?",buffer,currentStack);
			
			return 0;
			}
		}
	else
		{
		/* Get rule by key */
		target = 'k';
		pRule = getRule(target,key);

		if(pRule == NULL)
			{
			printf("Error: Key not found at line %d\n",line);
			printf(">>> %s --> %s?\n",buffer,key);

			return 0;
			}
			
		/* Check for child function */
		if(strcmp(keyChild,pRule->fChild) == 0)
			{
			/* Print current Key */
			fprintf(pOut,"%s ",key);
			
			/* Shift key and buffer */
			strcpy(key,keyChild);
			strcpy(buffer,buffer + strlen(key) + 1);
			
			/* Get rule from new key */
			pRule = getRule(target,key);

			if(pRule == NULL)
				{
				printf("Error: Key not found at line %d\n",line);
				printf(">>> %s --> %s?\n",buffer,key);
	
				return 0;
				}
			
			}

		printf("Rule got: %s\n",pRule->name);

		/* New function */
		printf("Target = Pre\n");		
		printf("postVar: %s\n",pRule->preVar);
		printf("postOut: %s\n",pRule->preOut);

		/* Set data */
		strcpy(inSet,pRule->preIn);
		strcpy(varSet,pRule->preVar);
		strcpy(printSet,pRule->preOut);
		}

	/* Update temp data */
	if(dataUpdate(pRule,buffer,&tempData) == 0)
		{
		printf("Error: Invalid Syntax at line %d\n",line);
		printf(">>> %s\n --> %s",buffer,inSet);
		return -1;
		}

	printf("Data Update success\n");

	printf("varSet: %s\n",varSet);
	printf("printSet: %s\n",printSet);

	/* Prepare Argument */
	varCount = prepareArg(arg,varSet,tempData);
	writeIndent(pOut,*indentCount);

	printf("pass Indent\n");

	if(varCount < 0 || writeOut(arg,printSet,varCount,pOut) == 0)
		{
		printf("Error: Invalid argument rule for \"%s\" at line %d\n",key,line);
		printf(">>> %s\n --> %s",buffer,varSet);
		return -2;
		}

	printf("pass writeOut\n");

	/* Check if this key crete new nested */
	if(target == 'k' && strlen(pRule->postKey) > 0)
		{
		printf("*This one create new stack\n");
		/* Update stack */
		push(currentStack);
		strcpy(currentStack,pRule->postKey);
		*indentCount = *indentCount+1;

		printf("**newStack = %s newIndent = %d\n",currentStack,*indentCount);

		/* print bracket */
		writeIndent(pOut,*indentCount);
		fprintf(pOut, "{\n");
		}

	printf("Finish this line\n");
	return 1;
	}

/* Preparing argument for writing out
 *	Argument:	arg = Array of argument
 *				varSet = Set of variable pattern
 *				tempData = Temp data structure
 *	Return:	Number of variable, -1 if varSet is invalid
 */
int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData)
	{
	int i = 0;
	char* var = NULL;

	printf("prepareArg\n");
	printf("varSet: %s\n",varSet);

	/* Get each variable */
	var = strtok(varSet,",");

	while(var != NULL)
		{
		printf("arg %d : %s\n",i,var);
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
		var = strtok(NULL,",");
		}

	printf("count arg = %d\n",i);

	return i;
	}

/* Writing C statement into C file
 *	Argument:	arg = Array of argument
 *				printSet = C statement pattern
 *				count = number of argument
 				pOut = Pointer to output file
 *	Return:	1 if success, 0 if not
 */
int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut)
	{
	if(count == 0)
		{
		fprintf(pOut,"%s",printSet);
		}
	else if(count == 1)
		{
		fprintf(pOut,printSet,arg[0]);
		}
	else if(count == 2)
		{
		fprintf(pOut,printSet,arg[0],arg[1]);
		}
	else if(count == 3)
		{
		fprintf(pOut,printSet,arg[0],arg[1],arg[2]);
		}
	else if(count == 4)
		{
		fprintf(pOut,printSet,arg[0],arg[1],arg[2],arg[3]);
		}
	else
		{
		return 0;
		}

	fprintf(pOut, "\n");

	return 1;
	}

/* Write standard include function to file
 *	Argument:	pOut = Output file pointer
 *	Return: 1 if success, 0 if file open failed
 */
int writeStdFunction(FILE* pOut)
	{
	printf("writeStdFunction\n");
	FILE* pHeader = NULL;
	char buffer[128];

	/* Open standard header file */
	pHeader = fopen(stdHeaderFile,"r");

	if(pHeader == NULL)
		{
		return 0;
		}

	while(fgets(buffer,sizeof(buffer),pHeader) != NULL)
		{
		fprintf(pOut,"%s",buffer);
		}

	fprintf(pOut,"\n\n");

	return 1;
	}

/* Write standard indenting to file
 *	Argument:	pOut = Output file pointer
 */
void writeIndent(FILE* pOut,int indentCount)
	{
	int i;

	for (i = 0; i < indentCount; i++)
		{
		fprintf(pOut,"\t");
		}
	}

/* Clean-up the buffer 
 *	Argument:	buffer = Buffer to clean up
 */
void cleanBuffer(char buffer[])
	{
	int i = 0;

	/* Clean \n */
	if(buffer[strlen(buffer)-1] == '\n')
		{
		buffer[strlen(buffer)-1] = '\0';
		}

	/* Clean \t */
	while(buffer[i] == '\t')
		{
		i++;
		}

	sprintf(buffer,"%s",buffer+i);
	printf("inClean buffer = %s\n",buffer);
	}