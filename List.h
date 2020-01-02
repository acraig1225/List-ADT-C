/********************************************************************************************************************
*	File: List.h
*	Name: Andrew Craig
*	CruzID: 1746116
*	Assignment: pa1
*********************************************************************************************************************/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//Constructors-Destructors*******************************************************************************************
List newList(void);						//Creates and returns a new empty List.
void freeList(List* pL);				//Frees all heap memory associated with *pL, and sets *pL to NULL.

//Access Functions***************************************************************************************************
int length(List L);						//Returns the number of elements in List L.
int index(List L);						//Returns index of cursor element if defined, -1 otherwise.
int front(List L);						//Returns front element of List L.
										//Precondition: length() > 0
int back(List L);						//Returns back element of List L.
										//Precondition: length() > 0
int get(List L);						//Returns cursor element of List L.
										//Precondition: length() > 0 & index() >= 0
int equals(List A, List B);				//Returns true if and only if Lists A and B are in the same state,
										//otherwise returns false.

//Manipulation Procedures********************************************************************************************
void clear(List L);						//Resets List L to its original empty state.
void moveFront(List L);					//If List L is non-empty, sets the cursor under the front element,
										//otherwise does nothing.
void moveBack(List L);					//If List L is non-empty, sets the cursor under the last element,
										//otherwise does nothing.
void movePrev(List L);					//If the cursor is defined and not at the front, move the cursor one
										//step towards the front of List L; if the cursor is defined and at
										//the front, cursor becomes undefined; if cursor is undefined do nothing.
void moveNext(List L);					//If the cursor is defined and not at back, move cursor one step towards
										//the back of List L; if the cursor is defined and at the back, the
										//cursor becomes undefined; if the cursor is undefined do nothing
void prepend(List L, int data);			//Insert new element into List L. If L is non-empty, insertion takes
										//place before front element.
void append(List L, int data);			//Insert new element into List L. If L is non-empty, insertion takes
										//place after back element.
void insertBefore(List L, int data);	//Insert new element before cursor.
										//Precondition: length() > 0 & index() >= 0
void insertAfter(List L, int data);		//Insert new element after cursor.
										//Precondition: length() > 0 & index() >= 0
void deleteFront(List L);				//Deletes the front element of List L.
										//Precondition: length() > 0
void deleteBack(List L);				//Deletes the back element of List L.
										//Precondition: length() > 0
void delete(List L);					//Delete cursor element, making the cursor undefined.
										//Precondition: length() > 0 & index() >= 0

//Other Operations***************************************************************************************************
void printList(FILE* out, List L);		//Prints to the file point to by out, a string representation of List L
										//consisting of a space separated by a sequence of integers, with front
										//on the left.
List copyList(List L);					//Returns a new List representing the same integer sequence as List L.
										//The cursor in the new list is undefined, regardless of the state of
										//the cursor in L. The state of L is unchanged.

List concatList(List A, List B); 		//Returns a new List which is the concatenation of
 										//A and B. The cursor in the new List is undefined,
 										//regardless of the states of the cursors in A and B.
 										//The states of A and B are unchanged.

#endif