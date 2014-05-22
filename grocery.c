/*   
 * Example 11.5   
 * Program to read grocery items and prices from a file.  The    
 * user types a sequence of item names and quantities, and     
 * the program prints the unit price and total price.   
 *   
 * Input file name read interactively.  Each line of the    
 * file contains a price and a blank followed immediately   
 * by its name
 *
 * Errors:  The error lied in an extra space in the data file   
 */   
   
#include <stdio.h>   
#include <string.h>   
#include <stdlib.h>   
   
#define MAX_NUM_CHARS 21   
#define MAX_NUM_ELS   500   
#define PERIOD '.'   
#define TRUE  1   
#define FALSE 0   
   
typedef char string_t[MAX_NUM_CHARS];	/* string type */   
   
typedef 	/* structure type for item name and price */   
struct	   
{   
	string_t name;   
	float price;   
}   
el_t;   
   
main()
{   
	void directions(void);   
	FILE *InitFile(const string_t);   
	void FileToArray(el_t item[],    
			int *NumEls_ptr, FILE *infile_ptr);   
	void GroceryList(el_t item[], int NumEls);   
   
	el_t item[MAX_NUM_ELS];	/* array of structures */   
								/* of names and prices */	   
	int NumEls;				/* number of elements in array item */   
	FILE *infile_ptr;			/* pointer to input file */   
   
	directions();
	printf("Give the name of the input file: ");   
	infile_ptr = InitFile("r");   
	FileToArray(item, &NumEls, infile_ptr);   
	fclose(infile_ptr);   
   
	GroceryList(item, NumEls);   
}   
   
/*   
 * Program directions   
 * Pre:   none   
 * Post:  Directions were displayed.   
 */   
   
void directions(void)
{   
	printf("This program reads grocery names and prices\n");
	printf("from a file. The user enters an item name and\n");   
	printf("quantity and the program returns the total.\n\n");   
}   
   
/*   
 * Function to read the name of file and open file in the   
 * argument's mode.  If trouble opening, print error message     
 * and abort.  If not, return file pointer.   
 * Pre:   mode is a string variable holding "r" or "w".   
 * Post:  Error message was displayed or file pointer was   
 *        returned.   
 */   
   
FILE *InitFile(const string_t mode)   
{   
	FILE *file_ptr;		/* pointer to input file */   
	string_t filename;	/* name of file */   
   
	/* read file name and open the file */   
	gets(filename);   
	file_ptr  = fopen(filename, mode);   
	if (file_ptr == NULL)
	{
		printf("Error opening file %s.\n", filename);
		exit(1);
	}
	return file_ptr;
}

/*
 * Function to read file pointed to by infile_ptr into array
 * item.  Send back item and pointer to number of elements,
 * NumEls_ptr.  Data in file assumed to have on each line
 * one price and a blank followed immediately by its name.
 * Pre:   infile_ptr is a file pointer to the input file.
 * Post:  item is an array of structures; each element
 *        contains name and price.
 *        NumEls_ptr is a pointer to number of elements in
 *        item (NumEls in main).
 */

void FileToArray(el_t item[], int *NumEls_ptr,
		FILE *infile_ptr)
{
    int i = 0;	/* index */
    char ch;
	/* read price and name from file, store in array */
	while ((i < MAX_NUM_ELS) &&
			(fscanf(infile_ptr, "%f", &item[i].price) == 1))
	{
		ch = getc(infile_ptr);	/* read past blank after price */
		if (fgets(item[i].name, MAX_NUM_CHARS, infile_ptr)
				== NULL)
		{
			printf("ERROR: no name for last data item\n");
			exit(1);
		}
		else
		{
			if (item[i].name[strlen(item[i].name) - 1] == '\n')
				item[i].name[strlen(item[i].name) - 1] = '\0';   
			fflush(infile_ptr);   
			i++;   
		}   
	}   
	   
	if ((i == MAX_NUM_ELS)  && !feof(infile_ptr))	/* out of room */   
	{   
		printf("ERROR:  array not large enough\n");
		exit(1);   
	}   
	else if (!feof(infile_ptr))				/* error reading price */   
	{   
		printf("ERROR reading price from file\n");   
		exit(1);   
	}   
	   
	*NumEls_ptr = i;   
}   
   
/*   
 * Function repeatedly to read a grocery item and quantity,    
 * search for its name in the item array, retrieve its unit       
 * price, read quantity, print unit price and total price.   
 * Pre:  item is an array of structures; each element    
 *       contains name and price.   
 *       NumEls is the number of elements in item.   
 * Post: Quantities and unit prices were printed.   
 */   
   
void GroceryList(el_t item[], int NumEls)   
{   
	string_t SearchName;	/* item name entered by user */   
	int i,					/* index */   
		quantity,			/* number of an item */   
		found;				/* becomes TRUE if item name in list */   
	   
	printf("\nEnter an item name (. to stop): ");   
	gets(SearchName); 	   
	while (*SearchName != PERIOD)   
	{   
		/* sequential search for SearchName in item names */   
		found = FALSE;   
		i = 0;   
		while (!found && i < NumEls)   
		{   
			if (strcmp(item[i].name, SearchName) == 0)   
				found = TRUE;   
			else   
				i++;   
		}   
		   
		if (found)   
		{   
			printf("Enter quantity: ");   
			scanf("%d", &quantity);   
			printf("Unit price = $%.2f, ", item[i].price);   
			printf("total price = $%.2f.\n",   
					quantity * item[i].price);   
		}   
		else	/* not found */   
			printf("\nItem \"%s\" is not in the list.\n",    
					SearchName);   
	   
		fflush(stdin);   
		printf("\nEnter an item name (. to stop): ");   
		gets(SearchName); 	   
	}   
	   
	printf("Thank you.\n");   
}   
