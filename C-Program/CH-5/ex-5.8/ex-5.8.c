#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day with error checking */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	/* validate month and day */
	if (month < 1 || month > 12)
		return -1;   /* invalid month */

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	if (day < 1 || day > daytab[leap][month])
		return -1;   /* invalid day */

	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;  /* valid day of year */
}

/* month_day: set month and day from day of year with error checking */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	/* valid range check for yearday */
	if (yearday < 1 || yearday > (leap ? 366 : 365))
		return -1;   /* invalid yearday */

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
	return 0;   /* success */
}

/* test program */
int main(void)
{
	int year = 2024;
	int month = 2, day = 29;
	int yearday = day_of_year(year, month, day);

	if (yearday == -1)
		printf("Invalid date!\n");
	else
		printf("%d-%02d-%02d is day number %d of the year\n", year, month, day, yearday);

	int m, d;
	if (month_day(year, 366, &m, &d) == 0)
		printf("Day 366 of %d is %d/%d\n", year, m, d);
	else
		printf("Invalid yearday!\n");

	return 0;
}

