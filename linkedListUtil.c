/**
 *  linkedListUtil.c
 *
 *  Utility linked list module
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

#include <stdlib.h>
#include <stdio.h>
#include "linkedListUtil.h"


/* Structure that represents one item of the list */
typedef struct _listitem
{
    void* pData;               /* Pointer to the data for this node */
    struct _listitem * pNext;  /* Link to the next item in the list */
} LISTITEM_T;

/* Structure to represent a list. Keeps track of head and tail of the 
 * list as well as the current node (for iterating through the list)
 */
typedef struct
{
    LISTITEM_T * head;    /* first item in list */  
    LISTITEM_T * tail;    /* last item in the list */
    LISTITEM_T * current; /* current item in the list */ 
} LIST_T;


/****************************************
 * Public functions
 */

/* Creates a new list, empty list.
 * Returns a pointer to the created list, or NULL if a memory allocation
 * error occurs. All other public functions require the list pointer
 * as their first argument.
 */
LIST_HANDLE newList()
{
    LIST_T * linkedList = NULL;
    linkedList = (LIST_T*) calloc(1,sizeof(LIST_T));
    /* note that since we use calloc, the head, tail and current 
     * will all be initialized to NULL
     */
    return (LIST_HANDLE) linkedList;
}


/* Frees all memory associated with this list, that is
 * the list items and the list structure itself.
 * Does not free the data.
 * Arguments
 *   linkedList  -   list to free. Once this function is called
 *                   this pointer is no longer valid
 */
void listDestroy(LIST_HANDLE list)
{
    LIST_T * linkedList = (LIST_T*) list;
    if (linkedList != NULL) /* if list has been initialized  */
       {
       LISTITEM_T * pThisItem = linkedList->head;
       while (pThisItem != NULL)
          {
	  LISTITEM_T * pNext = pThisItem->pNext;
	  free(pThisItem);        /* Free the item itself */
	  pThisItem = pNext;      /* Reset current item to next item in
				   * the list if any. If pNext is null
				   * then we are at the end of the list
				   * and the loop will exit.
				   */
	  }
       free(linkedList);
       }
}

/* Find out how many items currently are stored in the passed list
 * Arguments
 *   linkedList  -   list to whose size we want to know
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize(LIST_HANDLE list)
{
   int count = 0;
   LIST_T * linkedList = (LIST_T*) list;
   if (linkedList == NULL)
      {
      count = -1;  /* invalid list - just ignore */
      }
   else
      {
      /* Traverse the list and count */
      /* This could also be implemented by keeping track 
       * in the LIST_T structure every time we insert or remove
       * an item.
       */
      LISTITEM_T * pThisItem = linkedList->head;
      while (pThisItem != NULL) /* if list is empty, we will never */
                                /* enter the loop, and count will be 0 */
         {
	 count += 1;    
	 pThisItem = pThisItem->pNext;
	 }
      }
   return count;
}

/* Add a new element to the end of a list
 * Arguments:
 *   linkedList  -   list we want to add to
 *   data        -   pointer to the information to store in the list
 * Returns the 1 if successful or 0 if the list is not initialized.
 * Returns -1 if a memory allocation error occurs.
 */
int listInsertEnd(LIST_HANDLE list, void * data)
{
   int retval = 1;  /* assume success */
   LIST_T * linkedList = (LIST_T*) list;
   if (linkedList == NULL)
       retval = 0;  /* not initialized */
   else 
       {
       LISTITEM_T * pTail = linkedList->tail;
       LISTITEM_T * pNew = (LISTITEM_T *) calloc(1,sizeof(LISTITEM_T));
       if (pNew == NULL)
          {
	  retval = -1;  /* allocation error */
          }
       else  /* allocation succeeded, so we can continue */
          {
          pNew->pData = data; /* store data in the item */
	  if (pTail == NULL)  /* if the list is currently empty */
             {
	     linkedList->head = pNew;  /* new item is head as well as tail*/
	     linkedList->current = pNew;
	     }
	  else
             {
	     pTail->pNext = pNew;     /* add the item as the next
				       * item after the current 'tail
				       */
	     }
	  linkedList->tail = pNew;  /* Either way, now our new item 
				     * is the tail
				     * (last item on the list)
				     */
	  }  /* end else allocation is okay */
       }
   return retval;
}

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
void* listRemove(LIST_HANDLE list, int position)
{
   void* data = NULL;
   LIST_T * linkedList = (LIST_T*) list;
   /* If list exists and has any items*/
   if ((linkedList != NULL) && (linkedList->head != NULL))
      {
      int size = listSize(linkedList);
      LISTITEM_T * pRemoveItem = NULL;
      if (position == 0)  /* first item in the list */
          {
	  pRemoveItem = linkedList->head;
          linkedList->head = pRemoveItem->pNext;
          }
      else 
          {
	  int count = 0;
          if (position >= size)   /* adjust so we won't run off end of list */  
	      position = size-1;
	  LISTITEM_T* pThis = linkedList->head;
          LISTITEM_T* pPrev = NULL;
	  while ((pThis != NULL) && (count < position))
	    {
	    pPrev = pThis;
	    pThis = pThis->pNext;
            count++;		
	    }
	 pRemoveItem = pThis;
         pPrev->pNext = pRemoveItem->pNext;
         }
      data = (void*) pRemoveItem->pData;
      if (size == 1)   /* if we just took the last item off the list */
         {
	 linkedList->head = linkedList->tail = linkedList->current = NULL;
	 /* reset all the pointers to NULL */
	 }            
      /* Reset current to the beginning of the list if
       * it was pointing to the item about to be freed 
       */
      if (linkedList->current == pRemoveItem) 
          linkedList->current = linkedList->head; 
      free(pRemoveItem);          
      }
   return data;  /* Will be null if list was empty or handle was invalid */
}

/* Resets the "current" list pointer to the beginning
 * of the list.
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Returns 1 if successful, 0 if the list is empty,
 * -1 if the list has not been initialized.  
 */
int listReset(LIST_HANDLE list)
{
   int retval = 1;  /* assume success */ 
   LIST_T * linkedList = (LIST_T*) list;
   if (linkedList == NULL)
       retval = -1;  /* list not initialized */
   else if (linkedList->head == NULL)
       retval = 0;   /* list is empty */
   else  /* Just set current to be the head of the list */
      {
      linkedList->current = linkedList->head;
      }
   return retval;
}

/* Returns the data stored at the "current" list 
 * position, then moves the current position to the 
 * next position in the list.
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Returns data if successful, null if we are
 * already at the end of the list or if the
 * list has not been initialized.  
 */
void* listGetNext(LIST_HANDLE list)
{
   void * data = NULL;
   LIST_T * linkedList = (LIST_T*) list;
   /* If the list has been initialized */
   if (linkedList != NULL)
      {
      /* if there are any items in the list 
       * and we are not already at the end
       */ 
      if (linkedList->current != NULL)	  
         {
         data = linkedList->current->pData;
	 /* advance the current pointer to the next item */
         linkedList->current = linkedList->current->pNext;
         }
      }
   return data;
}

/* Find out if the current list position is past the
 * end. 
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Return 1 if the position is past the end of the list,
 * Return 0 if the position is not past the end.
 * Return -1 if the list has not been initialized.
 */
int listAtEnd(LIST_HANDLE list)
{
   LIST_T * linkedList = (LIST_T*) list;
   int retval = 0;/* assume we are not at the end */
   if (linkedList == NULL)
       retval = -1;  /* invalid handle */
   else if (linkedList->current == NULL)
       retval = 1;   /* this means we're at the end */
   return retval;
}

