/* Main data structure - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survived */

/* 1. Rules Database (dbAccess Module)
 * Array of structure which each structure contain rules of function. 
 * These data are read from database (csv file) when the program start. */
typedef struct
 	{
 	char name[16];
 	char key[16];
 	char preIn[64];
 	char preOut[64];
 	char preVar[32];
 	char postKey[16];
 	char postIn[64];
 	char postOut[64];
 	char postVar[32];
 	char fChild[16];
 	char description[128];
 	} RULE_T;

/* 2. Temporary Data (tempData Module)
 * Structure that handle the data for current function that relative to function rules. 
 * Each type will be handle differently. */
typedef struct 	
	{
 	char $con[64];
 	char $v_name[16];
	char $v_type[64];
	char $v_symbol[4];
	char $value[64];
	char $increm[4];
	char $f_pointer[8];
	char $f_path[16];
	char $f_mode[8];
	char $key[64];
	} TEMP_T;

/* 3. Variable Sorted-Tree (globalData Module)
	Tree that contain a variable that user declared. */
typedef struct _variable
	{
	char name[16];
	char type[8];
	char symbol[64];
	struct _variable *leftChild;
	struct _variable *rightChild;
	} VARIABLE_T;

/* 4. File handle Linked-List (globalData Module)
	Linked list that contain a data of file that user open. */
typedef struct _file
	{
	char handle[16];
	char path[32];
	char mode[4];
	struct _file *pleft;
	struct _file *pright;
	struct _file *pNext;
	} FILE_T;

/* 5. Nested function stack (globalData Module)
	Stack linked-list of postIn when the function are nested. */
typedef struct _nest
	{
	char postIn[16];
	struct _nest *pNext;
	} NEST_T;
