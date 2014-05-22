/*
 * Programmer: Corey Acri
 * Date: 10/04/99
 * File: Lab092.c
 * Purpose: Lab program to practice with arrays, pointers, and pass by
 * reference
 * Known Bugs: None
 */

#include <stdio.h>

/**3**/
void PrintArray(int *a, int NumEls);
void GetInsert(int, int *, int *);
void insert(int a[], int *, int, int);


/**********************************main**************************************/
main()
{
	int a[20] = {14, 17, 23, 26, 33, 38, 39, 41, 52, 56},
		NumEls = 10,	/* number of elements in array */
		InsertIndex,	/* index of element to insert */
		item,			/* item to insert */
		*ptr = a;			/* pointer to array */
      int dummy;
	/**2**/
	printf("The tenth array element is %d\n\n", *(ptr + 9));

	/**6**/
	PrintArray(ptr, NumEls);

	GetInsert(NumEls, &item, &InsertIndex);

	printf("Insertion %d at %d requested :\n", item, InsertIndex);
  	insert(a, &NumEls, item, InsertIndex);
 	PrintArray(a, NumEls);



	scanf("%d",&dummy);        /*if done in DOS */
	return 0;
}
/******************************************************************************/



/**************************************************************
 	PrintArray
   -----------------------------------------------------------
 * Function to print the first NumEls elements of array a
 * Pre:  a is an integer array.
 *       NumEls is the number of elements in a.
 * Post: The first NumEls elements of a have been printed.
***************************************************************/
/**4**/
void PrintArray(int *a, int NumEls)
{
	int i;

	printf("Array a has %d elements: ", NumEls);
	for(i = 0; i < NumEls; i++)
		printf("%3d", a[i]);		/**5**/
	printf("\n\n");
}



/*****************************************************************
   GetInsert
   ---------------------------------------------------------------
 * Function to read and send back an integer item (through
 * dereferencing item_ptr) to insert in array a and  to read and
 * send back the index (through dereferencing InsertIndex_ptr)
 * of where to insert.  Verify that the index is less than or
 * equal to NumEls
 * Pre:  NumEls is the number of elements in array a.
 * Post: item_ptr points to an item to insert into the array.
 *       InsertIndex_ptr references the index of where to insert.
 ******************************************************************/
void GetInsert(int NumEls, int *item_ptr, int *InsertIndex_ptr)
{
	printf("What do you want to insert? ");
	scanf("%d", item_ptr);
	do
	{
		printf("Give the index <= %d where to insert ", NumEls);
		scanf("%d", InsertIndex_ptr);
	}
	while (*InsertIndex_ptr < 0 || NumEls < *InsertIndex_ptr) ;
}



/***************************************************************
   insert
   -------------------------------------------------------------
 * Function to insert item at index InsertIndex in array
 * leaving the other array elements in order and increasing
 * the number of array elements by 1
 * Pre:  a is an integer array.
 *       item is the element to insert in array a.
 *       InsertIndex is the index of where to insert item in a.
 * Post: NumEls_ptr points to the number of elements in array a.
 ***************************************************************/
void insert(int a[], int *NumEls_ptr, int item, int InsertIndex)
{
	int i;

	for(i = *NumEls_ptr - 1; i >= InsertIndex; i--)
		a[i + 1] = a[i];

	a[InsertIndex] = item;
	*NumEls_ptr = *NumEls_ptr+1;
}


