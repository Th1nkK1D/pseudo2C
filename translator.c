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
void writeStdFunction(FILE* pOut);
void writeIndent(FILE* pOut);
int processLine(char buffer[],FILE* pOut,int line);
int prepareArg(char arg[4][12],char varSet[64],TEMP_T tempData);
int writeOut(char arg[4][12],char printSet[64],int count,FILE* pOut);

/* Global Variable */
static char currentStack[16];
static int indentCount = 0;

/* Translator from Pseudocode to C
 *	Return:	1 = Success
 *			0 = Error opening input/output file
 *			-1 = Preparing database failed
 */
int translator()
	{
	FILE* pIn = NULL;
	FILE* pOut = NULL;
	char buffer[256];
	char inName[32];
	char outName[32];
	int line = 0;

	/* Prepare rule file */
	if(prepareDB() != 1)
		{
		printf("Error preparing rule database\n");
		return -1;
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
	writeStdFunction(pOut);

	//push main
	fprintf(pOut,"int main()\n\t{\n");
	indentCount++;

	/* Read each line */
	while(fgets(buffer,sizeof(buffer),pIn) != NULL)
		{
		printf("Buffer read: %s\n",buffer);

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

	writeIndent(pOut);
	fprintf(pOut,"}");
	indentCount--;

	/* Close file */
	fclose(pIn);
	fclose(pOut);

	freeDB();

	printf("Translation Completed!\n");

	return 1;
	}

/* Write standard include function to file
 *	Argument:	pOut = Output file pointer
 */
void writeStdFunction(FILE* pOut)
	{
	printf("writeStdFunction\n");
	fprintf(pOut,"#include <stdio.h>\n");
	fprintf(pOut,"#include <stdlib.h>\n");
	fprintf(pOut,"#include <string.h>\n");
	fprintf(pOut,"\n");
	//To-Do : custom function
	}

/* Write standard indenting to file
 *	Argument:	pOut = Output file pointer
 */
void writeIndent(FILE* pOut)
	{
	int i;

	for (i = 0; i < indentCount; i++)
		{
		fprintf(pOut,"\t");
		}
	}

/* Translate a single line of pseudo code
 *	Argument:	buffer = Output file pointer
 *				pOut = Output file pointer
 *				line = number of input file current line
 *	Return:	-1 = Key not found
 *			0 = Data update error
 *			1 = Success	
 */
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
	int varCount;

	printf("processLine at line %d\n",line);

	/* Key = first word */
	sscanf(buffer,"%s",key);

	printf("Key read: %s\n",key);

	pRule = getRule('k',key);

	if(pRule == NULL)
		{
		printf("Error: Key not found at line %d\n",line);
		printf(">>> %s\n",buffer);

		return -1;
		}

	printf("Rule got: %s\n",pRule->name);

	/* Check if end nested found */
	if (strcmp(buffer,currentStack) == 0)
		{
		/* End nested (Old function) */
		writeIndent(pOut);
		fprintf(pOut,"}");

		/* Update stack */
		pop(currentStack);
		indentCount--;

		printf("Target = Post\n");
		printf("preVar: %s\n",pRule->preVar);
		printf("preOut: %s\n",pRule->preOut);

		/* Set data */
		strcpy(varSet,pRule->postVar);
		strcpy(printSet,pRule->postOut);
		}
	else
		{
		/* New function */
		printf("Target = Pre\n");		
		printf("preVar: %s\n",pRule->preVar);
		printf("preOut: %s\n",pRule->preOut);

		/* Set data */
		strcpy(varSet,pRule->preVar);
		strcpy(printSet,pRule->preOut);
		}

	/* Update temp data */
	if(dataUpdate(pRule,buffer,&tempData) == 0)
		{
		printf("dataUpdate Error");
		return 0;
		}

	printf("Data Update success\n");

	printf("varSet: %s\n",varSet);
	printf("printSet: %s\n",printSet);

	/* Prepare Argument */
	varCount = prepareArg(arg,varSet,tempData);
	writeIndent(pOut);
	writeOut(arg,printSet,varCount,pOut);


	/* Check if this key crete new nested */
	if(strlen(pRule->postKey) > 0)
		{
		/* Update stack */
		push(pRule->postKey);
		strcpy(currentStack,pRule->postKey);
		indentCount++;

		/* print bracket */
		fprintf(pOut, "\n");
		writeIndent(pOut);
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
	if(count == 1)
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
