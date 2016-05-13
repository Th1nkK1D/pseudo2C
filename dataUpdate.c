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
			printf("i\n");
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
			printf("ii\n");
			return 0;
			}	
		
		/* if it's not a valid sign, return 0 */
		if ( strcasecmp(pToken,">") != 0 && strcasecmp(pToken,"<") != 0 && strcasecmp(pToken,"==") != 0 && strcasecmp(pToken,"!=") != 0 && strcasecmp(pToken,">=") != 0 && strcasecmp(pToken,"<=") != 0 )
			{
			printf("DELL = %s\n",pToken);
			printf("iii\n");
			return 0;
			}
		strcpy(sign,pToken);

		/* checking third token, same as the first token */
		pToken = NULL;
		pToken = strtok_r(NULL," ",&hold_input);
		if ( pToken == NULL )
			{
			printf("iv\n");
			return 0;
			}	
		if ( pToken[0] == '\"' && pToken[strlen(pToken)-1] != '\"' )
			{
			printf("p3\n");
			strcat(tempDelim,pToken);
			strcat(tempDelim," ");
			if ( strstr(hold_input,"\"") == NULL )
				{
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
			printf("v\n");
			return 0;
			}
		/* if type of the two data in condition is not the same, return 0 */
		if ( strcasecmp(type1,type2) != 0 )
			{
			printf("vi\n");
			return 0;
			}

		strcpy(rightToken,item);

		printf("lefTOKEN = %s\n",leftToken);
		printf("rightTOKEN = %s\n",rightToken);

		if ( strcasecmp(type1,"string") == 0 )
			{
			strcat(tempCon,"strcasecmp(");
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
				printf("vii\n");
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
		if ( strcasecmp(command,"print") != 0 )
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
		sprintf(type,"%c",tempVar->type[0]);

		if ( strstr(varType,type) == NULL )
			{
			return 0;
			}	
		}
	return 1;		
	}

/* Function to check that line is in correct format 
 * Argument : 
 * pre_post_in => correct format of that line
 * lineCopied => string of that line
 * Return :
 * 1 => if it is in correct format
 * 0 => if it's not
 */
int checkFormat (char style[], char input[], char command[])
	{
	int i = 0;
	char lineCopied[512];
	char *format;
	char *line;
	char pre_post_in[512];
	char *temp_format = NULL;
	char *temp_line = NULL;
	int checkDollar = 0;
	int format_space = 0;
	int line_space = 0;	

	strcpy(lineCopied,input);
	strcpy(pre_post_in,style);

	temp_format = pre_post_in;
	temp_line = lineCopied;

	for(i=0;i<strlen(temp_format);i++)
		{
		if ( isspace(temp_format[i]) )
			{
			format_space++;
			}
		}

	for(i=0;i<strlen(temp_line);i++)
		{
		if ( isspace(temp_line[i]) )
			{
			line_space++;
			}
		}
	if ( strcasecmp(temp_format,"$con") == 0 )
		{
		return 1;
		}
	

	if ( format_space != line_space && strcasecmp(command,"for") != 0 )
		{
		return 0;
		}

	while ( (format = strtok_r(temp_format," ",&temp_format)) && (line = strtok_r(temp_line," ",&temp_line)) )
		{
		checkDollar = 0;
		checkDollar = findDollar(format);
		
		if ( checkDollar == 0 )
			{
			if ( strcasecmp(format,line) != 0 )
				{
				return 0;
				}
			}
		if ( strcasecmp(temp_format,"$con") == 0 )
			{
			return 1;
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
	char lineCondition[512];
	char* hold_format = NULL;			/* pointer to prein/postin */
	char* hold_line = NULL;				/* pointer to line */
	int foundDollar = 0;				/* boolean to check it's a variable in structure */				
	int bFormat = 0;				/* boolean to check format */
	int bName = 0;					/* boolean to check name */
	VARIABLE_T* tempVar = NULL;			/* store temporary of variable */
	FILE_T* tempFile = NULL;			/* store temporary of pointer to file */
	int bCondition = 0;				/* boolean to check condition */
	char* delim = NULL;
	int i = 0;
	char tempString[512];

	memset(data->$con,0,sizeof(data->$con));
	memset(data->$v_name,0,sizeof(data->$v_name));
	memset(data->$v_type,0,sizeof(data->$v_type));
	memset(data->$v_symbol,0,sizeof(data->$v_symbol));
	memset(data->$value,0,sizeof(data->$value));
	memset(data->$increm,0,sizeof(data->$increm));
	memset(data->$f_pointer,0,sizeof(data->$f_pointer));
	memset(data->$f_path,0,sizeof(data->$f_path));
	memset(data->$f_mode,0,sizeof(data->$f_mode));
	memset(tempString,0,sizeof(tempString));

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
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			bName = 0;

			if ( foundDollar == 1 )
				{
				if ( strcasecmp("$v_name",tempFormat) == 0 )
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
					strcpy(data->$v_name,tempLine);
					}
				else if ( strcasecmp("$v_type",tempFormat) == 0 )
					{
					if ( strcasecmp(tempLine,"int") == 0 )
						{						
						strcpy(data->$v_type,tempLine);
						}
					else if ( strcasecmp(tempLine,"char") == 0 )
						{
						strcpy(data->$v_type,tempLine);
						}
					else if ( strcasecmp(tempLine,"double") == 0 )
						{
						strcpy(data->$v_type,tempLine);
						}
					else if ( strcasecmp(tempLine,"string") == 0 )
						{
						strcpy(data->$v_type,tempLine);
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
					printf("Error - incorrect format\n");
					return 0;
					}
				}
			}
		addVariable(data->$v_name,data->$v_type);
		if ( strcasecmp(data->$v_type,"string") == 0 )
			{
			strcpy(data->$v_type,"char");
			strcat(data->$v_name,"[256]");
			}
		}

	else if ( strcasecmp("open",command) == 0 )
		{
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			tempFile = NULL;

			if ( foundDollar == 1 )
				{
				if ( strcasecmp("$f_path",tempFormat) == 0 )
					{
					tempFile = searchFile(tempLine);
					if ( tempFile != NULL )
						{
						printf("Error - this file is opening\n");
						return 0;
						}
					strcpy(data->$f_path,tempLine);
					}
				else if ( strcasecmp("$f_mode",tempFormat) == 0 )
					{
					if ( strcasecmp(tempLine,"read") == 0 )
						{
						strcpy(data->$f_mode,"r");
						}
					else if ( strcasecmp(tempLine,"write") == 0 )
						{
						strcpy(data->$f_mode,"w");
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
		addFile(data->$f_path,data->$f_mode,data->$f_pointer);
		}

	else
		{
		printf("I\n");
		tempFormat = strtok_r(hold_format," ",&hold_format);
		printf("J\n");
		printf("tempFormat === %s\n",tempFormat);
		if ( strcasecmp(tempFormat,"$con") != 0 )
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
				printf("point 0.9\n");
				if ( strstr(hold_line,"\"") == NULL )
					{
					printf("11\n");
					printf("Error - condition is invalid\n");
					return 0;
					}
				tempLine = strtok_r(NULL,"\"",&hold_line);
				printf("tempLine = %s\n",tempLine);
				printf("point 0.95\n");
				if ( tempLine != NULL )	
					{
					printf("point 1\n");
					strcat(tempString," ");
					strcat(tempString,tempLine);
					strcat(tempString,"\"");
					printf("tempString2 = %s\n",tempString);
					printf("point 2\n");
					strcpy(tempLine,tempString);
					printf("point 3\n");
					memset(tempString,0,sizeof(tempString));
					}
				}
			}
		
		while ( tempFormat != NULL )
			{
			
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);

			if ( foundDollar == 1 )
				{
				if ( strcasecmp("$con",tempFormat) == 0 )
					{
					memset(lineCondition,0,sizeof(lineCondition));
					tempLine = strtok_r(NULL," ",&hold_line);
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
								return 0;
								}
							tempLine = strtok_r(NULL,"\"",&hold_line);
							printf("TEMPPP = %s\n",tempLine);
							if ( tempLine == NULL )
								{
								printf("Error - condition is invalid\n");
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
					bCondition = checkCondition(lineCondition,data->$con);
					
					if ( bCondition != 1 )
						{
						printf("type is %s\n",data->$v_type);
						printf("Error - condition is invalid\n");
						return 0;
						}
					}
				else if ( strcasecmp("$v_name",tempFormat) == 0 )
					{
					bName = 0;
					bName = checkName(tempLine,command,tempRule->varType);
					printf("tempLine = %s\n",tempLine);

					if ( bName != 1 )
						{
						return 0;
						}
					strcpy(data->$v_name,tempLine);

					tempVar = NULL;
					tempVar = searchWord(data->$v_name);
					if ( tempVar == NULL )
						{
						strcpy(data->$v_symbol,"%s");
						}
					else
						{
						strcpy(data->$v_type,tempVar->type);
						if ( strcasecmp(data->$v_type,"int") == 0 )
							{
							strcpy(data->$v_symbol,"%d");
							}
						else if ( strcasecmp(data->$v_type,"char") == 0 )
							{
							strcpy(data->$v_symbol,"%c");
							}
						else if ( strcasecmp(data->$v_type,"double") == 0 )
							{
							strcpy(data->$v_symbol,"%lf");
							}
						else
							{
							strcpy(data->$v_symbol,"%s");
							}
						}
					strcat(data->$increm,data->$v_name);
					strcat(data->$increm,"++");			
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
								return 0;
								}
							}
						else if ( strcasecmp(data->$v_type,"int") == 0 || strcasecmp(data->$v_type,"double") == 0 )
							{
							if ( checkMath(tempLine,strlen(tempLine)) == 0 )
								{
								printf("Error - this value is invalid\n");
								return 0;
								}
							}
						else if ( strcasecmp(data->$v_type,"char") == 0 )
							{
							if ( strlen(tempLine) != 1 )
								{
								printf("Error - this data must be one character\n");
								return 0;
								}
							}
						}
					else
						{
						if ( strcasecmp(tempVar->type,data->$v_type) != 0 )
							{
							printf("Error - type of value is invalid\n");
							return 0;
							}
						}
					strcpy(data->$value,tempLine);							
					}
				else if ( strcasecmp("$f_path",tempFormat) == 0 )
					{
					tempFile = NULL;
					tempFile = searchFile(tempLine);

					if ( tempFile == NULL )
						{
						printf("Error - file is undeclared or deleted\n");
						return 0;
						}
					else
						{
						if ( strcasecmp(command,"read") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								return 0;
								}
							}
						else if ( strcasecmp(command,"write") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"w") != 0 )
								{
								printf("Error - this file is not in the write mode\n");
								return 0;
								}
							}
						else if ( strcasecmp(command,"getline") == 0 )
							{
							if ( strcasecmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								return 0;
								}
							}
						else if ( strcasecmp(command,"close") == 0 )
							{
							strcpy(data->$f_mode,tempFile->mode);
							strcpy(data->$f_pointer,tempFile->handle);
							deleteFile(tempLine);
							}
						}
					if ( strcasecmp(command,"close") != 0 )
						{
						strcpy(data->$f_path,tempLine);
						strcpy(data->$f_pointer,tempFile->handle);
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
			tempFormat = strtok_r(NULL," ",&hold_format);
			if ( tempFormat != NULL )
				{
				if ( strcasecmp(tempFormat,"$con") != 0 )
					{
					tempLine = strtok_r(NULL," ",&hold_line);
					if ( tempLine[0] == '\"' && tempLine[strlen(tempLine)-1] != '\"' )
						{
						printf("point 0.85\n");
						strcat(tempString,tempLine);
						printf("point 0.9\n");
						tempLine = strtok_r(NULL,"\"",&hold_line);
						printf("tempLine = %s\n",tempLine);
						printf("point 0.95\n");
						if ( tempLine != NULL )	
							{
							printf("point 1\n");
							strcat(tempString,tempLine);
							printf("point 2\n");
							strcpy(tempLine,tempString);
							printf("point 3\n");
							memset(tempString,0,sizeof(tempString));
							}
						}
					}
				}
			}		
		}
	printf("DATA CON is %s\n",data->$con);
	for ( i=0;i<strlen(data->$v_type);i++ )
		{
		data->$v_type[i] = tolower(data->$v_type[i]);
		}
	return 1;
	}
