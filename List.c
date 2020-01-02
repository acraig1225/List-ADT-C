/********************************************************************************************************************
*	File: List.c
*	Name: Andrew Craig
*	CruzID: 1746116
*	Assignment: pa1
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//Node Implementation************************************************************************************************
typedef struct NodeObj
{
	int data;
	struct NodeObj* previous;
	struct NodeObj* next;
} NodeObj;

typedef struct NodeObj* Node;

//Description: Creates and returns a new empty Node.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->previous = NULL;
	N->next = NULL;
	return (N);
}

//Description: Frees all heap memory associated with *pN, and sets *pN to NULL.
void freeNode(Node* pN)
{
	if(*pN != NULL && pN != NULL)
	{
		free(*pN);
		*pN = NULL;
	}
}

//List Implementation************************************************************************************************
typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//Constructors-Destructors*******************************************************************************************
//Description: Creates and returns a new empty List.
List newList(void)
{
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return (L);
}

//Description: Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL)
{
	if(*pL != NULL && pL != NULL)
	{
		while(length(*pL) != 0)
		{
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//Access Functions***************************************************************************************************
//Description: Returns the number of elements in List L.
int length(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	return (L->length);
}

//Description: Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(L->cursor == NULL)
	{
		return -1;
	}
	return (L->index);
}

//Description: Returns front element of List L.
//Precondition: length() > 0
int front(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling front() on an empty List\n");
		exit(EXIT_FAILURE);
	}

	return L->front->data;
}

//Description: Returns back element of List L.
//Precondition: length() > 0
int back(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling back() on an empty List\n");
		exit(EXIT_FAILURE);
	}

	return L->back->data;
}

//Description: Returns cursor element of List L.
//Precondition: length() > 0 & index() >= 0
int get(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling get() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		printf("List Error: calling get() on an undefined cursor\n");
		exit(EXIT_FAILURE);
	}

	return L->cursor->data;
}

//Description: Returns true if and only if Lists A and B are in the same state, otherwise returns false.
int equals(List A, List B)
{
	Node N = NULL;
	Node M = NULL;
	int compare;

	if(A == NULL || B == NULL)
	{
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);		
	}

	if(length(A) != length(B))
	{
		return 0;
	}

	N = A->front;
	M = B->front;

	while(N != NULL && M != NULL)
	{
		compare = (N->data == M->data);
		if(!compare)
		{
			return 0;
		}
		N = N->next;
		M = M->next;
	}
	return 1;
}

//Manipulation Procedures********************************************************************************************
//Description: Resets List L to its original empty state.
void clear(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	while(L->front != NULL)
	{
		deleteFront(L);
	}
	L->cursor = NULL;
	L->index = -1;
}

//Description: If List L is non-empty, sets the cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(length(L) > 0)
	{
		L->cursor = L->front;
		L->cursor->next = L->front->next;
		L->index = 0;
	}
}

//Description: If List L is non-empty, sets the cursor under the last element, otherwise does nothing.
void moveBack(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(length(L) > 0)
	{
		L->cursor = L->back;
		L->index = length(L) - 1;
	}
}

//Description: If the cursor is defined and not at the front, move the cursor one step towards the front of List L; 
//if the cursor is defined and at the front, cursor becomes undefined; if cursor is undefined do nothing.
void movePrev(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(index(L) != -1)
	{
		if(L->cursor == L->front)
		{
			L->cursor = NULL;
			L->index = -1;
		}
		else if(L->cursor != L->front)
		{
			L->cursor = L->cursor->previous;
			L->index--;
		}
	}
}

//Description: If the cursor is defined and not at back, move cursor one step towards the back of List L; 
//if the cursor is defined and at the back, the cursor becomes undefined; if the cursor is undefined do nothing
void moveNext(List L)
{
	if(L == NULL)
	{
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(index(L) != -1)
	{
		if(L->cursor == L->back)
		{
			L->cursor = NULL;
			L->index = -1;
		}
		else if(L->cursor != L->back)
		{
			L->cursor = L->cursor->next;
			L->index++;
		}
	}
}

//Description: Insert new element into List L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data)
{
	Node N = newNode(data);

	if(L == NULL)
	{
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	
	if(!length(L))
	{
		L->front = N;
		L->back = N;
	}
	else
	{
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
	}
	L->length++;
	L->index++;
}

//Description: Insert new element into List L. If L is non-empty, insertion takes place after back element.
void append(List L, int data)
{
	Node N = newNode(data);
	
	if(L == NULL)
	{
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(!length(L))
	{
		L->front = N;
		L->back = N;
	}
	else
	{
		L->back->next = N;
		N->previous = L->back;
		L->back = N;
	}
	L->length++;
}

//Description: Insert new element before cursor.
//Precondition: length() > 0 & index() >= 0
void insertBefore(List L, int data)
{
	Node N = newNode(data);
	
	if(L == NULL)
	{
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling insertBefore() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		printf("List Error: calling insertBefore() on an undefined cursor\n");
		exit(EXIT_FAILURE);
	}

	if(L->front == L->cursor)
	{
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
	}
	else
	{
		N->previous = L->cursor->previous;
		N->next = L->cursor;
		L->cursor->previous = N;
		N->previous->next = N;
	}
	L->length++;
	L->index++;
}

//Description: Insert new element after cursor.
//Precondition: length() > 0 & index() >= 0
void insertAfter(List L, int data)
{
	Node N = newNode(data);

	if(L == NULL)
	{
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		printf("List Error: calling insertAfter() on an undefined cursor\n");
		exit(EXIT_FAILURE);
	}

	if(L->back == L->cursor)
	{
		L->back->next = N;
		N->previous = L->back;
		L->back = N;
	}
	else
	{
		N->next = L->cursor->next;
		N->previous = L->cursor;
		L->cursor->next = N;
		N->next->previous = N;
	}
	L->length++;
}

//Description: Deletes the front element of List L.
//Precondition: length() > 0
void deleteFront(List L)
{
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	
	if(L->front == L->cursor)
	{
		L->cursor = NULL;
		L->index = -1;
	}
	else
	{
		L->index--;
	}

	N = L->front;
	if(length(L) > 1)
	{
		L->front = L->front->next;
		L->front->previous = NULL;
	}
	else
	{
		L->front = NULL;
		L->back = NULL;
	}
	L->length--;
	freeNode(&N);
}

//Description: Deletes the back element of List L.
//Precondition: length() > 0
void deleteBack(List L)
{
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling deleteBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}

	if(L->back == L->cursor)
	{
		L->cursor = NULL;
		L->index = -1;
	}

	N = L->back;
	if(length(L) > 1)
	{
		L->back = L->back->previous;
		L->back->next = NULL;
	}
	else
	{
		L->front = NULL;
		L->back = NULL;		
	}
	L->length--;
	freeNode(&N);
}

//Description: Delete cursor element, making the cursor undefined.
//Precondition: length() > 0 & index() >= 0
void delete(List L)
{
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!length(L))
	{
		printf("List Error: calling delete() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0)
	{
		printf("List Error: calling delete() on an undefined cursor\n");
		exit(EXIT_FAILURE);
	}

	N = L->cursor;
	if(length(L) == 1)
	{
		L->front = NULL;
		L->back = NULL;
	}
	else if(L->front == L->cursor)
	{
		L->front = L->front->next;
		L->front->previous = NULL;
	}
	else if(L->back == L->cursor)
	{
		L->back = L->back->previous;
		L->back->next = NULL;
	}
	else
	{
		L->cursor->previous->next = L->cursor->next;
		L->cursor->next->previous = L->cursor->previous;
	}
	L->cursor = NULL;
	L->index = -1;
	L->length--;
	freeNode(&N);
}


//Other Operations***************************************************************************************************
//Description: Prints to the file point to by out, a string representation of List L consisting of a space 
//separated by a sequence of integers, with front on the left.
void printList(FILE* out, List L)
{
	Node N = NULL;
	int i;

	if(L == NULL)
	{
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		printf("List Error: calling printList() on NULL FILE reference\n");
		exit(EXIT_FAILURE);
	}

	N = L->front;
	for(i = 0; i < length(L); i++)
	{
		fprintf(out, "%d ", N->data);
		N = N->next;
	}
}

//Description: Returns a new List representing the same integer sequence as List L. The cursor in the new list  
//is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L)
{
	List nL = newList();
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	N = L->front;
	while(N != NULL)
	{
		append(nL, N->data);
		N = N->next;
	}
	return (nL);
}

//Description: Returns a new List which is the concatenation of A and B. The cursor in the new List 
//is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged.
List concatList(List A, List B)
{
	List C = NULL;
	Node N = NULL;

	if(A == NULL || B == NULL)
	{
		printf("List Error: calling concatList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	C = copyList(A);
	N = B->front;
	while(N != NULL)
	{
		append(C, N->data);
		N = N->next;
	}
	return (C);
}