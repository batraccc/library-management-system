#ifndef _DATE_H_
#define _DATE_H_

#include <ctime>
#include <iostream>
#include <fstream>

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

    void display(std::ostream &os) const
    {
        if (day < 10)
            os << "0";
        os << day << "/";

        if (month < 10)
            os << "0";
        os << month << "/" << year;
    }

    bool operator==(const Date &other) const
    {
        return this->day == other.day && this->month == other.month && this->year == other.year;
    }

    static bool isLeapYear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    long long toTotalDays() const
    {
        long long totalDays = day;
        for (int m = 1; m < month; ++m)
        {
            if (m == 2)
            {
                totalDays += isLeapYear(year) ? 29 : 28;
            }
            else if (m == 4 || m == 6 || m == 9 || m == 11)
            {
                totalDays += 30;
            }
            else
            {
                totalDays += 31;
            }
        }

        for (int y = 0; y < year; ++y)
        {
            totalDays += isLeapYear(y) ? 366 : 365;
        }

        return totalDays;
    }

    long long operator-(const Date &other) const
    {
        return this->toTotalDays() - other.toTotalDays();
    }
};

#endif