#ifndef _DATE_H_
#define _DATE_H_

#include <ctime>

struct Date
{
    int day;
    int month;
    int year;
    Date()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
    }
    Date(int day, int month, int year) : day{day}, month{month}, year{year} {}
    bool operator==(const Date &other)
    {
        return this->day == other.day && this->month == other.month && this->year == other.year;
    }
};

#endif