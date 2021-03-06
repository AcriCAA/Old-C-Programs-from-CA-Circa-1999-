/*
 * Programmer: Corey Acri
 * File: Lab091.c (text with malloc)
 * Date: 10/04/99
 * Purpose: Program to print an area of memory
 * Known Bugs: None
 */

#include <stdio.h>
#include <stdlib.h>

void AlphaInit(unsigned char *);

#define NUM_LINES 10
#define NUM_BLOCKS 5

main()
{
	unsigned char *p,				/* pointer to a character */
	              *start_ptr;	/* pointer to allocated area */
	int LineNum, 					/* index to line */
		BlockNum, 					/* index to block of 4 bytes on line */
		ByteNum, 					/* index to byte in block */
   	dummy;                  /* dummy for DOS window   */

	if ((start_ptr=(unsigned char*)malloc((NUM_LINES * NUM_BLOCKS ) * 4))== NULL )
	{
		printf("Memory could not be allocated.\n");
		exit(1);
	}

	/* Part c:  Initialize first 26 bytes to A through Z */
	 AlphaInit(start_ptr);

	printf("Address\t\t\t\tMemory\n\n");

	p = start_ptr;				/* starting location */
	for (LineNum = 0; LineNum < NUM_LINES; LineNum++)
	{
		printf("%p  ", p++);	/*address at first of line */

		for (BlockNum = 0; BlockNum < NUM_BLOCKS; BlockNum++)
		{
			for (ByteNum = 0; ByteNum < 4; ByteNum++)
				printf(" %2x", *p++);

			printf("  ");
		}
		printf("\n");
	}

	scanf("%d",&dummy);	/*Dummy scanf for DOS */
	return 0;
}



/***************************************************************
   AlphaInit
   -------------------------------------------------------------
 * Function to initialize 26 bytes starting with start_ptr
 * with A through Z
 * Pre:  start_ptr is the starting address.
 * Post: The first 26 bytes starting with location start_ptr
 *       have been initialized with letters of the alphabet.
 **************************************************************/
void AlphaInit(unsigned char *start_ptr)
{
	unsigned char *p;
	int i;

	p = start_ptr;
	for (i = -1; i < 26; i++)
	{
		*p = 'A' + i;
		p++;
	}
}


