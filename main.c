/*
 * main.c
 * 
 * Main part for pseudocode to C translator program
 * This program is used for converting simple psedocode into C language.
 *
 * Created by Siriwimon Suksukhon (Poo), ID 3436
 * - Team We Must Survived -
 * 17 April 2016
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mainStructure.h"
#include "translator.h"
#include "help.h"

/* Function to check that user choose option 0,1,2,3 only
 * Argument:
 * - input => choice from user
 * Return:
 * 1 => if choice is valid
 * 0 => if not
 */
int checkLine (char input[])
	{
	char* menu = "0123"; 				/* declaration of valid choices */
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
	int bChoice = 0;			/* Boolean to check that choice from user is valid */
	char input[64];				/* Get data from user */
	int option = 0;				/* Get option that user want */
	int bExit = 0;				/* Boolean to check that user want to exit program */

	while ( bExit == 0 )
		{
		bChoice = 0;
		while ( bChoice == 0 )
			{
			clearScr();

			printf("********************************************************************************\n");
			printf("                   ____                      __      ___   ______\n");
			printf("                  / __ \\________  __  ______/ /___  |__ \\ / ____/\n");
			printf("                 / /_/ / ___/ _ \\/ / / / __  / __ \\__/ // /     \n");
			printf("                / ____(__  )  __/ /_/ / /_/ / /_/ / __// /___   \n");
			printf("               /_/   /____/\\___/\\__,_/\\__,_/\\____/____/\\____/   \n");
			printf("\n");
			printf("************************** Pseudocode to C Translator **************************\n");
			                                                 
			printf("\n--- MAIN MENU ---\n");
			printf("1 - Pseudocode's rule\n");
			printf("2 - Translate pseudocode to C file\n");
			printf("3 - Get help\n");
			printf("0 - Exit\n\n");

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
			printf("Entering to translator\n");
			translator();
			}
	
		else if ( option == 3 )
			{
			getHelp();
			}
		else
			{
			bExit = 1;
			printf("THANK YOU\n");
			}
		}
	
	}
