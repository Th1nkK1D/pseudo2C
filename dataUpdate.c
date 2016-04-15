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
				printf("FORMAT == %s\n",format);
				printf("LINE == %s\n",line);
				return 0;
				}
			}	
		printf("format = %s\n",format);
		printf("line = %s\n",line);
		}

	return 1;
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


/* Function for store all data in that line into the structure
 * Argument :
 * rule => rule for that line.
 * line => string of that line.
 * data => stucture for hold all data in line.
 * Return :
 * -1- => if that line or that rule is NULL.
 * 0 => if that line does not be in the correct format.
 * 1 => if line is in correct format and update data in structure already.
 */
int dataUpdate (RULE_T* rule,char line[],TEMP_T* data)
	{
	RULE_T* tempRule = NULL;
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

	tempRule = rule;
	strcpy(lineCopied_1,line);
	strcpy(lineCopied_2,line);

	if ( tempRule->preIn == NULL )
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

		while ( (tempFormat = strtok_r(hold_format," ",&hold_format)) && (tempLine = strtok_r(hold_line," ",&hold_line)) )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);

			if ( foundDollar == 1 )
				{
				if ( strstr("con",tempFormat) != NULL )
					{
					data->con = tempLine;
					}
				else if ( strstr("v_name",tempFormat) != NULL )
					{
					data->v_name = tempLine;
					}
				else if ( strstr("v_type",tempFormat) != NULL )
					{
					data->v_type = tempLine;
					}
				else if ( strstr("v_symbol",tempFormat) != NULL )
					{
					data->v_symbol = tempLine;
					}
				else if ( strstr("value",tempFormat) != NULL )
					{
					data->value = tempLine;
					}
				else if ( strstr("increm",tempFormat) != NULL )
					{
					data->increm = tempLine;
					}
				else if ( strstr("f_pointer",tempFormat) != NULL )
					{
					data->f_pointer = tempLine;
					}
				else if ( strstr("f_path",tempFormat) != NULL )
					{
					data->f_path = tempLine;
					}
				else if ( strstr("f_mode",tempFormat) != NULL )
					{
					data->f_mode = tempLine;
					}
				else
					{
					data->key = tempLine;
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
