#include<iostream>
using namespace std;



class MyException : public exception {

	const char * what() const throw ()
	{
		return "C++ Exception";
	}
};



class Date {
private:
	int year; // 1753-9999
	int month; // 1-12
	int day; // 1-31
	char * date; // Monday, 9 Mar 2017
	const static char STR_MONTHS[12][4];
	const static char STR_DAYS[12][10];
	const static int DAYS_IN_MONTHS[12];
	const static int YEAR_MIN = 1753;
	const static int YEAR_MAX = 9999;
public:
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);
	int getDayOfWeek(int y, int m, int d);
	Date(const Date&dateObj); //Copy Constructor and You must copy (dateObj.date to char * date).
	Date(int y, int m, int d);
	Date(); //Default Constructor set Date to Default value: Sunday, 1 Jan 2017
	void setDate(int y, int m, int d); //Initialize the char * date with exact date.
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	void setYear(int y);
	void setMonth(int m);
	void setDay(int d);
	void print() const;
	void nextDay(); //updates the value of Day.
	void previousDay();
	void nextMonth();
	void previousMonth();
	void nextYear();
	void previousYear();
};

// Initialize static non-integer variable (must be done outside the class declaration)
const char Date::STR_MONTHS[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const int Date::DAYS_IN_MONTHS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const char Date::STR_DAYS[12][10] = { "Sunday", "Monday", "Tuesday", "Wednesday",
"Thursday", "Friday", "Saturday" };

// A static function that returns the day of the week (0:Sun, 6:Sat) for the given date
// Wiki "Determination of the day of the week" for the algorithm


int Date::getDayOfWeek(int y, int m, int d)
{
	int centuryTable[] = { 4, 2, 0, 6, 4, 2, 0, 6 }; // 17xx, 18xx, ...
	int MonthTable[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	int MonthLeapYearTable[] = { 6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
	int century = y / 100;
	int twoDigitYear = y % 100;
	int centuryTableIndex = (century - 17) % 8;
	// Date before 17xx are not valid, but needed to prevent negative index
	if (centuryTableIndex< 0)
	{
		centuryTableIndex += 8;
	}
	int sum = centuryTable[centuryTableIndex] + twoDigitYear + twoDigitYear / 4;
	if (isLeapYear(y))
	{
		sum += MonthLeapYearTable[m - 1];
	}
	else
	{
		sum += MonthTable[m - 1];
	}
	sum += d;
	return sum % 7;
}

// Print this instance in the format &quot;xxxday, d mmm yyyy&quot;.
void Date::print() const
{
	cout << STR_DAYS[getDayOfWeek(year, month, day)] << ", "<< day << " " << STR_MONTHS[month - 1] << " " << year << endl;
	cout << "Char * Output is :" << date << endl;                          //This must be printed.
	
}


int main()
{

	Date d1(2012, 1, 1);
	d1.print(); // Sunday, 1 Jan 2012
	d1.nextDay();
	d1.print(); // Monday, 2 Jan 2012
	d1.setDate(2012, 1, 31);
	d1.print(); // Tuesday, 31 Jan 2012
	d1.nextDay();
	d1.print(); // Wednesday, 1 Feb 2012
	d1.setDate(2012, 2, 28);
	d1.print(); // Tuesday, 28 Feb 2012
	d1.nextDay();
	d1.print(); // Wednesday, 29 Feb 2012
	d1.setDate(2012, 12, 31);
	d1.print(); // Monday, 31 Dec 2012
	d1.nextDay();
	d1.print(); // Tuesday, 1 Jan 2013
	try{
		Date d3(2011, 2, 29); //Error should be printed &quot;Invalid Day&quot; and date should be initialized with default date given below.
		d3.print(); //Sunday, 1 Jan 2017 (Default Date)
	}
	catch (exception){}
	try{
		Date d4(9999, 12, 30);
		d4.nextDay();
		d4.print(); // Friday, 31 Dec 9999
		d4.nextDay(); //Error should be printed &quot;Next day is out of range.&quot; and date goes to default date discussed above.
		d4.print();
	}
	catch (exception){}
	Date d5(d4);
	d5.print(); //Sunday, 1 Jan 2017 (Default Date)
	return 0;
}