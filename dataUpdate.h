/*
 * dataUpdate.h
 * A header file that contains all functions from dataUpdate.c
 * Use for checking and storing string of line into temporary structure.
 * 
 * Created by Siriwimon Suksukhon (Poo), ID 3436
 * 17 April 2016
 */

/* Function to check that line is in correct format 
 * Argument : 
 * pre_post_in => correct format of that line
 * lineCopied => string of that line
 * Return :
 * 1 => if it is in correct format
 * 0 => if it's not
 */
int checkFormat (char pre_post_in[], char lineCopied[]);

/* Function to find dollar sign
 * Argument :
 * input => string that we want to look
 * Return :
 * 1 => if it has a dollar sign
 * 0 => if not
 */
int findDollar (char input[]);

/* Function for store all data in that line into the structure
 * Argument :
 * rule => rule for that line.
 * line => string of that line.
 * data => stucture for hold all data in line.
 * Return :
 * -1- => if that line or that rule is NULL.
 * 0 => if that line does not be in the correct format.
 * 1 => if line is in correct format and update data in structure already.
 */
int dataUpdate (RULE_T* rule,char line[],TEMP_T* data);
