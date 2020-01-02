/********************************************************************************************************************
*	File: Lex.c
*	Name: Andrew Craig
*	CruzID: 1746116
*	Assignment: pa1
*********************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 128

int main(int argc, char* argv[])
{
	int n = 0;
	int i = 0;
	FILE *in;
	FILE *out;
	char line[MAX_LEN];
	char* token;
	char** A;

	//Check for appropriate number of arguments. 
	if(argc != 3)
	{
		fprintf(stderr, "Lex Error: incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	//Open up input and output files.
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	//Check to see if the files were successfully opened.
	if(in == NULL)
	{
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(out == NULL)
	{
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	//Count the number of lines in the input file.
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		n++;
	}
	
	//Allocate space for an array based on the number of lines in the input file.
	A = calloc(n, sizeof(char*));

	for(i = 0; i < n; i++)
	{
		A[i] = malloc(MAX_LEN * sizeof(char));
	}
	
	rewind(in);
	i = 0;

	//Store each line of the input file into the array.
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		token = strtok(line, "\n");
		strcpy(A[i], token);
		i++;		
	}

	//Store the indices of the array into a List.
	//The indices will be arranged in the list based on lexicographic order.
	//This arrangement will indirectly sort the array.
	List L = newList();
	prepend(L, 0);

	for(i = 1; i < n; i++)
	{
		moveFront(L);
		while((index(L) != -1) && (strcmp(A[i], A[get(L)]) > 0))
		{
			moveNext(L);
		}

		if(index(L) == -1)
		{
			append(L, i);
		}
		else
		{
			insertBefore(L, i);
		}
		
	}

	//Print the contents of the array using the List to display them in lexicographic order.
	moveFront(L);
	for(i = 0; i < n; i++)
	{
		fprintf(out, "%s\n", A[get(L)]);
		moveNext(L);
	}

	//Deallocate the array and the List to avoid memory leaks.
	for(i = 0; i < n; i++)
	{
		free(A[i]);
	}
	free(A);
	freeList(&L);

	//Close input and output files.
	fclose(in);
	fclose(out);

	return(0);
}