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
int checkCondition ( char input[] , char con[])
	{
	char* delim;
	char tempData[512];
	int i = 0;
	char tempCon[512];
	char leftToken[16];
	char sign[16];
	char rightToken[16];

	VARIABLE_T* findVar = NULL;
	char type1[16];
	char type2[16];

	memset(tempCon,0,sizeof(tempCon));

	printf("temp con is %s\n",tempCon);

	printf("POINT 55\n");

	strcpy(tempData,input);
	
	printf("TEMPDATA is %s\n",tempData);
	
	printf("POINT 56\n");

	delim = strtok(tempData," ");
	
	printf("TEMPDATA is %s\n",tempData);
	
	printf("DELIM is %s\n",delim);
	printf("POINT 57\n");

	while ( delim != NULL )
		{
		printf("POINT 58\n");
		/* checking first token */
		findVar = NULL;
		findVar = searchWord(delim);

		printf("temp con is %s\n",tempCon);

		printf("POINT 59\n");

		/* if it's not a variable, we will find what type it is */
		if ( findVar == NULL )
			{
			printf("POINT 60\n");
			/* if it doesn't have two quotes (initial and terminal) then we know it's not a string or char */
			if ( delim[0] != '"' || delim[strlen(delim)-1] != '"' )
				{
				printf("POINT 61\n");
				/* if it has only one quote, return 0 */
				if ( delim[0] != '"' && delim[strlen(delim)-1] == '"' )
					{
					return 0;
					}
				else if ( delim[0] == '"' && delim[strlen(delim)-1] != '"' )
					{
					return 0;
					}
				/* if it doesn't have any quote, we absolutely know that it must be an int or double or char */ 
				else
					{
					if ( delim[0] == '\'' && delim[strlen(delim)-1] == '\'' )
						{
						strcpy(type1,"char");
						}
					else if ( delim[0] != '\'' && delim[strlen(delim)-1] == '\'' )
						{
						return 0;
						}
					else if ( delim[0] == '\'' && delim[strlen(delim)-1] != '\'' )
						{
						return 0;
						}
					else
						{
						printf("POINT 62\n");
						/* if it still has any alphabet or space then return 0 */
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
						printf("POINT 63\n");
						/* if it's nothing until now, it's an int */
						if ( strcmp(type1,"double") != 0 )
							{
							printf("POINT 64\n");
							strcpy(type1,"int");
							}
						}
					}
				}
			/* if it has two quotes, we completely know that it's a string */
			else
				{
				strcpy(type1,"string");
				}
			}
		/* if it's a variable, we can catch its type suddenly */
		else
			{
			printf("POINT 68\n");
			strcpy(type1,findVar->type);
			}
		printf("POINT 69\n");
		strcpy(leftToken,delim);
		
		/* checking the middle token */
		printf("TEMPDATA is %s\n",tempData);
		printf("delim is %s\n",delim);

		delim = NULL;
		delim = strtok(NULL," ");

		printf("TEMPDATA is %s\n",tempData);
		printf("delim is %s\n",delim);

		printf("POINT 70\n");
		
		if ( delim == NULL )
			{
			printf("POINT 70.5\n");
			return 0;
			}

		printf("POINT 71\n");		
		
		/* if it's not a valid sign, return 0 */
		if ( strcmp(delim,">") != 0 && strcmp(delim,"<") != 0 && strcmp(delim,"==") != 0 && strcmp(delim,"!=") != 0 && strcmp(delim,">=") != 0 && strcmp(delim,"<=") != 0 )
			{
			printf("POINT 72\n");
			printf("delim = %s\n",delim);
			return 0;
			}

		printf("POINT 73\n");
		strcpy(sign,delim);

		/* checking third token, same as the first token */
		delim = NULL;
		delim = strtok(NULL," ");
		printf("POINT 74\n");
		if ( delim == NULL )
			{
			printf("POINT 75\n");
			return 0;
			}	
		printf("POINT 76\n");

		findVar = NULL;
		printf("delim findvar is %s\n",delim);
		findVar = searchWord(delim);

		printf("POINT 77\n");
		printf("temp con is %s\n",tempCon);

		/* if it's not a variable, we will find what type it is */
		if ( findVar == NULL )
			{
			printf("delim = %s\n",delim);
			printf("variable not found\n");
			printf("POINT 78\n");
			printf("temp con is %s\n",tempCon);
			/* if it doesn't have two quotes (initial and terminal) then we know it's not a string or char */
			if ( delim[0] != '"' || delim[strlen(delim)-1] != '"' )
				{
				printf("POINT 79\n");
				/* if it has only one quote, return 0 */
				if ( delim[0] != '"' && delim[strlen(delim)-1] == '"' )
					{
					printf("POINT 79.1\n");
					return 0;
					}
				else if ( delim[0] == '"' && delim[strlen(delim)-1] != '"' )
					{
					printf("POINT 79.2\n");
					return 0;
					}
				/* if it doesn't have any quote, we absolutely know that it must be an int or double */ 
				else
					{
					printf("POINT aa\n");

					if ( delim[0] == '\'' && delim[strlen(delim)-1] == '\'' )
						{
						strcpy(type2,"char");
						}
					else if ( delim[0] != '\'' && delim[strlen(delim)-1] == '\'' )
						{
						return 0;
						}
					else if ( delim[0] == '\'' && delim[strlen(delim)-1] != '\'' )
						{
						return 0;
						}
					else
						{

						/* if it still has any alphabet, space return 0 */
						for (i=0;i<strlen(delim);i++)
							{
							if ( isalpha(delim[i]) )
								{
								printf("POINT 79.3\n");
								return 0;
								}
							else if ( isspace(delim[i]) )
								{
								printf("POINT 79.4\n");
								return 0;
								}
							/* if we found dot, we suddenly know it is a double */
							else if ( delim[i] == '.' )
								{
								strcpy(type2,"double");
								}
							}
						/* if it's nothing until now, it's an int */
						if ( strcmp(type2,"double") != 0 )
							{
							printf("POINT 79.5\n");
							strcpy(type2,"int");
							}
						}
					}
				printf("POINT 79.6\n");
				printf("type2 is %s\n",type2);
				}
			/* if it has two quotes, we completely know that it's a string */
			else
				{
				printf("POINT 80\n");
				strcpy(type2,"string");
				}
			printf("POINT 81\n");
			printf("type2 is %s\n",type2);
			}

		
		/* if it's a variable, we can catch its type suddenly */
		else
			{
			printf("POINT 82\n");
			strcpy(type2,findVar->type);
			}
		printf("temp con is %s\n",tempCon);
		/* if type of the two data in condition is not the same, return 0 */
		if ( strcmp(type1,type2) != 0 )
			{
			printf("POINT 83\n");
			return 0;
			}
		printf("temp con is %s\n",tempCon);

		strcpy(rightToken,delim);

		printf("POINT 84\n");

		if ( strcmp(type1,"string") == 0 )
			{
			printf("temp con is %s\n",tempCon);
			printf("POINT 85\n");
			strcat(tempCon,"strcmp(");
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,leftToken);
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,",");
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,rightToken);
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,") ");
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,sign);
			printf("temp con is %s\n",tempCon);
			strcat(tempCon," 0");
			printf("temp con is %s\n",tempCon);
			}
		else
			{
			printf("temp con is %s\n",tempCon);
			printf("POINT 86\n");
			strcat(tempCon,leftToken);
			printf("temp con is %s\n",tempCon);
			strcat(tempCon," ");
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,sign);
			printf("temp con is %s\n",tempCon);
			strcat(tempCon," ");
			printf("temp con is %s\n",tempCon);
			strcat(tempCon,rightToken);
			printf("temp con is %s\n",tempCon);
			}	
		printf("temp con is %s\n",tempCon);		

		printf("POINT 87\n");

		/* pop the next token, it must be && or || */
		delim = NULL;
		delim = strtok(NULL," ");

		if ( delim != NULL )
			{
			printf("temp con is %s\n",tempCon);

			printf("POINT 88\n");
			if ( strcmp(delim,"||") != 0 && strcmp(delim,"&&") != 0 )
				{
				return 0;
				}
			else
				{
				printf("POINT 89\n");
				strcat(tempCon," ");
				printf("POINT 89.1\n");
				printf("delim is %s\n",delim);
				printf("tempCondition is %s\n",tempCon);
				strcat(tempCon,delim);
				printf("POINT 89.2\n");
				strcat(tempCon," ");
				}
			}


		printf("temp con is %s\n",tempCon);
		printf("POINT 89.5\n");
		delim = NULL;	
		delim = strtok(NULL," ");
		}
	printf("POINT 90\n");
	strcpy(con,tempCon);
	printf(" C O N = %s\n",con);
	return 1;
	}


int checkName ( char tempLine[] , char command[] , char varType[] )
	{
	VARIABLE_T* tempVar = NULL;
	int i = 0;
	char type[48];

	printf("POINT 44\n");

	tempVar = searchWord(tempLine);

	printf("POINT 45\n");

	if ( tempVar == NULL )
		{
		printf("POINT 46\n");
		if ( strcasecmp(command,"print") != 0 )
			{
			printf("POINT 47\n");
			printf("Error - variable is undeclared (first use in this function)\n");
			return 0;
			}
		if ( tempLine[0] != '"' || tempLine[strlen(tempLine)-1] != '"' )
			{
			printf("POINT 48\n");
			printf("Error - variable or string not found\n");
			return 0;
			}
		printf("POINT 49\n");
		}
	else
		{
		printf("TYPE is %s\n",tempVar->type);
		printf("POINT 50\n");
		sprintf(type,"%c",tempVar->type[0]);
		
		//strcpy(type,tempVar->type[0]);

		printf("POINT 51\n");

		if ( strstr(varType,type) == NULL )
			{
			printf("POINT 52\n");
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
		printf("POINT 53\n");	
		}
	printf("POINT 54\n");
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
	if ( strcmp(temp_format,"$con") == 0 )
		{
		return 1;
		}
	

	if ( format_space != line_space && strcasecmp(command,"for") != 0 )
		{
		printf("POINT 91\n");
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
				printf("POINT 92\n");
				return 0;
				}
			}
		if ( strcmp(temp_format,"$con") == 0 )
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
	char lineCondition[128];
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

	memset(data->$con,0,sizeof(data->$con));
	memset(data->$v_name,0,sizeof(data->$v_name));
	memset(data->$v_type,0,sizeof(data->$v_type));
	memset(data->$v_symbol,0,sizeof(data->$v_symbol));
	memset(data->$value,0,sizeof(data->$value));
	memset(data->$increm,0,sizeof(data->$increm));
	memset(data->$f_pointer,0,sizeof(data->$f_pointer));
	memset(data->$f_path,0,sizeof(data->$f_path));
	memset(data->$f_mode,0,sizeof(data->$f_mode));
	memset(data->$key,0,sizeof(data->$key));

	printf("POINT 1\n");

	tempRule = rule;
	strcpy(command,input);
	printf("POINT 2\n");
	printf("command is %s\n",command);
	
	delim = strpbrk(command," ");
	if ( delim == NULL )
		{
		return 1;
		}
	*delim = '\0';
	strcpy(line,delim+1);
	//strcpy(lineCondition,line);
	printf("POINT 3\n");

	if ( strlen(tempRule->preIn) != 0 )
		{
		printf("POINT 4\n");
		strcpy(pre_post_in,tempRule->preIn);
		}
	else
		{
		printf("POINT 5\n");
		strcpy(pre_post_in,tempRule->postIn);
		}

	bFormat = checkFormat(pre_post_in,line,command);
	printf("pre_post_in = %s\n",pre_post_in);
	printf("line = %s\n",line);

	if ( bFormat != 1 )
		{
		printf("POINT 7\n");
		printf("Error - incorrect format\n");
		return 0;
		}

	printf("POINT 8\n");

	hold_format = pre_post_in;
	hold_line = line;

	if ( strcasecmp("variable",command) == 0 )
		{
		printf("POINT 9\n");
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);	

			printf("POINT 10\n");
			if ( foundDollar == 1 )
				{
				if ( strcmp("$v_name",tempFormat) == 0 )
					{
					printf("POINT 11\n");
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
					printf("POINT 12\n");
					strcpy(data->$v_name,tempLine);
					}
				else if ( strcmp("$v_type",tempFormat) == 0 )
					{
					printf("POINT 13\n");
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
					printf("POINT 14\n");
					}
				}
			}
		printf("POINT 15\n");
		addVariable(data->$v_name,data->$v_type);
		if ( strcmp(data->$v_type,"string") == 0 )
			{
			strcpy(data->$v_type,"char");
			strcat(data->$v_name,"[256]");
			}
		}

	else if ( strcasecmp("open",command) == 0 )
		{
		printf("POINT 16\n");
		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			printf("POINT 17\n");
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
				
			printf("POINT 18\n");
			if ( foundDollar == 1 )
				{
				if ( strcmp("$f_path",tempFormat) == 0 )
					{
					printf("POINT 19\n");
					strcpy(data->$f_path,tempLine);
					}
				else if ( strcmp("$f_mode",tempFormat) == 0 )
					{
					printf("POINT 20\n");
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
					printf("POINT 21\n");
					}
				}
			}
		printf("POINT 22\n");
		addFile(data->$f_path,data->$f_mode,data->$f_pointer);
		}

	else
		{
		printf("POINT 23\n");
		tempFormat = strtok_r(hold_format," ",&hold_format);
		if ( strcmp(tempFormat,"$con") != 0 )
			{
			printf("POINT 23.5\n");
			tempLine = strtok_r(hold_line," ",&hold_line);
			}
		
		while ( tempFormat != NULL )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);

			if ( foundDollar == 1 )
				{
				printf("POINT 24\n");
				if ( strcmp("$con",tempFormat) == 0 )
					{
					printf("POINT 25\n");
					printf("holdline == %s\n",hold_line);
					tempLine = strtok_r(NULL," ",&hold_line);
					printf("tempLINE == %s\n",tempLine);

					memset(lineCondition,0,sizeof(lineCondition));
					
					while ( tempLine != NULL )
						{
						printf("tempLine = %s\n",tempLine);
						strcat(lineCondition,tempLine);
						
						tempLine = strtok_r(NULL," ",&hold_line);
						if ( tempLine != NULL )
							{
							strcat(lineCondition," ");
							}
						}

					printf("lineCondition = %s\n",lineCondition);
					
					bCondition = 0;
					bCondition = checkCondition(lineCondition,data->$con);

					printf("DATA CON = %s\n",data->$con);
					
					if ( bCondition != 1 )
						{
						printf("Error - condition is invalid\n");
						return 0;
						}

					printf("POINT 26\n");
					}
				else if ( strcmp("$v_name",tempFormat) == 0 )
					{
					printf("POINT 27\n");
					bName = 0;
					bName = checkName(tempLine,command,tempRule->varType);

					if ( bName != 1 )
						{
						return 0;
						}
					printf("POINT 28\n");
					strcpy(data->$v_name,tempLine);

					tempVar = NULL;
					tempVar = searchWord(data->$v_name);
					printf("POINT 29\n");
					if ( tempVar == NULL )
						{
						strcpy(data->$v_symbol,"%s");
						}
					else
						{
						printf("POINT 30\n");
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
						printf("POINT 31\n");
						}
					strcat(data->$increm,data->$v_name);
					strcat(data->$increm,"++");			
					}
				else if ( strcmp("$value",tempFormat) == 0 )
					{
					printf("POINT 32\n");
					tempVar = searchWord(tempLine);

					if ( tempVar == NULL )
						{
						printf("POINT 33\n");
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
						printf("POINT 34\n");
						}
					else
						{
						printf("POINT 35\n");
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
					printf("POINT 36\n");
					strcpy(data->$value,tempLine);							
					}
				else if ( strcmp("$f_path",tempFormat) == 0 )
					{
					printf("POINT 37\n");
					tempFile = NULL;
					tempFile = searchFile(tempLine);

					if ( tempFile == NULL )
						{
						printf("Error - file not found\n");
						return 0;
						}
					else
						{
						printf("POINT 38\n");
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
						printf("POINT 39\n");
						}
					printf("POINT 40\n");
					strcpy(data->$f_path,tempLine);
					strcpy(data->$f_pointer,tempFile->handle);
					}
				}
			printf("POINT 41\n");
			tempFormat = strtok_r(NULL," ",&hold_format);
			printf("tempFormat is %s\n",tempFormat);
			if ( tempFormat != NULL )
				{
				if ( strcmp(tempFormat,"$con") != 0 )
					{
					tempLine = strtok_r(NULL," ",&hold_line);
					}
				}
			}
		printf("POINT 42\n");			
		}
	printf("POINT 43\n");
	return 1;
	}
