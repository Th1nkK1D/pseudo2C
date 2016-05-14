#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mainStructure.h"
#include "globalAccess.h"
#include "checkMath.h"

/* Function to check type of data and store its type into string
 * Argument:
 * input => string that we want to check
 * type => string that will contain input's type after checking
 * Return :
 * 0 => if it's invalid type
 * 1 => if it's valid type and checking success
 */
int checkType(char input[], char type[])
	{
	int i = 0;
	VARIABLE_T* findVar = NULL;		/* store a structure of variable that we found in line */				

	findVar = searchWord(input);		/* find the variable that has name match with 'input' */

	/* if it's not a variable, we will find what type it is */
	if ( findVar == NULL )
		{
		/* if it doesn't have exactly two quotes (initial and terminal) then we know it's not a string or char */
		if ( input[0] != '\"' || input[strlen(input)-1] != '\"' )
			{
			/* if it has only one quote, return 0 */
			if ( input[0] != '\"' && input[strlen(input)-1] == '\"' )
				{
				printf("15\n");
				return 0;
				}
			else if ( input[0] == '\"' && input[strlen(input)-1] != '\"' )					
				{
				printf("16\n");
				return 0;
				}
			/* if it doesn't have any quote, we absolutely know that it must be an int or double or char */ 
			else
				{
				if ( input[0] == '\'' && input[strlen(input)-1] == '\'' )
					{
					strcpy(type,"char");
					}
				else if ( input[0] != '\'' && input[strlen(input)-1] == '\'' )
					{
					printf("17\n");
					return 0;
					}
				else if ( input[0] == '\'' && input[strlen(input)-1] != '\'' )
					{
					printf("18\n");
					return 0;
					}
				else
					{
					/* if it still has any alphabet or space then return 0 */
					for (i=0;i<strlen(input);i++)
						{
						if ( isalpha(input[i]) )
							{
							printf("input = %s\n",input);
							printf("19\n");
							return 0;
							}
						else if ( isspace(input[i]) )
							{
							printf("20\n");
							return 0;
							}
						/* if we found dot, we suddenly know it is a double */
						else if ( input[i] == '.' )
							{
							strcpy(type,"double");
							}
						}
					/* if it's nothing until now, it's an int */
					if ( strcasecmp(type,"double") != 0 )
						{
						strcpy(type,"int");
						}
					}
				}
			}
		/* if it has two quotes, we completely know that it's a string */
		else
			{
			strcpy(type,"string");
			}
		}
	/* if it's a variable, we can catch its type suddenly */
	else
		{
		strcpy(type,findVar->type);
		}
	return 1;
	}

/* function to check that condition is valid
 * Argument:
 * - input => string of condition
 * Return:
 * - 1 => if condition is ok
 * - 0 => if condition is not ok 
 */
int checkCondition ( char input[] , char con[])
	{
	char* pToken;					/* hold token from each times of strtok */
	char item[512];					/* hold each item for checking type process */
	char tempDelim[512];				/* temporary of string that has a space (we need to strtok 2 times) */
	char tempData[512];				/* hold a copy of condition (input) */
	char tempCon[512];				/* use to combine all sub coondition into one condition */
	char leftToken[512];				/* store the token before the operator ( in sub condition ) */
	char sign[512];					/* store the operator ( in sub condition ) */
	char rightToken[512];				/* store the token after the operator ( in sub condition ) */
	char type1[16];					/* handle type of the left token */
	char type2[16];					/* handle type of the right token */
	char* hold_input;				/* pointer to condition */
	int i = 0;

	memset(tempCon,0,sizeof(tempCon));
	memset(tempDelim,0,sizeof(tempDelim));

	strcpy(tempData,input);				/* copy input into temporary */
	hold_input = tempData;				/* pointer to temporary input */
	pToken = strtok_r(hold_input," ",&hold_input);	/* pop the first token */

	/* loop until doesn't have any token left */
	while ( pToken != NULL )
		{
		/* if it is string that has a space between itself, we must pop it again */
		if ( pToken[0] == '\"' && pToken[strlen(pToken)-1] != '\"')
			{
			strcat(tempDelim,pToken);
			strcat(tempDelim," ");

			/* if it doesn't have a quote anymore, return 0 */
			if ( strstr(hold_input,"\"") == NULL )
				{
				printf("5\n");
				return 0;
				}
			pToken = strtok_r(NULL,"\"",&hold_input);
			strcat(tempDelim,pToken);
			strcat(tempDelim,"\"");
			strcpy(item,tempDelim);		/* store the complete version of that string as item */
			memset(tempDelim,0,sizeof(tempDelim));
			}
		/* if it's not a string, we can copy it suddenly */
		else
			{
			strcpy(item,pToken);
			}
		memset(type1,0,sizeof(type1));
		memset(type2,0,sizeof(type2));

		/* send item to check its type */
		if ( checkType(item,type1) == 0 )
			{
			printf("6\n");
			return 0;
			}
		strcpy(leftToken,item);			/* if it's type is supported, we store it as a left token ( left of the sign ) */

		/* checking the middle token */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);
		if ( pToken == NULL )
			{
			printf("7\n");
			return 0;
			}	
		
		/* if it's not a valid sign, return 0 */
		if ( strcasecmp(pToken,">") != 0 && strcasecmp(pToken,"<") != 0 && strcasecmp(pToken,"==") != 0 && strcasecmp(pToken,"!=") != 0 && strcasecmp(pToken,">=") != 0 && strcasecmp(pToken,"<=") != 0 )
			{
			printf("7\n");
			return 0;
			}
		strcpy(sign,pToken);

		/* checking third token, same as the first token */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);
		if ( pToken == NULL )
			{
			printf("8\n");
			return 0;
			}
		/* if it is string that has a space between itself, we must pop it again */
		if ( pToken[0] == '\"' && pToken[strlen(pToken)-1] != '\"' )
			{
			strcat(tempDelim,pToken);
			strcat(tempDelim," ");

			/* if it doesn't have a quote anymore, return 0 */
			if ( strstr(hold_input,"\"") == NULL )
				{
				printf("9\n");
				return 0;
				}

			pToken = strtok_r(NULL,"\"",&hold_input);
			strcat(tempDelim,pToken);
			strcat(tempDelim,"\"");
			strcpy(item,tempDelim);			/* store the complete version of that string as item */
			memset(tempDelim,0,sizeof(tempDelim));
			}
		/* if it's not a string, we can copy it suddenly */
		else
			{
			strcpy(item,pToken);
			}
		if ( checkType(item,type2) == 0 )
			{
			printf("10\n");
			return 0;
			}
		strcpy(rightToken,item);			/* store it as right token ( right of the sign ) */

		/* if type of the two data is not the same ( left token and right token ) , return 0 */
		/* we check only char and string because int can be compared with double */
		if ( strcasecmp(type1,"int") != 0 && strcasecmp(type1,"double") != 0 && strcasecmp(type2,"int") != 0 && strcasecmp(type2,"double") != 0 )
			{
			if ( strcasecmp(type1,type2) != 0 )
				{
				printf("11\n");
				return 0;
				}
			}
		/* if it's a string comparison, we must add "strcmp" to prepare for writing to output file */
		if ( strcasecmp(type1,"string") == 0 )
			{
			strcat(tempCon,"strcmp(");
			strcat(tempCon,leftToken);
			strcat(tempCon,",");
			strcat(tempCon,rightToken);
			strcat(tempCon,") ");
			strcat(tempCon,sign);
			strcat(tempCon," 0");
			}
		/* if not, we can store it as a temporary condition suddenly */
		else
			{
			strcat(tempCon,leftToken);
			strcat(tempCon," ");
			strcat(tempCon,sign);
			strcat(tempCon," ");
			strcat(tempCon,rightToken);
			}

		/* pop the next token, it must be && or || */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);

		if ( pToken != NULL )
			{
			if ( strcasecmp(pToken,"||") != 0 && strcasecmp(pToken,"&&") != 0 )
				{
				printf("12\n");
				return 0;
				}
			else
				{
				strcat(tempCon," ");
				strcat(tempCon,pToken);
				strcat(tempCon," ");
				}
			}
		pToken = NULL;	
		pToken = strtok_r(NULL," ",&hold_input);
		}
	strcpy(con,tempCon);			/* store tempCon as a fully condition */
	return 1;
	}

/* function to check that variable name for each command is valid
 * Arguments:
 * - tempLine -> name that we want to check
 * - command -> command (function) in c ( in some command, variable name can be a string
 * - varType -> type of that variable that the command requires
 * Return:
 * - 1 if variable is supported by command
 * - 0 if it's not supported by command
 */
int checkName ( char tempLine[] , char command[] , char varType[] )
	{
	VARIABLE_T* tempVar = NULL;			/* to find if it's a variable */
	int i = 0;
	char type[512];					/* store its type if it's a variable */ 

	tempVar = searchWord(tempLine);			/* search for a variable */

	/* if it's not a variable but the command requires a variable, return 0 */
	if ( tempVar == NULL )
		{
		/* the command which do not require a variable are "print" and "write" */
		if ( strcasecmp(command,"print") != 0 && strcasecmp(command,"write") != 0 )
			{
			printf("Error - variable is undeclared (first use in this function)\n");
			return 0;
			}
		/* if it's not covered by two quotes, return 0 */
		if ( tempLine[0] != '\"' || tempLine[strlen(tempLine)-1] != '\"' )
			{
			printf("Error - variable or string not found\n");
			return 0;
			}
		}

	/* if it's a variable, check that its type is supported by command */
	else
		{
		sprintf(type,"%c",tolower(tempVar->type[0]));

		if ( strstr(varType,type) == NULL )
			{
			printf("Error - this variable is not in support type\n");
			return 0;
			}	
		}
	return 1;		
	}

/* function to store line from user into a temporary data for ( divide each word to each slot of argument )
 * Arguments:
 * - rule -> rule for that line
 * - input -> line that want to store in temporary data
 * - data -> an empty structure for storing line
 * Return:
 * 1 if updating data success
 * 0 if not
 */  
int dataUpdate ( RULE_T* rule, char input[], TEMP_T* data )
	{
	RULE_T* tempRule = NULL;			/* store temporary of rule */
	char command[256];				/* store the first string as a command */
	char line[512];					/* store temporary of line */
	char pre_post_in[256];				/* store temporary of prein/postin */
	char* tempFormat;				/* hold each token of prein/postin */
	char* tempLine;					/* hold each token of line */
	char lineCondition[512];			/* hold the condition for checking */
	char* hold_format = NULL;			/* pointer to prein/postin */
	char* hold_line = NULL;				/* pointer to line */				
	int bFormat = 0;				/* boolean to check format */
	int bName = 0;					/* boolean to check name */
	VARIABLE_T* tempVar = NULL;			/* store temporary of variable */
	FILE_T* tempFile = NULL;			/* store temporary of pointer to file */
	int bCondition = 0;				/* boolean to check condition */
	char tempString[512];				/* temporary for string that has a space */
	char* delim = NULL;				/* delimiter that separate between command and data */
	int bFree = 0;					/* boolean to check that we need to free ( strdup is used ) */
	int i = 0;	
	printf("input = %s\n",input);
	printf("ENTER\n");

	tempRule = rule;
	strcpy(command,input);


	memset(data->condition,0,sizeof(data->condition));
	memset(data->varType,0,sizeof(data->condition));
	memset(data->varName,0,sizeof(data->condition));
	memset(data->varSymbol,0,sizeof(data->condition));
	memset(data->value,0,sizeof(data->condition));
	memset(data->increm,0,sizeof(data->condition));
	memset(data->filePointer,0,sizeof(data->condition));
	memset(data->filePath,0,sizeof(data->condition));
	memset(data->fileMode,0,sizeof(data->condition));
	memset(pre_post_in,0,sizeof(pre_post_in));
	memset(lineCondition,0,sizeof(lineCondition));
	memset(tempString,0,sizeof(tempString));
	printf("C0\n");

	
	printf("C0.1\n");
	
	printf("C0.2\n");
	printf("input = %s\n",input);
	printf("command = %s\n",command);
	/* separate command and line */
	delim = strpbrk(command," ");
	printf("DELIM = %s\n",delim);
	printf("COMMAND = %s\n",command);
	printf("C0.3\n");
	if ( delim == NULL )
		{
		return 0;
		}
	printf("C1\n");

	*delim = '\0';
	printf("C2\n");
	strcpy(line,delim+1);	
	printf("C3\n");			

	if ( strlen(tempRule->preIn) != 0 )
		{
		strcpy(pre_post_in,tempRule->preIn);
		}
	else
		{
		strcpy(pre_post_in,tempRule->postIn);
		}

	printf("C4\n");

	hold_format = pre_post_in;
	hold_line = line;
	printf("C5\n");
	if ( strcasecmp("variable",command) == 0 )
		{
		printf("C6\n");
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			printf("C7\n");
			bName = 0;

			if ( tempFormat[0] == '$' )
				{
				if ( strcasecmp("$varName",tempFormat) == 0 )
					{
					tempVar = NULL;
					tempVar = searchWord(tempLine);
					if ( tempVar != NULL )
						{
						printf("Error - this variable is existing\n");
						return 0;
						}
					if ( isdigit(tempLine[0]) )
						{
						printf("Error - cannot begin a variable name with a digit.\n");
						return 0;
						}
					else if ( isupper(tempLine[0]) )
						{
						printf("Error - cannot begin a variable name with an uppercase\n");
						return 0;
						}
					else if ( isspace(tempLine[0]) )
						{
						printf("Error - cannot begin a variable name with a space\n");
						return 0;
						}
					strcpy(data->varName,tempLine);
					}
				else if ( strcasecmp("$varType",tempFormat) == 0 )
					{
					printf("C8\n");
					if ( strcasecmp(tempLine,"int") == 0 )
						{						
						strcpy(data->varType,tempLine);
						}
					else if ( strcasecmp(tempLine,"char") == 0 )
						{
						strcpy(data->varType,tempLine);
						}
					else if ( strcasecmp(tempLine,"double") == 0 )
						{
						strcpy(data->varType,tempLine);
						}
					else if ( strcasecmp(tempLine,"string") == 0 )
						{
						printf("C9\n");
						strcpy(data->varType,tempLine);
						}
					else
						{
						printf("Error - type of variable now support [ int / char / string / double ]\n");
						return 0;
						}
					printf("C10\n");
					}
				printf("C11\n");
				}
			else
				{
				if ( strcasecmp(tempFormat,tempLine) != 0 )
					{
					printf("Error - incorrect format\n");
					return 0;
					}
				}
			printf("C12\n");
			}
		printf("C13\n");
		addVariable(data->varName,data->varType);
		printf("C14\n");
		if ( strcasecmp(data->varType,"string") == 0 )
			{
			printf("C15\n");
			strcpy(data->varType,"char");
			strcat(data->varName,"[256]");
			}
		printf("C16\n");
		}

	else if ( strcasecmp("open",command) == 0 )
		{
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			tempFile = NULL;

			if ( tempFormat[0] == '$' )
				{
				if ( strcasecmp("$f_path",tempFormat) == 0 )
					{
					tempFile = searchFile(tempLine);
					if ( tempFile != NULL )
						{
						printf("Error - this file is opening\n");
						return 0;
						}
					strcpy(data->filePath,tempLine);
					}
				else if ( strcasecmp("$f_mode",tempFormat) == 0 )
					{
					if ( strcasecmp(tempLine,"read") == 0 )
						{
						strcpy(data->fileMode,"r");
						}
					else if ( strcasecmp(tempLine,"write") == 0 )
						{
						strcpy(data->fileMode,"w");
						}
					else
						{
						printf("Error - mode of file now support [ read / write ]\n");
						return 0;
						}
					}
				}
			else
				{
				if ( strcasecmp(tempFormat,tempLine) != 0 )
					{
					printf("Error - incorrect format\n");
					return 0;
					}
				}
			}
		addFile(data->filePath,data->fileMode,data->filePointer);
		}

	else
		{
		tempFormat = strtok_r(hold_format," ",&hold_format);
		if ( strcasecmp(tempFormat,"$condition") != 0 )
			{
			tempLine = strtok_r(hold_line," ",&hold_line);
			if ( tempLine[0] == '\"' && tempLine[strlen(tempLine)-1] != '\"' )
				{
				memset(tempString,0,sizeof(tempString));
				strcat(tempString,tempLine);
				if ( strstr(hold_line,"\"") == NULL )
					{
					printf("1\n");
					printf("Error - condition is invalid\n");
					return 0;
					}
				tempLine = strtok_r(NULL,"\"",&hold_line);
				if ( tempLine != NULL )	
					{
					strcat(tempString," ");
					strcat(tempString,tempLine);
					strcat(tempString,"\"");
					tempLine = strdup(tempString);
					bFree = 1;
					memset(tempString,0,sizeof(tempString));
					}
				}
			}
		while ( tempFormat != NULL )
			{
			if ( tempFormat[0] == '$' )
				{
				if ( strcasecmp("$condition",tempFormat) == 0 )
					{
					memset(lineCondition,0,sizeof(lineCondition));
					tempLine = strtok_r(NULL," ",&hold_line);			
					while ( tempLine != NULL )
						{
						if ( tempLine[0] == '\"' && tempLine[strlen(tempLine)-1] != '\"')
							{
							strcat(tempString,tempLine);
							if ( strstr(hold_line,"\"") == NULL )
								{	
								printf("4\n");
								printf("Error - condition is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);	
									}
								return 0;
								}
							tempLine = strtok_r(NULL,"\"",&hold_line);
							if ( tempLine == NULL )
								{
								printf("3\n");
								printf("Error - condition is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							if ( tempLine != NULL )	
								{
								strcat(tempString," ");
								strcat(tempString,tempLine);
								strcat(tempString,"\"");
								}
							strcat(lineCondition,tempString);
							memset(tempString,0,sizeof(tempString));
							}
						else
							{
							strcat(lineCondition,tempLine);
							}
						tempLine = strtok_r(NULL," ",&hold_line);
						if ( tempLine != NULL )
							{
							strcat(lineCondition," ");
							}
						}
					
					bCondition = 0;
					bCondition = checkCondition(lineCondition,data->condition);
					
					if ( bCondition != 1 )
						{
						printf("2\n");
						printf("Error - condition is invalid\n");
						if ( bFree == 1 )
							{
							free(tempLine);
							}
						return 0;
						}
					}
				else if ( strcasecmp("$varName",tempFormat) == 0 )
					{
					bName = 0;
					bName = checkName(tempLine,command,tempRule->varType);

					if ( bName != 1 )
						{
						if ( bFree == 1 )
							{
							free(tempLine);
							}
						return 0;
						}
					strcpy(data->varName,tempLine);

					tempVar = NULL;
					tempVar = searchWord(data->varName);
					if ( tempVar == NULL )
						{
						
						strcpy(data->varSymbol,"%s");
						}
					else
						{
						strcpy(data->varType,tempVar->type);
						if ( strcasecmp(data->varType,"int") == 0 )
							{
							strcpy(data->varSymbol,"%d");
							}
						else if ( strcasecmp(data->varType,"char") == 0 )
							{
							strcpy(data->varSymbol,"%c");
							}
						else if ( strcasecmp(data->varType,"double") == 0 )
							{
							strcpy(data->varSymbol,"%lf");
							}
						else
							{
							strcpy(data->varSymbol,"%s");
							}
						}
					strcat(data->increm,data->varName);
					strcat(data->increm,"++");			
					}
				else if ( strcasecmp("$value",tempFormat) == 0 )
					{
					tempVar = searchWord(tempLine);

					if ( tempVar == NULL )
						{
						if ( strcasecmp(command,"SETSTRING") == 0 )
							{
							if ( tempLine[0] != '\"' || tempLine[strlen(tempLine)-1] != '\"' )
								{
								printf("Error - this data must be a string\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						else if ( strcasecmp(data->varType,"int") == 0 || strcasecmp(data->varType,"double") == 0 )
							{
							if ( checkMath(tempLine,strlen(tempLine)) == 0 )
								{
								printf("Error - this value is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						else if ( strcasecmp(data->varType,"char") == 0 )
							{
							if ( strlen(tempLine) != 1 )
								{
								printf("Error - this data must be one character\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}							
						}
					else
						{
						if ( strcasecmp(tempVar->type,"int") != 0 && strcasecmp(tempVar->type,"double") != 0 && strcasecmp(data->varType,"int") != 0 && strcasecmp(data->varType,"double") != 0 )
							{
							if ( strcasecmp(tempVar->type,data->varType) != 0 )
								{
								printf("Error - type of value is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						}
					strcpy(data->value,tempLine);							
					}
				else if ( strcasecmp("$f_path",tempFormat) == 0 )
					{
					tempFile = NULL;
					tempFile = searchFile(tempLine);

					if ( tempFile == NULL )
						{
						printf("Error - file is undeclared or deleted\n");
						if ( bFree == 1 )
							{
							free(tempLine);
							}
						return 0;
						}
					else
						{
						if ( strcasecmp(command,"read") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						else if ( strcasecmp(command,"write") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"w") != 0 )
								{
								printf("Error - this file is not in the write mode\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						else if ( strcasecmp(command,"getline") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							}
						else if ( strcasecmp(command,"close") == 0 )
							{
							strcpy(data->fileMode,tempFile->mode);
							strcpy(data->filePointer,tempFile->handle);
							deleteFile(tempLine);
							}
						}
					if ( strcasecmp(command,"close") != 0 )
						{
						strcpy(data->filePath,tempLine);
						strcpy(data->filePointer,tempFile->handle);
						}
					}
				}
			else
				{
				if ( strcasecmp(tempFormat,tempLine) != 0 )
					{
					printf("Error - incorrect format\n");
					if ( bFree == 1 )
						{
						free(tempLine);
						}
					return 0;
					}
				}
			tempFormat = strtok_r(NULL," ",&hold_format);
			if ( tempFormat != NULL )
				{
				if ( strcmp(tempFormat,"$condition") != 0 )
					{
					tempLine = strtok_r(NULL," ",&hold_line);
					}
				}
			}
		}
	printf("C17\n");
	tempLine = strtok_r(NULL," ",&hold_line);
	printf("C18\n");
	if ( tempLine != NULL )
		{
		printf("C19\n");
		printf("Error - this line is not in the correct format\n");
		if ( bFree == 1 )
			{
			printf("C20\n");
			free(tempLine);
			}
		return 0;
		}
	printf("C21\n");
	for ( i=0;i<strlen(data->varType);i++ )
		{
		data->varType[i] = tolower(data->varType[i]);
		}
	printf("C22\n");
	if ( bFree == 1 )
		{
		free(tempLine);
		}
	printf("data name = %s\n",data->varName);
	printf("data type = %s\n",data->varType);
	printf("C23\n");
	return 1;
	}
