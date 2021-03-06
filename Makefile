# Makefile for Pseudo2C Project
# We Must Survive Team
# Withee Poositasai (Lookkid) 58070503429

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= Pseudo2C$(EXECEXT) 

all : $(EXECUTABLES)

ReadRule.o :	ReadRule.c mainStructure.h
	gcc -c ReadRule.c

dbAccess.o :	dbAccess.c mainStructure.h
	gcc -c dbAccess.c

globalAccess.o :	globalAccess.c mainStructure.h
	gcc -c globalAccess.c

dataUpdate.o :	dataUpdate.c mainStructure.h globalAccess.h
	gcc -c dataUpdate.c

translator.o :	translator.c mainStructure.h dataUpdate.h globalAccess.h
	gcc -c translator.c

help.o :	dbAccess.c mainStructure.h
	gcc -c help.c

clearScr.o : clearScr.c
	gcc -c clearScr.c -D$(PLATFORM)
	
checkMath.o :	checkMath.c mainStructure.h globalAccess.h
	gcc -c checkMath.c

main.o :	main.c translator.h
	gcc -c main.c

Pseudo2C$(EXECEXT) : main.o ReadRule.o dbAccess.o globalAccess.o dataUpdate.o translator.o help.o clearScr.o checkMath.o
	gcc -o Pseudo2C$(EXECEXT) main.o ReadRule.o dbAccess.o globalAccess.o dataUpdate.o translator.o help.o clearScr.o checkMath.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
