#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mainStructure.h"
#include "globalAccess.h"
#include "checkMath.h"

/* Function to find dollar sign
 * Argument :
 * input => string that we want to look
 * Return :
 * 1 => if it has a dollar sign
 * 0 => if not
 */
int findDollar (char input[])
	{
	int i = 0;
	for (i=0;i<strlen(input);i++)
		{
		if ( input[i] == '$' )
			{
			return 1;
			}
		}
	return 0;
	}

/* Function to check type of data and store its type into string
 * Argument:
 * input => string that we want to check
 * type => string that will contain input's type
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
				printf("22");
				return 0;
				}
			else if ( input[0] == '\"' && input[strlen(input)-1] != '\"' )					
				{
				printf("33");
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
					printf("44");
					return 0;
					}
				else if ( input[0] == '\'' && input[strlen(input)-1] != '\'' )
					{
					printf("55");
					return 0;
					}
				else
					{
					/* if it still has any alphabet or space then return 0 */
					for (i=0;i<strlen(input);i++)
						{
						if ( isalpha(input[i]) )
							{
							printf("66");
							return 0;
							}
						else if ( isspace(input[i]) )
							{
							printf("77");
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
	int i = 0;
	char tempCon[512];				/* use to combine all sub coondition into one condition */
	char leftToken[512];				/* store the token before the operator ( in sub condition ) */
	char sign[512];					/* store the operator ( in sub condition ) */
	char rightToken[512];				/* store the token after the operator ( in sub condition ) */
	char type1[16];					/* handle type of the left token */
	char type2[16];					/* handle type of the right token */
	char* hold_input;				/* pointer to condition */

	memset(tempCon,0,sizeof(tempCon));
	memset(tempDelim,0,sizeof(tempDelim));
	strcpy(tempData,input);
	hold_input = tempData;
	pToken = strtok_r(hold_input," ",&hold_input);
	while ( pToken != NULL )
		{
		if ( pToken[0] == '\"' && pToken[strlen(pToken)-1] != '\"')
			{
			strcat(tempDelim,pToken);
			strcat(tempDelim," ");
			if ( strstr(hold_input,"\"") == NULL )
				{
				printf("m1\n");
				return 0;
				}
			pToken = strtok_r(NULL,"\"",&hold_input);
			strcat(tempDelim,pToken);
			strcat(tempDelim,"\"");
			strcpy(item,tempDelim);
			printf("token 1 = %s\n",item);
			memset(tempDelim,0,sizeof(tempDelim));
			}
		else
			{
			strcpy(item,pToken);
			printf("token 2 = %s\n",item);
			}
		memset(type1,0,sizeof(type1));
		memset(type2,0,sizeof(type2));

		if ( checkType(item,type1) == 0 )
			{
			printf("m2\n");
			return 0;
			}
		strcpy(leftToken,item);
		printf("HOLD in = %s\n",hold_input);
		/* checking the middle token */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);
		printf("EDEL = %s\n",pToken);
		if ( pToken == NULL )
			{
			printf("m3\n");
			return 0;
			}	
		
		/* if it's not a valid sign, return 0 */
		if ( strcasecmp(pToken,">") != 0 && strcasecmp(pToken,"<") != 0 && strcasecmp(pToken,"==") != 0 && strcasecmp(pToken,"!=") != 0 && strcasecmp(pToken,">=") != 0 && strcasecmp(pToken,"<=") != 0 )
			{
			printf("m4\n");
			return 0;
			}
		strcpy(sign,pToken);

		/* checking third token, same as the first token */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);
		if ( pToken == NULL )
			{
			printf("m5\n");
			return 0;
			}	
		if ( pToken[0] == '\"' && pToken[strlen(pToken)-1] != '\"' )
			{
			printf("p3\n");
			strcat(tempDelim,pToken);
			strcat(tempDelim," ");
			if ( strstr(hold_input,"\"") == NULL )
				{	
				printf("m6\n");
				return 0;
				}
			pToken = strtok_r(NULL,"\"",&hold_input);
			strcat(tempDelim,pToken);
			strcat(tempDelim,"\"");
			strcpy(item,tempDelim);
			memset(tempDelim,0,sizeof(tempDelim));
			}
		else
			{
			strcpy(item,pToken);
			}
		printf("TOKEN 2 == %s\n",item);
		if ( checkType(item,type2) == 0 )
			{
			printf("m7\n");
			return 0;
			}
		/* if type of the two data in condition is not the same, return 0 */
		if ( strcasecmp(type1,"int") != 0 && strcasecmp(type1,"double") != 0 && strcasecmp(type2,"int") != 0 && strcasecmp(type2,"double") != 0 )
			{
			if ( strcasecmp(type1,type2) != 0 )
				{
				printf("type1 = %s\n",type1);
				printf("type2 = %s\n",type2);
				printf("m8\n");
				return 0;
				}
			}

		strcpy(rightToken,item);

		printf("lefTOKEN = %s\n",leftToken);
		printf("rightTOKEN = %s\n",rightToken);

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
		else
			{
			strcat(tempCon,leftToken);
			strcat(tempCon," ");
			strcat(tempCon,sign);
			strcat(tempCon," ");
			strcat(tempCon,rightToken);
			}
		printf("tempCon = %s\n",tempCon);

		/* pop the next token, it must be && or || */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);

		if ( pToken != NULL )
			{
			if ( strcasecmp(pToken,"||") != 0 && strcasecmp(pToken,"&&") != 0 )
				{
				printf("m9\n");
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
	strcpy(con,tempCon);
	return 1;
	}

int checkName ( char tempLine[] , char command[] , char varType[] )
	{
	VARIABLE_T* tempVar = NULL;
	int i = 0;
	char type[512];

	tempVar = searchWord(tempLine);

	if ( tempVar == NULL )
		{
		if ( strcasecmp(command,"print") != 0 && strcasecmp(command,"write") != 0 )
			{
			printf("Error - variable is undeclared (first use in this function)\n");
			return 0;
			}
		if ( tempLine[0] != '\"' || tempLine[strlen(tempLine)-1] != '\"' )
			{
			printf("Error - variable or string not found\n");
			return 0;
			}
		}
	else
		{
		sprintf(type,"%c",tolower(tempVar->type[0]));

		if ( strstr(varType,type) == NULL )
			{
			printf("t1 = %c, t2 = %s\n",varType[0],type);
			printf("Error - this variable is not in supported type\n");
			return 0;
			}	
		}
	return 1;		
	}

int dataUpdate ( RULE_T* rule, char input[], TEMP_T* data )
	{
	RULE_T* tempRule = NULL;			/* store temporary of rule */
	char command[256];				/* store the first string as a command */
	char line[512];					/* store temporary of line */
	char pre_post_in[256];				/* store temporary of prein/postin */
	char* tempFormat;				/* hold each token of prein/postin */
	char* tempLine;					/* hold each token of line */
	char lineCondition[512];			/* store condition for checking */
	char* hold_format = NULL;			/* pointer to prein/postin */
	char* hold_line = NULL;				/* pointer to line */
	int foundDollar = 0;				/* boolean to check it's a variable in structure */				
	int bFormat = 0;				/* boolean to check format */
	int bName = 0;					/* boolean to check name */
	VARIABLE_T* tempVar = NULL;			/* store temporary of variable */
	FILE_T* tempFile = NULL;			/* store temporary of pointer to file */
	int bCondition = 0;				/* boolean to check condition */
	char* delim = NULL;				/* break between command and line */
	char tempString[512];				/* temporary of string that has a space ( need to strtok 2 times ) */
	int bFree = 0;					/* boolean to check that strdup is used */
	int i = 0;	

	memset(data->condition,0,sizeof(data->condition));
	memset(data->varName,0,sizeof(data->varName));
	memset(data->varType,0,sizeof(data->varType));
	memset(data->varSymbol,0,sizeof(data->varSymbol));
	memset(data->value,0,sizeof(data->value));
	memset(data->increm,0,sizeof(data->increm));
	memset(data->filePointer,0,sizeof(data->filePointer));
	memset(data->filePath,0,sizeof(data->filePath));
	memset(data->fileMode,0,sizeof(data->fileMode));
	memset(tempString,0,sizeof(tempString));
	memset(line,0,sizeof(line));
	memset(command,0,sizeof(command));
	memset(pre_post_in,0,sizeof(pre_post_in));
	memset(lineCondition,0,sizeof(lineCondition));

	printf("start\n");

	tempRule = rule;
	strcpy(command,input);

	printf("A\n");
	
	delim = strpbrk(command," ");
	printf("B\n");
	if ( delim == NULL )
		{
		printf("C\n");
		return 1;
		}
	printf("C.D\n");
	*delim = '\0';
	strcpy(line,delim+1);

	printf("D\n");

	if ( strlen(tempRule->preIn) != 0 )
		{
		printf("E\n");
		strcpy(pre_post_in,tempRule->preIn);
		}
	else
		{
		printf("F\n");
		strcpy(pre_post_in,tempRule->postIn);
		}

	//bFormat = checkFormat(pre_post_in,line,command);

	//if ( bFormat != 1 )
		//{
		//printf("Error - incorrect format\n");
		//return 0;
		//}
	printf("G\n");
	hold_format = pre_post_in;
	hold_line = line;
	printf("H\n");
	if ( strcasecmp("variable",command) == 0 )
		{
		printf("D1\n");
		tempFormat = strtok_r(hold_format," ",&hold_format);
		tempLine = strtok_r(hold_line," ",&hold_line);
		printf("D2\n");
		while ( tempFormat != NULL )
			{
			if ( tempLine == NULL )
				{
				printf("Error - missing argument for this command\n");
				return 0;
				}
			printf("D3\n");
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			bName = 0;
			printf("D4\n");
			if ( tempFormat[0] == '$' )
				{
				printf("D5\n");
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
						strcpy(data->varType,tempLine);
						}
					else
						{
						printf("Error - type of variable now support [ int / char / string / double ]\n");
						return 0;
						}
					}
				}
			else
				{
				if ( strcasecmp(tempFormat,tempLine) != 0 )
					{
					printf("Error - incorrect format1\n");
					return 0;
					}
				}
			tempFormat = strtok_r(NULL," ",&hold_format);
			tempLine = strtok_r(NULL," ",&hold_line);
			}
		addVariable(data->varName,data->varType);
		if ( strcasecmp(data->varType,"string") == 0 )
			{
			strcpy(data->varType,"char");
			strcat(data->varName,"[256]");
			}
		}

	else if ( strcasecmp("open",command) == 0 )
		{
		tempFormat = strtok_r(hold_format," ",&hold_format);
		tempLine = strtok_r(hold_line," ",&hold_line);

		while ( tempFormat != NULL )
			{
			if ( tempLine == NULL )
				{
				printf("Error - missing argument for this command\n");
				return 0;
				}
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			tempFile = NULL;

			if ( tempFormat[0] == '$' )
				{
				if ( strcasecmp("$filePath",tempFormat) == 0 )
					{
					tempFile = searchFile(tempLine);
					if ( tempFile != NULL )
						{
						printf("Error - this file is opening\n");
						return 0;
						}
					strcpy(data->filePath,tempLine);
					}
				else if ( strcasecmp("$fileMode",tempFormat) == 0 )
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
					printf("Error - incorrect format3\n");
					return 0;
					}
				}
			tempFormat = strtok_r(NULL," ",&hold_format);
			tempLine = strtok_r(NULL," ",&hold_line);
			}
		addFile(data->filePath,data->fileMode,data->filePointer);
		}

	else
		{
		printf("I\n");
		tempFormat = strtok_r(hold_format," ",&hold_format);
		printf("J\n");
		printf("tempFormat === %s\n",tempFormat);
		if ( strcasecmp(tempFormat,"$condition") != 0 )
			{
			printf("K\n");
			tempLine = strtok_r(hold_line," ",&hold_line);
			printf("L\n");
			if ( tempLine[0] == '\"' && tempLine[strlen(tempLine)-1] != '\"' )
				{
				printf("tempLinee = %s\n",tempLine);
				printf("point 0.85\n");
				memset(tempString,0,sizeof(tempString));
				strcat(tempString,tempLine);
				printf("tempString = %s\n",tempString);
				printf("point 0.90\n");
				if ( strstr(hold_line,"\"") == NULL )
					{
					printf("11\n");
					printf("Error - condition is invalid\n");
					return 0;
					}
				tempLine = strtok_r(NULL,"\"",&hold_line);
				printf("holdlin = %s\n",hold_line);
				printf("point 0.950\n");
				printf("HOL = %s\n",hold_line);
				if ( tempLine != NULL )	
					{
					printf("HD = %s\n",hold_line);
					printf("point 1ja\n");
					strcat(tempString," ");
					//sprintf(tempString,"%s%s",tempString,tempLine);
					strcat(tempString,tempLine);
					strcat(tempString,"\"");
					printf("tempString2 = %s\n",tempString);
					printf("point 2\n");
					tempLine = strdup(tempString);
					bFree = 1;
					//strcpy(tempLine,tempString);
					printf("point 3\n");
					memset(tempString,0,sizeof(tempString));
					printf("H %s\n",hold_line);
					}
				printf("HL %s\n",hold_line);
				}
			printf("HLL %s\n",hold_line);
			}
		
		printf("HLLLLL %s\n",hold_line);
		while ( tempFormat != NULL )
			{
			if ( strcasecmp(tempFormat,"$condition") != 0 && (tempLine == NULL ) )
				{
				printf("Error - missing argument for this command\n");
				return 0;
				}
			printf("tempFormat = %s.\n",tempFormat);
			printf("tempLine = %s.\n",tempLine);
			printf("A1\n");
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);

			if ( tempFormat[0] == '$' )
				{
				if ( strcasecmp("$condition",tempFormat) == 0 )
					{
					printf("A2\n");
					memset(lineCondition,0,sizeof(lineCondition));
					tempLine = strtok_r(NULL," ",&hold_line);
					if ( tempLine == NULL )
						{
						printf("Error - missing argument for this command\n");
						return 0;
						}
					printf("TMP LN = %s\n",tempLine);				
					while ( tempLine != NULL )
						{
						if ( tempLine[0] == '\"' && tempLine[strlen(tempLine)-1] != '\"')
							{
							strcat(tempString,tempLine);
							printf("temppp = %s\n",tempString);
							if ( strstr(hold_line,"\"") == NULL )
								{	
								printf("Error - condition is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);	
									}
								return 0;
								}
							tempLine = strtok_r(NULL,"\"",&hold_line);
							printf("TEMPPP = %s\n",tempLine);
							if ( tempLine == NULL )
								{
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
								printf("tempS = %s\n",tempString);
								}
							printf("tempSTR = %s\n",tempString);
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
					printf("L C is %s\n",lineCondition);
					bCondition = checkCondition(lineCondition,data->condition);
					
					if ( bCondition != 1 )
						{
						printf("type is %s\n",data->varType);
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
					printf("tempLine = %s\n",tempLine);

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
						strcpy(data->varType,"string");
						}
					else
						{
						strcpy(data->varType,tempVar->type);
						printf("VARTYPE is %s\n",data->varType);
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
						printf("type is %s\n",data->varType);
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
							printf("AA\n");
							if ( checkMath(tempLine,strlen(tempLine)) == 0 )
								{
								printf("BB\n");
								printf("Error - this value is invalid\n");
								if ( bFree == 1 )
									{
									free(tempLine);
									}
								return 0;
								}
							printf("CC\n");
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
						printf("AA2\n");
						}
					else
						{
						printf("AA8\n");
						if ( strcasecmp(data->varType,"char") == 0 || strcasecmp(data->varType,"string") == 0 || strcasecmp(tempVar->type,"char") == 0 || strcasecmp(tempVar->type,"string") == 0 )
							{
							printf("tempV type+ = %s\n",tempVar->type);
							printf("type+ = %s\n",data->varType);
							printf("AA8\n");
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
						printf("AA9\n");
						}
					printf("type = %s\n",data->varType);
					strcpy(data->value,tempLine);
					printf("AA3\n");							
					}
				else if ( strcasecmp("$filePath",tempFormat) == 0 )
					{
					tempFile = NULL;
					tempFile = searchFile(tempLine);
					printf("search %s in temp line\n",tempLine);

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
				printf("AA4\n");
				}
			else
				{
				if ( strcasecmp(tempFormat,tempLine) != 0 )
					{
					printf("tempFormat = %s.\n",tempFormat);
					printf("tempLine = %s.\n",tempLine);
					printf("Error - incorrect format2\n");
					if ( bFree == 1 )
						{
						free(tempLine);
						}
					return 0;
					}
				}
			printf("AA5\n");
			printf("tempFormat- = %s.\n",tempFormat);
			printf("tempLine- = %s.\n",tempLine);
			tempFormat = strtok_r(NULL," ",&hold_format);
			if ( tempFormat != NULL )
				{
				if ( strcmp(tempFormat,"$condition") != 0 )
					{
					tempLine = strtok_r(NULL," ",&hold_line);
					}
				}
			printf("tempFormat+ = %s.\n",tempFormat);
			printf("tempLine+ = %s.\n",tempLine);
			printf("AA6\n");
			}
		printf("hold line now = %s\n",hold_line);
		}
	tempLine = strtok_r(NULL," ",&hold_line);
	if ( tempLine != NULL )
		{
		printf("Error - this line is not in the correct format\n");
		if ( bFree == 1 )
			{
			free(tempLine);
			}
		return 0;
		}
	printf("condition = %s\n",data->condition);
	printf("varName = %s\n",data->varName);
	printf("varType = %s\n",data->varType);
	printf("varSymbol = %s\n",data->varSymbol);
	printf("value = %s\n",data->value);
	printf("increm = %s\n",data->increm);
	printf("filePointer = %s\n",data->filePointer);
	printf("filePath = %s\n",data->filePath);
	printf("fileMode = %s\n",data->fileMode);
	for ( i=0;i<strlen(data->varType);i++ )
		{
		data->varType[i] = tolower(data->varType[i]);
		}
	if ( bFree == 1 )
		{
		free(tempLine);
		}
	printf("poo\n");
	return 1;
	}
