# pseudo2C
Convert pseudo code to compilable and standard C language
CPE113 Project, CPE, KMUTT

**Team We Must Survive!**
- Withee Poositasai (Lookkid)     58070503429 
- Siriwimon Suksukhon  (Poo) 	    58070503436
- Gittipat Ariyaprayoon (Gide) 	58070503440

Run Pseudo2C to start a program.

### Rule

##### Basic Rules
1. Can only translate 1 Psedocode file with exactly 1 main function.
2. Only supported command can be used (Full command list is in getHelp menu)

##### Syntax Rule
1. In conditional statement, operator must be use like standard C.
2. Comment can be use like normal, but can't be in the same line with command.
3. Indenting is optional, but will be generated automatically in C file.
4. Empty line will be remained in C file.
5. Don't type Semi-colon.
6. Uppercase for command is optional but it is recommended.
7. For mathermatical statement only +,-,*,/,% and (,) are allowed.
8. Using command inside other command is not allowed (Except ELSE IF).

##### Variable Rules
1. All used variable must be declared before using. Same as open file.
2. Variable support type is "int", "double", "char", "string" that must be 
   defined in declaration.
3. String will have size of 256.
4. To assign string value, "" is needed. To assign char value, '' is needed.
5. Array and structure is not supported.