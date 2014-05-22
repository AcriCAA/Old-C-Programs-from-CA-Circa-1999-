/* Programmer: Corey Acri
	Date: 9/20/99
   Version: 1.0
   Purpose: To print out a calendar and any special dates in the appropriate
   			spots
   Input: The Year and the month from the user
   Output: A calendar for that year and month. It will also print "Easter",
   			"Christmas","Labor Day","New Year's","Thanksgivin.","Independ."
            and "Labor Day" on the appropriate dates.

   Known Bugs: For certain months the calendar will not finish off the blank
   				spaces at the end of the calendar. I could not for the life
               of me figure out why it wouldn't print the remaining
               blanks in some cases and would print them in others.
               I was also unable to figure out how to print memorial day.  All
               other special dates have been inserted.


   Other Comments: Although it was suggested to use an array to place the dates
						 in the calendar, I felt it was not neccesary. I am familar
                   with the use of Arrays but for this program I felt it would
                   be more of a hassle.
*/

#include <stdio.h>

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12


void welcome (void);             /* opening prints */
int getyear (void);              /* Gets the year from the user */
int getmonth (void);             /* Gets the month from the user */
void print_month_year (int, int);/* Prints the name if the month and the year */
void printBars(void); 				/* Prints a dividing row */
void printDividers(void);			/* Prints dividing columns */
int weekDate(int, int, int);     /* Calculates the weekdate for a specific date */
int monthLength(int, int);			/* Calculates the length of a month for a specific year */
void printMonth (int);				/* Prints the name of a given month */
int easterDate(int);             /* Calculates the Easter Date */
void printdays(void);            /* Prints the headers for the days of the week */
void printdate(int,int,int,int); /* Prints the body of the calendar */
int chkspecial(int, int, int);   /* Checks if the Date is a special date */
void printspecial(int);          /* Prints the name of the special date */
void wait (void);                /* Waits for final user input to quit program */

main()
{
	int year, month, day, weekdate,count;
   int monthdays,   /* number of days int the month */
       specialday;

   welcome();
	year = getyear();
   month = getmonth();
   print_month_year(month, year);
   printBars();
   printdays();
   printBars();
   weekdate = weekDate(year, month,1);
   monthdays = monthLength(year,month);
	specialday = chkspecial(year,month,day);
	printdate(weekdate,monthdays,specialday,month);
	wait();

 	return 0;
}
/***********************************************
	welcome
------------------------------------------------
	Purpose: To greet the user to the program
   Pre: None
   Post: Prints the Welcome message
***********************************************/
void welcome (void)
{

	printf("Hello user and welcome to Corey Acri's Calendar Program\n");
   printf("Please follow the directions carefully\n\n");

}
/******************************************************************************/



/**********************************************
	wait
-----------------------------------------------
	Purpose: To end the program if it is in DOS mode
   Pre: Any input from the user
   Post: quits the program
***********************************************/

void wait (void)
{
   int wait;
 	scanf("%d", &wait);
}
/******************************************************************************/


/*********************************************
	printdays
---------------------------------------------
	Purpose: To print the Days of the Week on the top of the Calendar.
   Pre: None
   Post: Prints the days of the week.
*********************************************/
void printdays (void)
{

	printf("%s%s",
"|Sunday    |Monday    |Tuesday   |Wednesday |Thursday  |Friday    ",
				"|Saturday  |\n");


}
/******************************************************************************/




/*********************************************
	getyear
----------------------------------------------
	Purpose: To get the year input from the user.
   Pre: Integer input for the year.
   Post: None
**********************************************/
int getyear (void)
{
	int year;

	printf("Please input the year\n");
	printf("and input a year after 1600 to end:\t");
	scanf("%d", &year);
	return year;

}
/******************************************************************************/


/*********************************************
	getmonth
----------------------------------------------
	Purpose: To get the month input from the user.
   Pre: Integer input for the month.
   Post: None
**********************************************/
int getmonth (void)
{

	int month;

	printf("\nPlease input the month:\t");
	scanf("%d", &month);
	return month;
}
/******************************************************************************/



/*********************************************
	print_month_year
----------------------------------------------
	Purpose: To print the Name of the month and the year.
   Pre: None.
   Post: Prints the month and the year.
**********************************************/
void print_month_year(int month, int year)
{

	if(month == JANUARY)
	  printf("\nJanuary ");
	else if (month == FEBRUARY)
	  printf("\nFebruary ");
	else if (month == MARCH)
	  printf("\nMarch ");
	else if (month == APRIL)
	  printf("\nApril ");
	else if (month == MAY)
	  printf("\nMay ");
	else if (month == JUNE)
	  printf("\nJune ");
	else if (month == JULY)
	  printf("\nJuly ");
	else if (month == AUGUST)
	  printf("\nAugust ");
	else if (month == SEPTEMBER)
	  printf("\nSeptember ");
	else if (month == OCTOBER)
	  printf("\nOctober ");
	else if (month == NOVEMBER)
	  printf("\nNovember ");
	else				/* December */
	  printf("\nDecember ");

	printf("%d\n", year);
}
/******************************************************************************/

/**********************************************************
	printBars
-----------------------------------------------------------
	Purpose:	Prints a diving row
	Pre:		None
	Post:		Prints a fixed length line of 78 bars (=)
**********************************************************/
void printBars(void)
{
	int i;
	for(i = 1; i <= 78; i++)
		printf("=");
	printf("\n");
}
/******************************************************************************/


/**********************************************************
	printDividers
-----------------------------------------------------------
	Purpose:	Prints dividing columns
	Pre:		None
	Post:    Prints a fixed length line of 78 special characters
**********************************************************/
void printDividers(void)
{
	int i, j;

	for(i = 1; i <= 7; i++)			/* Number of days */
	{
		printf("|");              	/* Print divider and ten spaces */
		for(j = 1; j <= 10; j++)
			printf(" ");
	}
	printf("|");						/* Complete the line */
	printf("\n");
}
/******************************************************************************/

/**********************************************************
	weekDate
-----------------------------------------------------------
	Purpose:	Calculates the weekdate for a specific date
	Pre:		Integer input for year, month, and day (after 1600)
	Post:		Outputs an integer representing a weekday
				0 = Sunday, 1 = Monday, ..., 6 = Saturday
**********************************************************/
int weekDate(int iYear, int iMonth, int iDay)
{
	int month, year,leap, century,special, weekday;


	if(iMonth == 1) {
		iYear--;
		month = 11;
	}

	else if (iMonth == 2) {
		iYear--;
		month = 12;
	}
	else{
		month = (iMonth + 10) % 12;
	}

	year = iYear - 1600;
	leap = year/4;
	century = year/100;
	special = year/400;
	weekday = (2 + iDay + year + leap -century + special +
					(int)(2.6 * month - 2.2)) % 7;

	return weekday;

}
/******************************************************************************/



/**********************************************************
	monthLength
-----------------------------------------------------------
	Purpose:	Calculates the length of a month for a specific year
	Pre:		Integer input for year and month
	Post:		Outputs an integer representing the length of a month
**********************************************************/
int monthLength(int iYear, int iMonth)
{
	if(iMonth == JANUARY)
	  return 31;
	else if ((iMonth == FEBRUARY) && (iYear % 400 == 0))
	  return 29;
	else if ((iMonth == FEBRUARY) && (iYear % 100 == 0))
	  return 28;
	else if ((iMonth == FEBRUARY) && (iYear % 4 == 0))
	  return 29;
	else if (iMonth == FEBRUARY)
	  return 28;
	else if (iMonth == MARCH)
	  return 31;
	else if (iMonth == APRIL)
	  return 30;
	else if (iMonth == MAY)
	  return 31;
	else if (iMonth == JUNE)
	  return 30;
	else if (iMonth == JULY)
	  return 31;
	else if (iMonth == AUGUST)
	  return 31;
	else if (iMonth == SEPTEMBER)
	  return 30;
	else if (iMonth == OCTOBER)
	  return 31;
	else if (iMonth == NOVEMBER)
	  return 30;
	else				/* December */
	  return 31;
}
/******************************************************************************/



/**********************************************************
	printMonth
-----------------------------------------------------------
	Purpose:	Prints the name of a given month
	Pre:		Integer input for month
	Post:		None
**********************************************************/
void printMonth(int iMonth)
{
	if (iMonth == 1)
	  printf("January");
	else if (iMonth == 2)
	  printf("February");
	else if (iMonth == 3)
	  printf("March");
	else if (iMonth == 4)
	  printf("April");
	else if (iMonth == 5)
	  printf("May");
	else if (iMonth == 6)
	  printf("June");
	else if (iMonth == 7)
	  printf("July");
	else if (iMonth == 8)
	  printf("August");
	else if (iMonth == 9)
	  printf("September");
	else if (iMonth == 10)
	  printf("October");
	else if (iMonth == 11)
	  printf("November");
	else
	  printf("December");
}
/******************************************************************************/


/**********************************************************
	easterDate
-----------------------------------------------------------
	Purpose:	Calculates the date of Easter
	Pre:		Integer input for year
	Post:		Returns an integer representing the date of Easter
**********************************************************/
int easterDate(int iYear)
{

	int century, leap, week, month, day;
	int easter;

	century = iYear % 19;
	leap = iYear % 4;
	week = iYear % 7;
	month = (19 * century + 24) % 30;
	day = (2 * leap + 4 * week + 6 * month + 5) % 7;

	easter = 22 + month + day;

	if (easter > 31 )
		return easter;
	else
		return easter;

}
/******************************************************************************/



/*********************************************
	printdate
----------------------------------------------
	Purpose: To print the body of the calendar including special dates (i.e."Easter).
   Pre: The weekdate, the days of the month any special days and the month.
   Post: Prints the body of the calendar.
**********************************************/
void printdate (int weekdate, int imonthdays, int specialday,int month)
{
	int count, day;

	for(count=0;count!=weekdate; count++)
			printf("|          ");

	for(day = 1; day <= imonthdays; day++){
			if(count!= 0 && count%6 == 0){
			if(day < 10){
			if (day == specialday  && specialday!=0){
					printspecial(month);
					printf("|\n");
			  }
         else
         printf("|%d         |\n",day);

			printDividers();
         printDividers();
         printBars();
         day++;
			}
			else{
			  if (day == specialday  && specialday!=0){
					printspecial(month);
					printf("|\n");
			  }
			  else
				printf("|%d        |\n",day);

				printDividers();
				printDividers();
				printBars();
				day++;
			}

			}
			if(day > imonthdays)
				;
			else{
			if (day == specialday  && specialday!=0)
			  printspecial(month);
			else{
			printf("|%d",day);
			if(day < 10)
				printf("         ");
			else
				printf("        ");
			}
			}
		count++;

		}
		if(count < 31)
			while(count < 31){
				printf("|          ");
				count++;
				}
		printf("|\n");
		printDividers();
		printDividers();
		printBars();
}
/******************************************************************************/


/*********************************************
	checkspecial
----------------------------------------------
	Purpose: Checks to see if the current day is a special date.
   Pre: The current date.
   Post: returns the special day or 0 if it isn't a special day.
**********************************************/
int chkspecial(int year,int imonth, int day)
{
	 int easter, month, weekdate;

	 month = 3;

	if (imonth == 4 || imonth == 3) {
			easter = easterDate(year);
		if (easter > 31){
			month = 4;
			easter = easter - 31;
		}
	}
	if (month == imonth)
		return easter;
	else if(imonth == 12)
		return 25;
	else if (imonth == 1)
		return 1;
	else if (imonth == 7)
		return 4;

	else if (imonth == 9){
		weekdate = weekDate(year,imonth,1);
		if (weekdate == 1)
			return 1;
		else if (weekdate < 1)
			return weekdate+=2;
		else if (weekdate == 2)
			return weekdate+=5;
		else if (weekdate == 3)
			return weekdate+=3;
		else if (weekdate == 4)
			return weekdate+=1;
		else if (weekdate == 5)
			return weekdate--;
		else if (weekdate == 6)
			return weekdate -=4;
	}

	else if (imonth == 11){
		weekdate = weekDate (year,imonth,1);
		if(weekdate == 4)
			return weekdate*=5.5;
		else if (weekdate == 0)
			return weekdate = ((weekdate + 7) * 3) + 5;
		else if (weekdate == 1)
			return weekdate = ((weekdate + 7) * 3) + 1;
		else if (weekdate == 2)
			return weekdate = (weekdate + 6) * 3;
		else if (weekdate == 3)
			return weekdate = ((weekdate + 5) * 3) - 1;
		else if (weekdate == 5)
			return weekdate = ((weekdate + 3) * 3) - 3;
		else if (weekdate == 6)
			return weekdate = ((weekdate + 2) * 3) - 4;
	}
	else
		return 0;
}
/******************************************************************************/


/*********************************************
	printspecial
----------------------------------------------
	Purpose: To print the Name of the Special date in place of the number.
   Pre: The month the special day falls on
   Post: Prints the special day
**********************************************/
void printspecial(iMonth)
{

if (iMonth == 1)
	  printf("|New Year's");
	else if (iMonth == 3)
	  printf("|Easter    ");
	else if (iMonth == 4)
	  printf("|Easter    ");
   else if (iMonth == 7)
	  printf("|Independ. ");
	else if (iMonth == 9)
	  printf("|Labor Day ");
	else if (iMonth == 11)
	  printf("|Thanksgiv.");
	else
	  printf("|Christmas ");
}
/******************************************************************************/
