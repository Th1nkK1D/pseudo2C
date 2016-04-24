/* 
 * dataUpdate.c
 * 
 * Use for updateing temporary data.
 *
 * Created by Siriwimon Suksukhon (Poo), ID 3436
 * - Team We Must Survived -
 * 17 April 2016
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mainStructure.h"
#include "globalAccess.h"

/* function to check that condition is valid
 * Argument:
 * - input => string of condition
 * Return:
 * - 1 => if condition is ok
 * - 0 => if condition is not ok 
 */
int checkCondition ( char input[] )
	{
	int i = 0;
	char temp_input[512];
	char* tempCondition;
	VARIABLE_T* tempVar = NULL;
	int bQuotes = 0;

	strcpy(temp_input,input);

	tempCondition = strtok(temp_input," ");

	tempVar = searchWord(tempCondition);

	if ( tempVar != NULL )
		{
		tempCondition = strtok(NULL," ");
		if ( strcmp(tempCondition,"==") == 0 || strcmp(tempCondition,"<") == 0 || strcmp(tempCondition,">") == 0 || strcmp(tempCondition,"!=") == 0 || strcmp(tempCondition,"<=") == 0 || strcmp(tempCondition,">=") == 0 )
			{
			tempCondition = strtok(NULL," ");
			tempVar = NULL;
			tempVar = searchWord(tempCondition);
			if ( tempVar == NULL )
				{
				bQuotes = checkQuotes(tempCondition);
				if ( bQuotes == 0 )
					{
					for (i=0;i<strlen(tempCondition);i++)
						{
						if ( isalpha(tempCondition[i]) || isspace(tempCondition[i]) )
							{
							return 0;
							}
						}
					}
				else if ( bQuotes == -1 )
					{
					return 0;
					}
				}
			}
		else
			{
			return 0;
			}
		}		
	/* if it's not a variable, it must be a digit or string only */
	else	
		{
		bQuotes = checkQuotes(tempCondition);
		if ( bQuotes == 0 )
			{
			for (i=0;i<strlen(tempCondition);i++)
				{
				if ( isalpha(tempCondition[i]) || isspace(tempCondition[i]) )
					{
					return 0;
					}
				}
			}
		else if ( bQuotes == -1 )
			{
			return 0;
			}
		}
	return 1;
	}

/* function to check that this string has quotes (" ") or not.
 * Argument:
 * - input => word that want to check
 * Return:
 * - 1 => if there are quotes in this string
 * - 0 => if not
 * - -1 => if it has one quote or more than two quotes
 */ 
int checkQuotes ( char input[] )
	{
	int i = 0;
	int bQuotes = 0;
	if ( input[0] == '"' && input[strlen(input)-1] '"' )
		{
		return 1;
		}
	for ( i=0;i<strlen(input);i++ )
		{
		if ( input[i] == '"' )
			{
			bQuotes++;
			}
		}
	if ( bQuotes == 0 )
		{
		return 0;
		}
	else
		{
		return -1;
		}
	}

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

/* Function to check that line is in correct format 
 * Argument : 
 * pre_post_in => correct format of that line
 * lineCopied => string of that line
 * Return :
 * 1 => if it is in correct format
 * 0 => if it's not
 */
int checkFormat (char pre_post_in[], char lineCopied[])
	{
	int i = 0;
	char *format;
	char *line;
	char *temp_format = pre_post_in;
	char *temp_line = lineCopied;
	int checkDollar = 0;
	int format_space = 0;
	int line_space = 0;

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

/* Function for store all data in that line into the structure
 * Argument :
 * rule => rule for that line.
 * line => string of that line.
 * data => stucture for hold all data in line.
 * Return :
 * -5 => if condition is not valid
 * -4 => if variable is initialize by a number or a capital letter
 * -3 => file not found
 * -2 => variable is undeclared
 * -1 => if that line or that rule is NULL.
 * 0 => if that line does not be in the correct format.
 * 1 => if line is in correct format and update data in structure already.
 */
int dataUpdate (RULE_T* rule,char line[],TEMP_T* data)
	{
	RULE_T* tempRule;
	char lineCopied_0[512];
	char lineCopied_1[512];
	char lineCopied_2[512];
	char pre_post_in_1[512];	
	char pre_post_in_2[512];
	char* tempFormat;
	char* tempLine;
	char* hold_format = NULL;
	char* hold_line = NULL;
	int foundDollar = 0;
	int bFormat = 0;
	char* delim = NULL;
	VARIABLE_T* tempVar = NULL;
	FILE_T* tempFile = NULL;
	int bQuotes = 0;
	char* tempCondition = NULL;
	char condition[512];
	int bCondition = 0;
	char* delim = NULL;

	tempRule = rule;

	strcpy(lineCopied_0,line);

	delim = strpbrk(lineCopied_0," ");			/* To get first string of line */
	*delim = '\0';
	strcpy(lineCopied_1,delim+1);
	strcpy(lineCopied_2,delim+1);

	if (strlen(tempRule->preIn) == 0)
		{
		strcpy(pre_post_in_1,tempRule->postIn);
		strcpy(pre_post_in_2,tempRule->postIn);
		}
	else
		{
		strcpy(pre_post_in_1,tempRule->preIn);
		strcpy(pre_post_in_2,tempRule->preIn);
		}

	if ( strlen(pre_post_in_1) != 0 && strlen(lineCopied_1) != 0 )
		{
		bFormat = 0;
		bFormat = checkFormat(pre_post_in_1,lineCopied_1);

		if ( bFormat != 1 )
			{
			return 0;
			}

		hold_format = pre_post_in_2;
		hold_line = lineCopied_2;

		if ( strcasecmp("variable",lineCopied_0) == 0 )
			{
			while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
				{
				foundDollar = 0;
				foundDollar = findDollar(tempFormat);
				
				if ( foundDollar == 1 )
					{
					if ( strcmp("$v_name",tempFormat) == 0 )
						{
						strcpy(data->$v_name,tempLine);
						}
					else if ( strcmp("$v_type",tempFormat) == 0 )
						{
						strcpy(data->$v_type,tempLine);
						}
					}
				}
			addVariable(data->$v_name,data->$v_type);
			}
		else if ( strcasecmp("open",lineCopied_0) == 0 )
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
						strcpy(data->$f_mode,tempLine);
						}
					}
				}
			addFile(data->$f_path,data->$f_mode);
			}
		else
			{
			/* strtok format and line until NULL */
			while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
				{
				
				foundDollar = 0;
				foundDollar = findDollar(tempFormat);

				/* if we found Dollar, we knew it is a variable */
				if ( foundDollar == 1 )
					{
					/* store each type of data into structure */
					if ( strcmp("$con",tempFormat) == 0 )
						{
						strcpy(data->$con,tempLine);
						}
					else if ( strcmp("$v_name",tempFormat) == 0 )
						{
						strcpy(data->$v_name,tempLine);
						bQuotes = checkQuotes(data->$v_name);
						if ( bQuotes == 1 )
							{
							strcpy(data->$v_symbol,"s");
							}
						else
							{
							tempVar = searchWord(data->$v_name);
							if ( tempVar == NULL )
								{
								return -2;
								}
							else
								{
								if ( strcmp("print",lineCopied_0) == 0 || strcmp("get",lineCopied_0) == 0 || strcmp("read",lineCopied_0) == 0 || strcmp("write",lineCopied_0) == 0 )
									{
									strcpy(data->$v_symbol,tempVar->symbol);
									}
								}
							}
						}
					else if ( strcmp("$v_type",tempFormat) == 0 )
						{
						strcpy(data->$v_type,tempLine);
						}
					else if ( strcmp("$v_symbol",tempFormat) == 0 )
						{
						strcpy(data->$v_symbol,tempLine);
						}
					else if ( strcmp("$value",tempFormat) == 0 )
						{
						strcpy(data->$value,tempLine);
						}
					else if ( strcmp("$increm",tempFormat) == 0 )
						{
						strcpy(data->$increm,tempLine);
						}
					else if ( strcmp("$f_pointer",tempFormat) == 0 )
						{
						strcpy(data->$f_pointer,tempLine);
						}
					else if ( strcmp("$f_path",tempFormat) == 0 )
						{
						strcpy(data->$f_path,tempLine);
						if ( strcmp("open",lineCopied_0) == 0 || strcmp("read",lineCopied_0) == 0 || strcmp("getline",lineCopied_0) == 0 || strcmp("write",lineCopied_0) == 0 || strcmp("close",lineCopied_0) == 0 )
							{
							//tempFile = /* Missing */;
							if ( tempFile == NULL )
								{
								return -3;
								}
							else
								{
								strcpy(data->$f_pointer,tempFile->handle);
								}
							}
			
						}
					else if ( strcmp("$f_mode",tempFormat) == 0 )
						{
						strcpy(data->$f_mode,tempLine);
						}
					else
						{
						strcpy(data->$key,tempLine);
						}
					}
				}			
				
			}			
		return 1;
		}

	else
		{
		return -1;
		}
	}
