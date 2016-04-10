int checkFormat (char pre_post_in[], char lineCopied[])
	{
	char* format;
	char* line;
	int checkDollar = 0;

	format = strtok(pre_post_in," ");
	line = strtok(lineCopied," ");

	while ( format != NULL )
		{
		checkDollar = 0;
		checkDollar = findDollar(format);

		if ( checkDollar == 0 )
			{
			if ( strcmp(format,line) != 0 )
				{
				return 0;
				}
			}

		format = strtok (NULL," ");
		line = strtok (NULL," ");
		}

	if ( format == NULL && line == NULL )
		{
		return 1;
		}
	else
		{
		return 0;
		}		
			

int findDollar (char input[])
	{
	int i = 0;
	for (i=0;i<strlen(input);i++)
		{
		if (strcmp(input[i],'$')
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

int dataUpdate (RULE_T* rule,char line[],TEMP_DATA_T* data)
	{
	RULE_T* tempRule = NULL;
	char lineCopied_1[512];
	char lineCopied_2[512];
	char pre_post_in_1[512];	
	char pre_post_in_2[512];
	char* tempFormat = NULL;
	char* tempLine = NULL;
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
		strcpy(pre_post_in_2,tempRule->preIn);
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
		tempFormat = strtok(pre_post_in_2," ");
		tempLine = strtok(lineCopied_2," ");

		while ( tempFormat != NULL )
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
			tempFormat = strtok(NULL," ");
			tempLine = strtok(NULL," ");
			}
		}

	else
		{
		return -1;
		}
