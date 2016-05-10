/* Main data structure - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survived */

/* 1. Rules Database (dbAccess Module)
 * Array of structure which each structure contain rules of function. 
 * These data are read from database (csv file) when the program start. 
 * We use these rule as a expected pseudocode pattern and the C corrected syntax for translation. */
typedef struct
 	{
 	char name[16];			/* Name of this function, Showing in help menu. */ 
 	char key[16];			/* “Key” of function, which is the first word of each pseudocode line. */
 	char preIn[64];			/* Expect input pseudocode format. Containing “Keyword” to compare with pseudo code and extract input data. */
 	char preOut[64];		/* Output correct C format to be write. */
 	char preVar[32];		/* List of “Keyword” in order to be print out in C syntax. */
 	char postKey[16];		/* End “Key” of function, in case of this function create a scope. */
 	char postIn[64];		/* Expect input pseudocode format after scope (If it create new scope). Containing “Keyword” like preIn. */
 	char postOut[64];		/* Output correct C format for end line. (If this function create new scope) */
 	char postVar[32];		/* List of “Keyword” for the end line in order to be print out in C syntax. */
 	char varType[2];		/* Type of variable that allowed in this function. (i = int, d = double, c = char, s = string) */
 	char fChild[16];		/* Other function “Key” that allow to be use without create a new scope */
 	char description[128];	/* Description of function showing in help menu. */
 	} RULE_T;

/* 2. Temporary Data (tempData Module)
 * Structure that handle the data related to “Keyword” in function rules.
 *These data will be retrieve from input pseudo code, check and updated related data, and then use to write output file along the valid C syntax. 
 */
typedef struct 	
	{
 	char $con[128];			/* Condition statement */
 	char $v_name[16];		/* Variable name */
	char $v_type[64];		/* Type of variable (Related to v_name) */
	char $v_symbol[4];		/* Symbol of that variable type (%d,%lf,%c,%s) (Related to v_name) */
	char $value[64];		/* Value or calculation statement that give a value */
	char $increm[4];		/* For loop increment (—,++) */
	char $f_pointer[8];		/* File pointer */
	char $f_path[16];		/* File path/name (Related to f_pointer) */
	char $f_mode[8];		/* File open mode (“r” = read, “w” = write) (Related to f_pointer) */
	} TEMP_T;

/* 3. Variable Sorted-Tree (globalData Module)
	Linked-list that contain a variable that user declared. */
typedef struct _variable
	{
	char name[16];				/* Variable name */
	char type[8];				/* Variable type */
	char symbol[64];			/* Symbol of that variable */
	struct _variable *pNext;	/* Pointer to next item */
	} VARIABLE_T;

/* 4. File handle Linked-List (globalData Module)
	Linked-list that contain a data of file that user open. */
typedef struct _file
	{
	char handle[16];		/* Name of pointer file handle */
	char path[32];			/* Variable type */
	char mode[4];			/* Symbol of that variable */
	struct _file *pNext;	/* Pointer to next item */
	} FILE_T;

/* 5. Nested function stack (globalData Module)
	Stack linked-list of postIn when the function are nested. */
typedef struct _nest
	{
	char postIn[16];		/* postKey of the function that create a new scope (nested) */
	struct _nest *pNext;	/* Pointer to next item in stack */
	} NEST_T;

/* Clear screen function */
void clearScr();