#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int getHelp()
	{
	char input[32];
	char command[32];
	printf("1.if or else\n2.printf\n3.do while\n4.while\n5.for loop\n");
	printf("ENTER COMMAND : ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",command);
	if(strcmp(command,"if"||"else") == 0)
		{
		/*printf description of the command*/
		}
	else if(strcmp(command,"printf") == 0)
		{
		/*printf description of the command*/
		}
	else if(strcmp(command,"dowhile") == 0)
		{
		/*printf description of the command*/
		}
	else if(strcmp(command,"while") == 0)
		{
		/*printf description of the command*/
		}
	else if(strcmp(command,"for") == 0)
		{
		/*printf description of the command*/
		}
	else 
		{
		printf("ERROR");
		}
	}