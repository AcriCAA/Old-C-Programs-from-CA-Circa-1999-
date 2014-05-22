/*
	Programmer: Corey Acri
   File: vending.c
   Data File: vending.dat
	Purpose: To construct a vending machine that dispenses items, updates the
   			inventory and returns the correct amount of change
   Input: The Items in the machine and their prices from a file, the amount of items
			 and coins to start with. Also the choices from and amount of money from
          the user
   Output: The item dipensed or an error message if exact change is not provided.
   			The amount of money in the change maker and the inventory.


   Known Bugs: To my belief the correct change is dispensed however sometimes there
   				may not be enough money in the changemaker to dispense the change or
               the money in the changemaker may be incorrect at the end.

 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define ITEMS 10
#define DOLLAR 1.00
#define QUARTER .25
#define DIME .10
#define NICKEL .05

/*********************************structs**************************************/
	typedef
	struct
	{
		char name[MAX];
   	float price;
      int amount;
	}
	item_t;

	typedef
	struct
	{

      float quarters;
      float dimes;
      float nickels;
   }
   coins_t;
/******************************************************************************/

/*********************************prototypes***********************************/
coins_t money (void);
void getcandy (int [], item_t []);
void scanfile(item_t []);
coins_t change(coins_t);
int printlist(item_t []);
coins_t insert (coins_t, float *);
float getnumber (void);
int numberItem (void);
void ChangeMaker (coins_t coins);
coins_t dispense (int, float *, item_t [],coins_t );
void delay (int);
coins_t return_coins(coins_t, float *);
void inventory (item_t []);

/*******************************main*******************************************/
main()
{


   int item[MAX];
   item_t candy[MAX];
   coins_t coins;
   float choice;      /* user's choice of which number to purchase */
   int cont = TRUE;   /* contine looping */

   float *u_money;    /* amount of money inserted by user */

	scanfile(candy);
   getcandy(item, candy);
	coins = money();

	while(cont == TRUE)
   {
      coins = change(coins);  /*change in machine */
   	delay(2);
      cont = printlist(candy);
      if (cont == FALSE)
      	break;
   	coins = insert(coins, &u_money);
   	choice = numberItem();
   	coins = dispense(choice,&u_money,candy,coins);
   	delay(3);
   	fflush(stdin);
   }

   	clrscr();
      inventory(candy);
   	ChangeMaker(coins);
      delay(3);
   	fflush(stdin);
      exit(1);


	return 0;
}
/******************************************************************************/



/*******************************************************************************
	inventory
--------------------------------------------------------------------------------
Purpose: To dispay the inventory left in the machine when the user chooses to
			exit
Pre: The struct candy contains the inventory information
Post: Prints the inventory list
*******************************************************************************/
void inventory (item_t candy [])
{

   int i;
   printf("Items remaining:\n");
 	for(i = 0; i < ITEMS; i++)
   	printf("%-25s$%.02f%20d\n", candy[i].name, candy[i].price, candy[i].amount);


}
/******************************************************************************/



/*******************************************************************************
	dispense
--------------------------------------------------------------------------------
Purpose: To give the user the item they choose to purchase and then call the \
			function to give them back their change or tell them they need exact
         change.

Pre: The user's amount of money the choice and the coins and candy structs are
		all passed to the function
Post: Dispenses the candy and change and updates the structs
*******************************************************************************/
coins_t dispense (int choice, float *u_money, item_t candy[], coins_t coins)
{
     float cost;
     float total;

     cost = candy[choice].price;
     total = coins.quarters + coins.dimes + coins.nickels;

     if (*u_money >= cost && candy[choice].price <= total)
     {
     	if(candy[choice].amount > 0)
         {
				printf("\nDispensing one %s\n", candy[choice].name);
        		candy[choice].amount--;

         *u_money = *u_money - cost;
         if (*u_money != cost)
         coins = return_coins(coins, u_money);

         return coins;
         }


     	else if (candy[choice].amount == 0)
     	{
     		printf("Sorry all out");
      	return coins;
     	}

     }

     else
     {
     	printf("Need Exact Change. Please Try Again");
      delay(3);
      return coins;
     }
     return coins;
}
/******************************************************************************/


/*******************************************************************************
	return_coins
--------------------------------------------------------------------------------
Purpose: To return the correct amount of change to the user
Pre: Their is enough change in the machine
Post: The correct change is dispensed and the  coins  is updated
*******************************************************************************/
coins_t return_coins (coins_t coins, float *u_money)
{
   int i = 0;

   if(*u_money > QUARTER)
   {
   		while(coins.quarters >= QUARTER && *u_money > 0)
      	{
   			coins.quarters -= QUARTER;
      		*u_money -= QUARTER;
         	i++;
      	}
      if(i == 4)
         	printf("\nReturning 1 dollar\n");
      else
      		printf("\nReturning %d quarters\n", i);
   }

   if (*u_money > DIME)
   {
   	i = 0;
      while(coins.dimes >= DIME && *u_money > 0 )
         {
         	coins.dimes -=  DIME;
            *u_money -= DIME;
            i++;
         }

         printf("Returning %d dimes\n", i);
   }


      i =0;
      while(/*coins.nickels >= NICKEL && */ *u_money > 0 )
         {
         	coins.nickels -=  NICKEL;
            *u_money -= NICKEL;
            i++;
         }
         printf("Returning %d nickels\n", i);


   	return coins;
}
/******************************************************************************/




/*******************************************************************************
	delay
--------------------------------------------------------------------------------
Purpose: to delay the output from being cleared from the screen
Pre: A amount of seconds to delay is passed to the fucntion
Post: None
*******************************************************************************/
void delay (int seconds)
{
   time_t cur_time = time((time_t *)NULL);
   while(time((time_t*)NULL) < cur_time + (time_t)seconds);
}
/******************************************************************************/



/*******************************************************************************
	ChangeMaker
--------------------------------------------------------------------------------
Purpose: To display the amount of money left in the machine
Pre: None
Post: The amount of money left in the machine is diplayed
*******************************************************************************/
void ChangeMaker (coins_t coins)
{
   float quarters, dimes, nickels;

	printf("\nMoney in Change Maker:\n");
   quarters = coins.quarters /QUARTER;

   if(quarters > 0)
   	printf("\n%1.0f quarter(s)\n", quarters);
   else
   	printf("0 quarters\n");
   dimes = coins.dimes/DIME;
   if (coins.dimes > 0)
   	printf("%1.0f dime(s)\n", dimes);
   else
   	printf("0 dimes\n");
   nickels = coins.nickels/ NICKEL;
   if (nickels > 0 )
   	printf("%1.0f nickel(s)\n", nickels);
   else
   	printf("0 nickels\n");

   delay(5);
}
/******************************************************************************/




/*******************************************************************************
	numberItem
--------------------------------------------------------------------------------
Purpose: To indincate the number of item to be purchased by the user
Pre:  None
Post: The choice is returned
*******************************************************************************/
int numberItem (void)
{

	float item;
   printf("\n\nIndicate the Number of Item to be purchased:  ");
   item = getnumber();
   item--;
   return item;

}
/******************************************************************************/



/*******************************************************************************
	insert
--------------------------------------------------------------------------------
Purpose: To get the coins being inserted from the user
Pre: None
Post: The coins struct is updated and returned
*******************************************************************************/
coins_t insert (coins_t coins, float *u_money)
{
   float n_coins;     /* number of coins being inserted by the user */

   float u_dollar, u_quarter, u_dime, u_nickel; /* $ amount of each coin */

  	printf("indicate how many are being inserted:\n");
   printf("\nDollar (0 or 1):  ");
   n_coins = getnumber();
   u_dollar = n_coins * DOLLAR;
   printf("\nQuarters:  ");
   n_coins = getnumber();

   u_quarter = n_coins * QUARTER;
   coins.quarters = coins.quarters + u_quarter;
   printf("\nDimes:  ");
   n_coins = getnumber();
   u_dime = n_coins * DIME ;
   coins.dimes = coins.dimes + u_dime;
   printf("\nNickels: ");
   n_coins = getnumber();
   u_nickel = n_coins * NICKEL;
   coins.nickels = coins.nickels + u_nickel;

   *u_money = u_nickel + u_dime + u_quarter + u_dollar;
   printf("\nYou inserted $%.02f", *u_money);

   return coins;
}
/******************************************************************************/


/*******************************************************************************
	getnumber
--------------------------------------------------------------------------------
Purpose: To scan a floating point number
Pre: None
Post: return the number
*******************************************************************************/
float getnumber (void)
{
   float number;
	scanf("%f", &number);
   return number;
}
/******************************************************************************/



/*******************************************************************************
	printlist
--------------------------------------------------------------------------------
Purpose: To print the list of items that can be purchased and display an OUT
			message if their are none left
Pre: The struct candy contains information
Post: The list is printed and choice is returned
*******************************************************************************/
int printlist(item_t candy[])
{

   int i, choice;
   int count = 1;
	i = 0;

   clrscr();
   printf("Please type 1 to make a purchase or 0 to stop:\t");
   while(i < ITEMS)
   {

      if (candy[i].amount == 0)
      	printf("\n%d. %-24s%s\n", count, candy[i].name, "OUT");
      else if(i == 9)
      	printf("\n%d. %-24s%.02f\n", count, candy[i].name, candy[i].price);
      else
			printf("\n%d. %-25s%.02f\n", count, candy[i].name, candy[i].price);

      i++;
      count++;
   }


	scanf("%d", &choice);

		return choice;
}
/******************************************************************************/



/*******************************************************************************
	scanfile
--------------------------------------------------------------------------------
Purpose: To read the data in from the vending.dat file
Pre: vending.dat exists
Post: File is read into structs
*******************************************************************************/
void scanfile(item_t candy[])
{


   FILE *infile;
   char filename[MAX];
   int i = 0;
   char ch;

   printf("PLease enter the filename:\t\n");
   scanf("%s", filename);
   infile = fopen(filename, "r");


	/* read price and name from file, store in array */
	while ((i < MAX) &&
			(fscanf(infile, "%f", &candy[i].price) == 1))
	{
		ch = getc(infile);	/* read past blank after price */
		if (fgets(candy[i].name, MAX, infile)
				== NULL)
		{
			printf("ERROR: no name for last data item\n");
			exit(1);
		}
		else
		{
			if (candy[i].name[strlen(candy[i].name) - 1] == '\n')
				candy[i].name[strlen(candy[i].name) - 1] = '\0';
			fflush(infile);
			i++;
		}
	}

	fclose(infile);
}
/******************************************************************************/



/*******************************************************************************
	getcandy
--------------------------------------------------------------------------------
Purpose: To get the item amount of each type of candy
Pre: None
Post: The amount of candy is updated
*******************************************************************************/
void getcandy (int item[], item_t candy[] )
{
   int i = 0;

	printf("Please enter the number of items you wish to start with\n");
   while(i < ITEMS)
   {
   	scanf("%d", &item[i]);
      i++;
   }

   for (i = 0;i < ITEMS;i++)
   	candy[i].amount = item[i];

   for(i = 0; i < ITEMS; i++)
   	printf("%-25s%.02f%20d\n", candy[i].name, candy[i].price, candy[i].amount);


}
/******************************************************************************/



/*******************************************************************************
	money
--------------------------------------------------------------------------------
Purpose: To tell the machine how much money to start with
Pre: None
Post: Amount of money in machine is updated
*******************************************************************************/
coins_t money (void)
{
	coins_t coins;

   int nickels, dimes, quarters;
   fflush(stdin);
   printf("\nHow many nickels, dimes, and quarters should I have\n");
   scanf("%d%d%d", &nickels, &dimes, &quarters);
   coins.quarters = quarters;
   coins.dimes = dimes;
   coins.nickels = nickels;

   return coins;
}
/******************************************************************************/




/*******************************************************************************
	change
--------------------------------------------------------------------------------
Purpose: To convert the amount of money into the actual monetary (DOLLAR) amount
Pre: That coins contains the amount of money
Post: The struct is updated
*******************************************************************************/
coins_t change (coins_t coins)
{


	coins.quarters = coins.quarters * QUARTER;
   coins.dimes = coins.dimes * DIME;
   coins.nickels = coins.nickels * NICKEL;

   return coins;

}
/******************************************************************************/
