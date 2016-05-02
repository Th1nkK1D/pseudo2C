#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mainStructure.h"
#include "globalAccess.h"

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

/* function to check that condition is valid
 * Argument:
 * - input => string of condition
 * Return:
 * - 1 => if condition is ok
 * - 0 => if condition is not ok 
 */
int checkCondition ( char input[] )
	{
	char* delim;
	char tempData[512];
	int i = 0;

	VARIABLE_T* findVar = NULL;
	char *type1 = NULL;
	char *type2 = NULL;

	strcpy(tempData,input);
	
	delim = strtok(tempData," ");

	while ( delim != NULL )
		{
		/* checking first token */
		findVar = NULL;
		findVar = searchWord(delim);

		/* if it's not a variable, we will find what type it is */
		if ( findVar == NULL )
			{
			/* if it doesn't have two quotes (initial and terminal) then we know it's not a string or char */
			if ( delim[0] != '"' || delim[strlen(delim)-1] != '"' )
				{
				/* if it has only one quote, return 0 */
				if ( delim[0] != '"' && delim[strlen(delim)-1] == '"' )
					{
					return 0;
					}
				else if ( delim[0] == '"' && delim[strlen(delim)-1] != '"' )
					{
					return 0;
					}
				/* if it doesn't have any quote, we absolutely know that it must be an int or double */ 
				else
					{
					/* if it still has any alphabet, space return 0 */
					for (i=0;i<strlen(delim);i++)
						{
						if ( isalpha(delim[i]) )
							{
							return 0;
							}
						else if ( isspace(delim[i]) )
							{
							return 0;
							}
						/* if we found dot, we suddenly know it is a double */
						else if ( delim[i] == '.' )
							{
							strcpy(type1,"double");
							}
						}
					/* if it's nothing until now, it's an int */
					if ( type1 == NULL )
						{
						strcpy(type1,"int");
						}
					}
				
				}
			/* if it has two quotes, we need to check that it is a char or string */
			else
				{
				/* if it has one character between two quotes, we know it is a char */
				if ( strlen(delim) == 3 )
					{
					strcpy(type1,"char");
					}
				/* if not, it is a string */
				else
					{
					strcpy(type1,"string");
					}
				}
			}
		/* if it's a variable, we can catch its type suddenly */
		else
			{
			strcpy(type1,findVar->type);
			}
		
		/* checking the middle token */
		delim = NULL;
		delim = strtok(NULL," ");
		
		if ( delim == NULL )
			{
			return 0;
			}		
		
		/* if it's not a valid sign, return 0 */
		if ( strcmp(delim,">") != 0 && strcmp(delim,"<") != 0 && strcmp(delim,"==") != 0 && strcmp(delim,"!=") != 0 && strcmp(delim,">=") != 0 && strcmp(delim,"<=") != 0 )
			{
			return 0;
			}

		/* checking third token, same as the first token */
		delim = NULL;
		delim = strtok(NULL," ");
		if ( delim == NULL )
			{
			return 0;
			}	

		findVar = NULL;
		findVar = searchWord(delim);

		/* if it's not a variable, we will find what type it is */
		if ( findVar == NULL )
			{
			/* if it doesn't have two quotes (initial and terminal) then we know it's not a string or char */
			if ( delim[0] != '"' || delim[strlen(delim)-1] != '"' )
				{
				/* if it has only one quote, return 0 */
				if ( delim[0] != '"' && delim[strlen(delim)-1] == '"' )
					{
					return 0;
					}
				else if ( delim[0] == '"' && delim[strlen(delim)-1] != '"' )
					{
					return 0;
					}
				/* if it doesn't have any quote, we absolutely know that it must be an int or double */ 
				else
					{
					/* if it still has any alphabet, space return 0 */
					for (i=0;i<strlen(delim);i++)
						{
						if ( isalpha(delim[i]) )
							{
							return 0;
							}
						else if ( isspace(delim[i]) )
							{
							return 0;
							}
						/* if we found dot, we suddenly know it is a double */
						else if ( delim[i] == '.' )
							{
							strcpy(type2,"double");
							}
						}
					/* if it's nothing until now, it's an int */
					if ( type1 == NULL )
						{
						strcpy(type2,"int");
						}
					}
				
				}
			/* if it has two quotes, we need to check that it is a char or string */
			else
				{
				/* if it has one character between two quotes, we know it is a char */
				if ( strlen(delim) == 3 )
					{
					strcpy(type2,"char");
					}
				/* if not, it is a string */
				else
					{
					strcpy(type2,"string");
					}
				}
			}
		/* if it's a variable, we can catch its type suddenly */
		else
			{
			strcpy(type2,findVar->type);
			}

		/* if type of the two data in condition is not the same, return 0 */
		if ( strcmp(type1,type2) != 0 )
			{
			return 0;
			}

		/* pop the next token, it must be && or || */
		delim = NULL;
		delim = strtok(NULL," ");

		if ( delim != NULL )
			{
			if ( strcmp(delim,"||") != 0 && strcmp(delim,"&&") != 0 )
				{
				return 0;
				}
			}
		delim = NULL;	
		delim = strtok(NULL," ");
		}
	return 1;
	}


int checkName ( char tempLine[] , char command[] , char varType[] )
	{
	VARIABLE_T* tempVar = NULL;
	int i = 0;
	char* type = NULL;

	tempVar = searchWord(tempLine);

	if ( tempVar == NULL )
		{
		if ( strcasecmp(command,"print") != 0 )
			{
			printf("Error - variable is undeclared (first use in this function)\n");
			return 0;
			}
		if ( tempLine[0] != '"' || tempLine[strlen(tempLine)-1] != '"' )
			{
			printf("Error - variable or string not found\n");
			return 0;
			}
		}
	else
		{
		sprintf(type,"%c",tempVar->type[0]);
		//strcpy(type,tempVar->type[0]);

		if ( strstr(varType,type) == NULL )
			{
			return 0;
			}
		
		/*if ( strcasecmp(command,"for") == 0 )
			{
			if ( strcmp(tempVar->type,"char") == 0 )
				{
				printf("Error - variable types of FOR loop now support [ int / double ]\n");
				return 0;
				}
			else if ( strcmp(tempVar->type,"string") == 0 )
				{
				printf("Error - variable types of FOR loop now support [ int / double ]\n");
				return 0;
				}
			}
		else if ( strcasecmp(command,"set") == 0 )
			{
			if ( strcmp(tempVar->type,"string") == 0 )
				{
				printf("Error - variable types of SET now support [ int / double / char ]\n");
				return 0;
				}
			}
		else if ( strcasecmp(command,"setstring") == 0 )
			{
			if ( strcmp(tempVar->type,"string") != 0 )
				{
				printf("Error - variable type of SETSTRING now support [ string ]\n");
				return 0;
				}
			}
		else if ( strcasecmp(command,"getline") == 0 )
			{
			if ( strcmp(tempVar->type,"string") != 0 )
				{
				printf("Error - variable type of GETLINE now support [ string ]\n");
				return 0;
				}
			}*/	
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
int checkFormat (char style[], char input[])
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

	printf("0LINE is %s\n",lineCopied);
	printf("0FORMAT is %s\n",pre_post_in);


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

	if ( format_space != line_space )
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
		}
	return 1;
	}	

int dataUpdate ( RULE_T* rule, char input[], TEMP_T* data )
	{
	RULE_T* tempRule = NULL;			/* store temporary of rule */
	char command[256];				/* store the first string as a command */
	char line[512];					/* store temporary of line */
	//char lineCopied_1[512];			/* store line for format checking */
	//char lineCopied_2[512];			/* store line for saving in temporary structure */
	char pre_post_in[256];				/* store temporary of prein/postin */
	char* tempFormat;				/* hold each token of prein/postin */
	char* tempLine;					/* hold each token of line */
	char* hold_format = NULL;			/* pointer to prein/postin */
	char* hold_line = NULL;				/* pointer to line */
	//int foundDollar = 0;				
	int bFormat = 0;				/* boolean to check format */
	int bName = 0;					/* boolean to check name */
	//int bValue = 0;
	VARIABLE_T* tempVar = NULL;			/* store temporary of variable */
	FILE_T* tempFile = NULL;			/* store temporary of pointer to file */
	//int bQuotes = 0;
	//char* tempCondition = NULL;
	//char condition[512];
	int bCondition = 0;				/* boolean to check condition */
	char* delim = NULL;
	int foundDollar = 0;
	int i = 0;

	tempRule = rule;
	strcpy(command,input);
	delim = strpbrk(command," ");
	*delim = '\0';
	strcpy(line,delim+1);

	if ( tempRule->preIn != NULL )
		{
		strcpy(pre_post_in,tempRule->preIn);
		}
	else
		{
		strcpy(pre_post_in,tempRule->postIn);
		}

	bFormat = checkFormat(pre_post_in,line);

	if ( strcasecmp(command,"if") == 0 )
		{
		bFormat = 1;
		}

	if ( bFormat != 1 )
		{
		printf("Error - incorrect format\n");
		return 0;
		}

	hold_format = pre_post_in;
	hold_line = line;

	if ( strcasecmp("variable",command) == 0 )
		{
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			
			if ( foundDollar == 1 )
				{
				if ( strcmp("$v_name",tempFormat) == 0 )
					{
					if ( isdigit(tempLine[0]) )
						{
						printf("Error - cannot begin a variable name with a number.\n");
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
				else if ( strcmp("$v_type",tempFormat) == 0 )
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
			}
		addVariable(data->$v_name,data->$v_type);
		}

	else if ( strcasecmp("open",command) == 0 )
		{
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
				
			if ( foundDollar == 1 )
				{
				if ( strcmp("$f_path",tempFormat) == 0 )
					{
					strcpy(data->$f_path,tempLine);
					}
				else if ( strcmp("$f_mode",tempFormat) == 0 )
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
			}
		addFile(data->$f_path,data->$f_mode);
		}

	else
		{
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);

			if ( foundDollar == 1 )
				{
				if ( strcmp("$con",tempFormat) == 0 )
					{
					bCondition = 0;
					bCondition = checkCondition(tempLine);
					
					if ( bCondition != 1 )
						{
						printf("Error - condition is invalid\n");
						return 0;
						}
					strcpy(data->$con,tempLine);
					}
				else if ( strcmp("$v_name",tempFormat) == 0 )
					{
					bName = 0;
					//bName = checkName(tempLine,command,tempRule->$varType);

					bName = 1;

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
						if ( strcmp(data->$v_type,"int") == 0 )
							{
							strcpy(data->$v_symbol,"%d");
							}
						else if ( strcmp(data->$v_type,"char") == 0 )
							{
							strcpy(data->$v_symbol,"%c");
							}
						else if ( strcmp(data->$v_type,"double") == 0 )
							{
							strcpy(data->$v_symbol,"%lf");
							}
						else
							{
							strcpy(data->$v_symbol,"%s");
							}
						}				
					}
				else if ( strcmp("$value",tempFormat) == 0 )
					{
					
					tempVar = searchWord(tempLine);

					if ( tempVar == NULL )
						{
						if ( strcmp(data->$v_type,"int") == 0 || strcmp(data->$v_type,"double") )
							{
							for (i=0;i<strlen(tempLine);i++)
								{
								if ( isalpha(tempLine[i]) || isspace(tempLine[i]) )
									{
									printf("Error - this data must be digit\n");
									return 0;
									}
								}
							}
						else if ( strcmp(data->$v_type,"char") == 0 )
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
						if ( strcmp(tempVar->type,data->$v_type) != 0 )
							{
							printf("Error - type of value is invalid\n");
							return 0;
							}			
					
					/*if ( strcasecmp(command,"for") == 0 )
						{
						for (i=0;i<strlen(tempLine);i++)
							{
							if ( isalpha(tempLine[i]) || isspace(tempLine[i]) )
								{
								printf("Error - value of FOR loop now support digit\n");
								return 0;
								}
							}
						}
					else if ( strcasecmp(command,"set") == 0 )
						{
						if ( strcmp(data->$v_symbol,"%c") == 0 )
							{
							if ( strlen(tempLine) != 1 )
								{
								printf("Error - this value must be one character\n");
								return 0;
								}
							}
						else if ( strcmp(data->$v_symbol,"%d") == 0 || strcmp(data->$v_symbol,"%lf") == 0 )
							{
							for (i=0;i<strlen(tempLine);i++)
								{
								if ( isalpha(tempLine[i]) || isspace(tempLine[i]) )
									{
									printf("Error - this value must be integer or double\n");
									return 0;
									}
								}
							}
						}*/
						}
					strcpy(data->$value,tempLine);							
					}
				else if ( strcmp("$f_path",tempFormat) == 0 )
					{
					tempFile = NULL;
					tempFile = searchFile(tempLine);

					if ( tempFile == NULL )
						{
						printf("Error - file not found\n");
						return 0;
						}
					else
						{
						if ( strcasecmp(command,"read") == 0 )
							{
							if ( strcmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								return 0;
								}
							}
						else if ( strcasecmp(command,"write") == 0 )
							{
							if ( strcmp(tempFile->mode,"w") != 0 )
								{
								printf("Error - this file is not in the write mode\n");
								return 0;
								}
							}
						else if ( strcasecmp(command,"getline") == 0 )
							{
							if ( strcmp(tempFile->mode,"r") != 0 )
								{
								printf("Error - this file is not in the read mode\n");
								return 0;
								}
							}
						}
					strcpy(data->$f_path,tempLine);
					strcpy(data->$f_pointer,tempFile->handle);
					}
				}
			}			
		}
	return 1;
	}
