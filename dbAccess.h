/* DB Accessing Module Header File - Pseudo2C Project
 * 
 * Withee Poositasai (Lookkid) 58070503429
 * Team We Must Survived */

 /* Import rules to array from rules file 
 *	Return:	1 = Success
 *			0 = Can't open input file
 *			-1 = Can't read count
 *			-2 = Allocation error
 */
int prepareDB();

/* Extract property from each rule into a structure
 *	Argument:	target = Name of property in structure
 *				buffer = line buffer
 */
void extractProperty(char* target,char* buffer);

/* Get rule structure pointer from keyword
 *	Argument:	target = Search by 'k' (key) or 'n' name
 *				keyword = Keyword to search
 *	Return:	Matched RULE_T structure pointer if keyword found, NULL if not
 */
RULE_T* getRule(char target,char keyword[]);

/* Get number of rules 
 * Return: number of rule in array 
 */
int countRule();

/* Get number of rules 
 * Argument:	nameList = array to store each rule name
 * Return: total rule name that added to array
 */
int getAllRuleName(char** nameList);

/* Free the rules database
 */
void freeDB();