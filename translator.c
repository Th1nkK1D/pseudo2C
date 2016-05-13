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
void cleanBuffer(char buffer[],int length);
int checkComment(int commentStatus,char buffer[],int length);
void freeAll();
void compileRun(char cName[]);

/* Static Variable */
const char stdHeaderFile[] = "stdHeader.in";

/* Translator from Pseudocode to C
 *	Return:	1 = Success
 *			0 = Failed
 */
int translator()
	{
	/* Variable Declaration */
	FILE* pIn = NULL;				/* Input pseudo file Pointer */
	FILE* pOut = NULL;				/* Output C file Pointer */
	char buffer[256];				/* Input buffer */
	char inName[32]; 				/* Input file name */
	char outName[32];				/* Output file name */
	int line = 0;					/* Line counter */
	char currentStack[16] = "main";	/* Current nested stack */
	int indentCount = 0;			/* Indent Counter*/
	int commentStatus = 0;			/* Status of comment */

	clearScr();

	/* Prepare rule file */
	if(prepareDB() != 1)
		{
		printf("Error preparing rule database\n");
		return 0;
		}

	/* Get input file name */
	do
		{
		printf("Input pseudocode file name : ");
		fgets(buffer,sizeof(buffer),stdin);
		sscanf(buffer,"%s",inName);
		}
	while(buffer[0] == '\n');

	/* Open input file */
	pIn = fopen(inName,"r");

	if(pIn == NULL)
		{
		printf("Error: Can't open pseudo code file: \"%s\"\n",inName);
		freeDB();
		return 0;
		}

	/* Get output file name */
	do
		{
		printf("Output C file name : ");
		fgets(buffer,sizeof(buffer),stdin);
		sscanf(buffer,"%s",outName);
		}
	while(buffer[0] == '\n');

	/* Open output file */
	pOut = fopen(outName,"w");

	if(pOut == NULL)
		{
		printf("Error: Can't create C file: \"%s\"\n",outName);
		freeDB();
		return 0;
		}

	printf("> Translation started\n");

	/* Write standard function */
	if(writeStdFunction(pOut) == 0)
		{
		printf("Error: Writing standard header and function failed\n");
		freeDB();
		return 0;
		}

	printf("> Write standard header completed\n");

	/* Open main function */
	fprintf(pOut,"/* Main function */\n");
	fprintf(pOut,"int main()\n");
	fprintf(pOut,"\t{\n");
	indentCount++;

	/* Read each line */
	while(fgets(buffer,sizeof(buffer),pIn) != NULL)
		{
		line++;
		
		/* Cleaning buffer */
		cleanBuffer(buffer,strlen(buffer));

		if(strlen(buffer) == 0)
			{
			/* Print blank line if blank line found */
			fprintf(pOut,"\n");
			}
		else
			{

			/* Check if it is a comment line */			
			commentStatus = checkComment(commentStatus,buffer,strlen(buffer));

			if(commentStatus > 0)
				{
				/* Comment found print the comment */
				writeIndent(pOut,indentCount);
				fprintf(pOut,"%s\n",buffer);
				}
			else
				{
				/* Process the line */
				if(processLine(buffer,pOut,line,currentStack,&indentCount) != 1)
					{
					/* Process line failed */
					printf("Translation aborted\n");
					freeAll();
					return 0;
					}
				}
			}
		}

	/* Check if all stack was end */
	if(strcmp(currentStack,"main") != 0)
		{
		printf("Error: postKey not found at line %d\n",line);
		printf(">>> -> %s\n",currentStack);
		
		return 0;
		}

	/* Close main function */
	writeIndent(pOut,indentCount);
	fprintf(pOut,"}");
	indentCount--;
	
	/* Free all data structure */
	freeAll();

	/* Close file */
	fclose(pIn);
	fclose(pOut);

	printf("Translation Completed!\n");
	
	/* If user want to compile and run */
	compileRun(outName);
	
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
	char key[16];			/* Key read */
	char keyChild[16];		/* Possible child key read */
	RULE_T* pRule = NULL;	/* Rule data of the key read */
	char target;			/* getKey target mode */
	TEMP_T tempData;		/* Temporary data for traslation */
	char inSet[64];			/* Expected pseudo for key read */
	char varSet[64];		/* Set of variable to print */
	char printSet[64];		/* Output c pattern to print */
	int varCount;			/* Number of argument to print  */
	char arg[4][12];		/* Array of argument value to print */

	/* Scan line for key and childKey */
	sscanf(buffer,"%s %s",key,keyChild);

	printf("> Line %d: %s\n",line,key);
	
	writeIndent(pOut,*indentCount);

	/* Check if end nested found */
	if (strncmp(buffer,"END",3) == 0)
		{
		/* Check if postKey match with currentStack */
		if(strcmp(buffer,currentStack) == 0)
			{
			/* Get rule by end key */
			target = 'e';
			pRule = getRule(target,key);
	
			if(pRule == NULL)
				{
				printf("Error: postKey not found at line %d\n",line);
				printf(">>> %s --> %s?\n",buffer,key);
	
				return 0;
				}
		
			/* End nested (close function) */
			fprintf(pOut,"}");
			
			/* Update Stack */
			*indentCount = *indentCount-1;
			pop(currentStack);
	
			/* Set data from rule */
			strcpy(inSet,pRule->postIn);
			strcpy(varSet,pRule->postVar);
			strcpy(printSet,pRule->postOut);
			}
		else
			{
			/* postKey doesn't match with currentStack */
			printf("Error: Invalid postKey at line %d\n",line);
			printf(">>> %s --> %s?",buffer,currentStack);
			
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
			fprintf(pOut,"%s ",pRule->preOut);
			
			/* Shift key and buffer */
			strcpy(buffer,buffer + strlen(key) + 1);
			strcpy(key,keyChild);
			
			/* Get rule from new key */
			pRule = getRule(target,key);

			if(pRule == NULL)
				{
				printf("Error: Key not found at line %d\n",line);
				printf(">>> %s --> %s?\n",buffer,key);
	
				return 0;
				}
			}

		/* Set data from rule */
		strcpy(inSet,pRule->preIn);
		strcpy(varSet,pRule->preVar);
		strcpy(printSet,pRule->preOut);
		}

	/* Update temp data */
	if(dataUpdate(pRule,buffer,&tempData) == 0)
		{
		printf("Error: Invalid Syntax at line %d\n",line);
		printf(">>> %s --> %s\n",buffer,inSet);
		return -1;
		}

	/* Prepare Argument */
	varCount = prepareArg(arg,varSet,tempData);

	/* Write to the C file */
	if(varCount < 0 || writeOut(arg,printSet,varCount,pOut) == 0)
		{
		printf("Error: Invalid argument rule for \"%s\" at line %d\n",key,line);
		printf(">>> %s --> %s\n",buffer,varSet);
		return -2;
		}

	/* Check if this key crete new nested */
	if(target == 'k' && strlen(pRule->postKey) > 0)
		{
		/* Update stack */
		push(currentStack);
		strcpy(currentStack,pRule->postKey);
		*indentCount = *indentCount+1;

		/* print open bracket */
		writeIndent(pOut,*indentCount);
		fprintf(pOut, "{\n");
		}

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
	int i = 0;			/* Argument counter */
	char* var = NULL;	/* Variable token */

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
	FILE* pHeader = NULL;	/* Header file pointer */
	char buffer[128];		/* Read buffer */

	/* Open standard header file */
	pHeader = fopen(stdHeaderFile,"r");

	if(pHeader == NULL)
		{
		return 0;
		}

	/* Print each line from header file */
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
	int i;	/* Counter */

	for (i = 0; i < indentCount; i++)
		{
		fprintf(pOut,"\t");
		}
	}

/* Clean-up the buffer 
 *	Argument:	buffer = Buffer to clean up
 */
void cleanBuffer(char buffer[],int length)
	{
	int i = 0;	/* Pre buffer counter */
	int j = 0;	/* Post buffer counter */
	
	if(buffer[length-1] == '\n')
		{
		buffer[length-1] = '\0';
		length--;
		}

	/* Count pre tab and space */
	while(buffer[i] == '\t' || buffer[i] == ' ')
		{
		i++;
		}
		
	/* Count post \n, tab and space */
	while(buffer[length-j-1] == '\t' || buffer[length-j-1] == ' ')
		{
		j++;
		}
		
	/* Set new string end point */
	buffer[length-j] = '\0';
	
	printf("Clean buffer: i=%d j=%d",i,j);

	sprintf(buffer,"%s",buffer+i);
	}

/* Check if this line is a comment
 *	Argument:	commentStatus = current status like return value
 *				buffer = input line to check
 *				length = length of input line
 *	Return:	0 = Not a comment line
 *			1 = A single-line comment
 *			2 = A pending muti-line comment
 */
int checkComment(int commentStatus,char buffer[],int length)
	{
	if(commentStatus == 2)
		{
		/* Comment is pending */
		if(buffer[length-2] == '*' && buffer[length-1] == '/')
			{
			return 1;	/* Multi line comment end point found */
			}
		else
			{
			return 2;	/* Comment still pending */
			}
		}
	else
		/* No comment pending */
		{
		if(strncmp(buffer,"//",2) == 0)
			{
			return 1;	/* Single line comment found */	
			}
		else if(strncmp(buffer,"/*",2) == 0)
			{
			/* Multi line comment start point found */
			if(buffer[length-2] == '*' && buffer[length-1] == '/')
				{
				return 1;	/* Multi line comment end point found */	
				}
			else
				{
				return 2;	/* Comment still pending */
				}
			}
		else
			{
			return 0;	/* No comment found */
			}	
		}
	}

/* Free all the data structure */
void freeAll()
	{
	freeVariable();
	freeFile();
	freeDB();
	}

/* Compile and run the translated C code if user want 
 *	Argument:	cName = Name of C file
 */
void compileRun(char cName[])
	{
	/* Variable Declaration */
	char buffer[64];	/* Input buffer */
	char action[12];	/* User action */
	char exeName[24];	/* Execute file name */
	char command[64];	/* System command */

	/* Get compile decision */
	printf("Do you want to compile %s now? (gcc is required) (Y) : ",cName);
	fgets(buffer,sizeof(buffer),stdin);
	sscanf(buffer,"%s",action);
	
	if(strcasecmp("Y",action) == 0)
		{
		/* Get execute file name f*/
		do
			{
			printf("Please enter exucute file name : ");
			fgets(buffer,sizeof(buffer),stdin);
			sscanf(buffer,"%s",exeName);
			}
		while(buffer[0] == '\n');
		
		/* Set command */
		sprintf(command,"gcc -o %s %s",exeName,cName);
		
		/* Run command */
		system(command);
		
		/* Get run decision */
		printf("Compiling completed!\n");
		printf("Do you want to run %s now? (Y) : ",exeName);
		fgets(buffer,sizeof(buffer),stdin);
		sscanf(buffer,"%s",action);
		
		if(strcasecmp("Y",action) == 0)
			{
			printf("Starting %s\n\n",exeName);
			
			/* Set command */
			sprintf(command,"./%s",exeName);
			
			/* Run command */
			system(command);
			}
		}
	}