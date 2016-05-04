#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainStructure.h"
#include "dbAccess.h"

void getHelp()
	{
	char** help;
	int i=0;
	int count;
	int check;
	printf("1\n");
	prepareDB();
	printf("2\n");
	count = countRule();
	printf("3\n");
	printf("%d\n",count);
	help = (char**) calloc(count,sizeof(char*));
	for(i=0;i<count;i++)
		{
		help[i] = (char*) calloc(16,sizeof(char));
		}

	sprintf(help[0],"testtest");
	printf("%s\n",help[0]);

	check = getAllRuleName(help);
	printf("%d\n",check);
	printf("4\n");
	for(i=0;i<count;i++)
		{
		printf("%s.\n",help[i]);
		}
	printf("5\n");
	}

int main()
	{
	printf("HELLO\n");
	getHelp();
	return 0;
	}