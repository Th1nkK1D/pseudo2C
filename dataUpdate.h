/*
 * dataUpdate.h
 * 
 * A header file that contains all functions from dataUpdate.c
 * Use for checking and storing string of line into temporary structure.
 * 
 * Created by Siriwimon Suksukhon (Poo), ID 3436
 * - Team We Must Survived -
 * 17 April 2016
 */

/* Function for store all data in that line into the structure
 * Argument :
 * rule => rule for that line.
 * line => string of that line.
 * data => stucture for hold all data in line.
 * Return :
 * 0 => if the string is not follow the instruction
 * 1 => if the string is fine and update temporary data already
 */
int dataUpdate (RULE_T* rule,char line[],TEMP_T* data);
