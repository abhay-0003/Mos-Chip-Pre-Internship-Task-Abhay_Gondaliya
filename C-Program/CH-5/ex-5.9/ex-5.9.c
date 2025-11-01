#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day using pointers */
int day_of_year(int year, int month, int day)
{
	int leap;
	char *p;

	/* validate month */
	if (month < 1 || month > 12)
		return -1;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	/* point to first day in correct row */
	p = daytab[leap];

	/* validate day */
	if (day < 1 || day > *(p + month))
		return -1;

	/* accumulate days */
	while (--month > 0)
		day += *(++p);

	return day;
}

/* month_day: set month and day from day of year using pointers */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	char *p;

	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	/* validate yearday */
	if (yearday < 1 || yearday > (leap ? 366 : 365))
		return -1;

	p = daytab[leap] + 1;  /* point to first month (Jan = index 1) */

	while (yearday > *p && (p - daytab[leap]) < 12)
		yearday -= *p++;

	*pmonth = (int)(p - daytab[leap]);
	*pday = yearday;
	return 0;
}

/* test driver */
int main(void)
{
	int year = 2024;
	int month = 3, day = 1;
	int yearday, m, d;

	yearday = day_of_year(year, month, day);
	if (yearday == -1)
		printf("Invalid date!\n");
	else
		printf("%d-%02d-%02d is day number %d of the year\n", year, month, day, yearday);

	if (month_day(year, yearday, &m, &d) == 0)
		printf("Day %d of %d is %d/%d\n", yearday, year, m, d);
	else
	printf("Invalid yearday!\n");

	return 0;
}

