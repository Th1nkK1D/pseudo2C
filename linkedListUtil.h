/** 
 *  linkedListUtil.h
 *
 *  Header file for utility linked list module
 *  Used to create and manage lists that are part of other data
 *    structures.
 *
 *  Each call to newList() creates a new list and returns the pointer
 *  to that list. So by calling newList() multiple times, the calling
 *  program can create and manage many linked lists.
 *
 *  The list can hold any kind of data, via a void* pointer. It assumes
 *  that the calling program will manage the memory for that data,
 *  so it does not free it.
 *
 *  Created by Sally Goldin, 12 February 2013 for CPE113
 *
 */

/* opaque pointer to a list */
typedef void* LIST_HANDLE;

/* Creates a new list, empty list.
 * Returns a pointer to the created list, or NULL if a memory allocation
 * error occurs. All other public functions require the list pointer
 * as their first argument.
 */
LIST_HANDLE newList();


/* Frees all memory associated with this list, that is
 * the list items and the list structure itself.
 * Does not free the data.
 * Arguments
 *   linkedList  -   list to free. Once this function is called
 *                   this pointer is no longer valid
 */
void listDestroy(LIST_HANDLE list);


/* Find out how many items currently are stored in the passed list
 * Arguments
 *   linkedList  -   list to whose size we want to know
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize(LIST_HANDLE list);


/* Add a new element to the end of a list
 * Arguments:
 *   linkedList  -   list we want to add to
 *   data        -   pointer to the information to store in the list
 * Returns the 1 if successful or 0 if the list is not initialized.
 * Returns -1 if a memory allocation error occurs.
 */
int listInsertEnd(LIST_HANDLE list, void * data);

/* Removes the element at a specified position and
 * returns its data. Frees the list item but does not
 * free the data.
 * Arguments:
 *   linkedList  -   list we want to remove from
 *   position    -   position in the list to remove, where 0 is the head
 *                   of the list. If 'position' is larger than the number
 *                   of elements in the list, we simply remove the last element
 *                   rather than returning an error.
 * Returns the data for the item removed. 
 * Returns NULL if the list is empty or the list pointer is NULL
 */
void* listRemove(LIST_HANDLE list, int position);


/* Resets the "current" list pointer to the beginning
 * of the list.
 * Arguments:
 *   linkedList  -   list we want to set back to the start
 * Returns 1 if successful, 0 if the list is empty,
 * -1 if the list has not been initialized.  
 */
int listReset(LIST_HANDLE list);

/* Returns the data stored at the "current" list 
 * position, then moves the current position to the 
 * next position in the list.
 * Arguments:
 *   linkedList  -   list we are traversing
 * Returns data if successful, null if we are
 * already at the end of the list or if the
 * list has not been initialized.  
 */
void* listGetNext(LIST_HANDLE list);

/* Find out if the current list position is past the
 * end. 
 * Arguments:
 *   linkedList  -   list we are interested in
 * Return 1 if the position is past the end of the list,
 * Return 0 if the position is not past the end.
 * Return -1 if the list has not been initialized.
 */
int listAtEnd(LIST_HANDLE list);