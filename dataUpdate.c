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

void dataUpdate (RULE_T* rule,char line[],TEMP_DATA_T** data)
	{
	RULE_T* tempRule = NULL;
	char lineCopied[512];
	char pre_post_in[512];
	char* tempFormat = NULL;
	char* tempLine = NULL;
	int foundDollar = 0;	


	tempRule = rule;
	strcpy(lineCopied,line);

	if ( tempRule->preIn == NULL )
		{
		strcpy(pre_post_in,tempRule->postIn);
		}
	else
		{
		strcpy(pre_post_in,tempRule->preIn);
		}

	if ( strlen(pre_post_in) != 0 && strlen(lineCopied) != 0 )
		{

	
		tempFormat = strtok(pre_post_in," ");
		while ( tempFormat != NULL )
			{
			foundDollar = 0;
			foundDollar = findDollar(tempFormat);
			if ( foundDollar == 0 )
				{
				tempFormat = strtok(NULL," ");
				}
			tempLine = strtok(lineCopied," ");
		
			}
		while (

	else
		{
		return 0;
		}
