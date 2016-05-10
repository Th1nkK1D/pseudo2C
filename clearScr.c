#include <stdlib.h>
#include <stdio.h>

/* Clear screen function 
 * Depend on system that run makefile */
void clearScr()
	{
	#ifdef linux
		/* For Mac and Linux */
		system("clear");
	#else
		/* For Windows */
		system("cls");
	#endif
	}