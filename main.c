#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mainStructure.h"
#include "translator.h"

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
		else if ( isspace(input[i]) )
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
	int bChoice = 0;
	char input[64];
	int option = 0;
	int bExit = 0;

	printf("\n--- MAIN MENU ---\n");
	printf("0 - Exit\n");
	printf("1 - Pseudocode's rule\n");
	printf("2 - Compile pseudocode to C file\n");
	printf("3 - Get help\n\n");


	while ( bExit == 0 )
		{
		bChoice = 0;
		while ( bChoice == 0 )
			{

			printf("Which option? ");
			fgets(input,sizeof(input),stdin);

			if ( input[strlen(input)-1] == '\n' )
				{
				input[strlen(input)-1] = '\0';
				}
			bChoice = checkLine(input);
			if ( bChoice == 0 )
				{
				printf("Error - please select number from the above menu.\n");
				}
			}	
		sscanf(input,"%d",&option);

		if ( option == 1 )
			{
			//pseudoRule();
			printf("To be implement soon\n");
			}

		else if ( option == 2 )
			{
			translator();
			}
	
		else if ( option == 3 )
			{
			/* ... Get help function ... */
			printf("To be implement soon\n");
			}
		else
			{
			bExit = 1;
			printf("THANK YOU\n");
			}
		}
	
	}
