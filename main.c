#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkLine (char input[])
	{
	char* menu = "0123"; 
	int i = 0;

	if ( strlen(input) != 1 )
		{
		return 0;
		}

	for (i=0;i<strlen(input);i++)
		{
		if ( isalpha(input[i]) )
			{
			return 0;
			}
		else if ( issapce(input[i]) )
			{
			return 0;
			}			
		}
	if ( strstr(menu,input) != NULL )
		{
		return 1;
		}
	return 0;
	}

int main ()
	{
	int bLine = 0;
	char input[64];
	int option = 0;

	printf("--- MAIN MENU ---\n");
	printf("0 - Exit\n");
	printf("1 - Pseudocode's rule\n");
	printf("2 - Compile pseudocode to C file\n\n");
	printf("3 - Get help\n");
	

	printf("Which option? ");
	fgets(input,sizeof(input),stdin);

	if ( input[strlen(input)-1] == '\n' )
		{
		input[strlen(input)-1] = '\0';
		}

	while ( bLine == 0 )
		{
		bLine = checkLine(input);
		if ( bLine == 0 )
			{
			printf("Error - please select number from the above menu.\n");
			}
		}
	sscanf(input,"%d",&option);

	if ( option == 1 )
		{
		pseudoRule();
		}

	else if ( option == 2 )
		{
		compiler();
		}
	
	else if ( option == 3 )
		{
		/* ... Get help function ... */
		}
	
	}
