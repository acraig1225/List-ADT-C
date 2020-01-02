#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[])
{
	List L = newList();
	int i;
	//FILE* out = fopen("out.txt", "w");

	for(i=1; i<=3; i++)
	{
		append(L, i);
	}

	moveFront(L);
	printf("First index: %d\n", index(L));
	
	moveNext(L);
	printf("Second index: %d\n", index(L));

	return(0);
}