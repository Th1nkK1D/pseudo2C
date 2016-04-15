#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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

int checkFormat (char pre_post_in[], char lineCopied[])
	{
	char* format;
	char* line;
	int checkDollar = 0;

	//printf("POINT 1\n");

	format = strtok(pre_post_in," ");
	line = strtok(lineCopied," ");

	printf("format = %s\n",format);

	while ( format != NULL )
		{
		checkDollar = 0;
		checkDollar = findDollar(format);
		
		if ( checkDollar == 0 )
			{
			if ( strcmp(format,line) != 0 )
				{
				//printf("POINT 2\n");
				return 0;
				}
			}
		format = strtok (NULL," ");
		line = strtok (NULL," ");		
		printf("format = %s\n",format);
		if ( format == NULL )
			{
			printf("NULL\n");
			}
		}

	if ( format == NULL && line == NULL )
		{
		//printf("POINT 3\n");
		return 1;
		}
	else
		{
		//printf("POINT 4\n");
		return 0;
		}
	}

int main()
	{
	char format[256];
	char line[256];
	int check = 0;

	strcpy(format,"$v_name TO $value");
	strcpy(line,"count TO 0");

	check = checkFormat(format,line);

	//printf("CHECK = %d\n",check);
	
	}
