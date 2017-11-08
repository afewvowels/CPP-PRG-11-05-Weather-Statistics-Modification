//
//  main.cpp
//  CPP-PRG-11-05-Weather-Statistics-Modification
//
//  Created by Keith Smith on 11/7/17.
//  Copyright © 2017 Keith Smith. All rights reserved.
//
//  Modify the program that you wrote for Programming Challenge 4 (weather statistics)
//  so it defines an enumerated data type with enumerators for the months (JANUARY,
//  FEBRUARY, so on). The program should use the enumerated type to step through the
//  elements of the array.

#include <iostream>
#include <iomanip>

using namespace std;

struct StructMonthWeather
{
    double dblRainfallTotal;
    double dblTempHigh;
    double dblTempLow;
    double dblTempAverage;
};

struct StructWeatherResults
{
    double dblAverageMonthlyRainfall;
    double dblTotalRainfallAnnual;
    double dblTempHighest;
    string strMonthHigh;
    double dblTempLowest;
    string strMonthLow;
    double dblAverageMonthlyTemp;
};

enum EnmMonth { JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };

StructMonthWeather *getMonthsData(int);
string *convertEnumToString(int);
StructWeatherResults *calculateResults(StructMonthWeather *, int);
void displayResults(StructWeatherResults *);

int main()
{
    int INT_ARR_SIZE = 12;
    
    StructMonthWeather *stcWeather = nullptr;
    stcWeather = new StructMonthWeather[INT_ARR_SIZE];
    
    StructWeatherResults *stcWeatherResults = nullptr;
    stcWeatherResults = new StructWeatherResults;
    
    for (int month = JANUARY ; month <= DECEMBER ; month++)
    {
        stcWeather[month] = *getMonthsData(month);
    }
    
    stcWeatherResults = calculateResults(stcWeather, INT_ARR_SIZE);
    
    displayResults(stcWeatherResults);
    
    return 0;
}

StructMonthWeather *getMonthsData(int intMonth)
{
    StructMonthWeather *stcWeatherMonth = nullptr;
    stcWeatherMonth = new StructMonthWeather;
    
//    intMonth++;
    
    cout << "Please enter the total rainfall for month " << *convertEnumToString(intMonth) << ": ";
    cin >> stcWeatherMonth->dblRainfallTotal;
    while(!cin || stcWeatherMonth->dblRainfallTotal < 0 || stcWeatherMonth->dblRainfallTotal > 1000)
    {
        cout << "Please enter a number between 0 and 1,000: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblRainfallTotal;
    }
    
    cout << "Please enter the highest temperature for month " << *convertEnumToString(intMonth) << ": ";
    cin >> stcWeatherMonth->dblTempHigh;
    while(!cin || stcWeatherMonth->dblTempHigh < -100 || stcWeatherMonth->dblTempHigh > 140)
    {
        cout << "Please enter a temperature between -100F and 140F: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblTempHigh;
    }
    
    cout << "Please enter the lowest temperature for month " << *convertEnumToString(intMonth) << ": ";
    cin >> stcWeatherMonth->dblTempLow;
    while(!cin || stcWeatherMonth->dblTempLow < -100 || stcWeatherMonth->dblTempLow > 140)
    {
        cout << "Please enter a temperature between -100F and 140F: ";
        cin.clear();
        cin.ignore();
        cin >> stcWeatherMonth->dblTempLow;
    }
    
    stcWeatherMonth->dblTempAverage = (stcWeatherMonth->dblTempHigh + stcWeatherMonth->dblTempLow) / 2;
    
    return stcWeatherMonth;
}

string *convertEnumToString(int intMonth)
{
    string *strMonth = nullptr;
    strMonth = new string;
    
    switch(intMonth)
    {
        case JANUARY:
            *strMonth = "January";
            break;
        case FEBRUARY:
            *strMonth = "February";
            break;
        case MARCH:
            *strMonth = "March";
            break;
        case APRIL:
            *strMonth = "April";
            break;
        case MAY:
            *strMonth = "May";
            break;
        case JUNE:
            *strMonth = "June";
            break;
        case JULY:
            *strMonth = "July";
            break;
        case AUGUST:
            *strMonth = "August";
            break;
        case SEPTEMBER:
            *strMonth = "September";
            break;
        case OCTOBER:
            *strMonth = "October";
            break;
        case NOVEMBER:
            *strMonth = "November";
            break;
        case DECEMBER:
            *strMonth = "December";
            break;
        default:
            *strMonth = "ERROR";
            break;
    }
    
    return strMonth;
}

StructWeatherResults *calculateResults(StructMonthWeather *stcArr, const int INT_MONTHS)
{
    StructWeatherResults *stcResults = nullptr;
    stcResults = new StructWeatherResults;
    
    EnmMonth *enmMonths = nullptr;
    enmMonths = new EnmMonth;
    
    double *dblAverageRainfall = nullptr;
    dblAverageRainfall = new double;
    *dblAverageRainfall = 0;
    
    double *dblTotalRainfall = nullptr;
    dblTotalRainfall = new double;
    *dblTotalRainfall = 0;
    
    string *strHighestMonth = nullptr;
    strHighestMonth = new string;
    
    double *dblHighestTemp = nullptr;
    dblHighestTemp = new double;
    *dblHighestTemp = __DBL_MIN__;
    
    string *strLowestMonth = nullptr;
    strLowestMonth = new string;
    
    double *dblLowestTemp = nullptr;
    dblLowestTemp = new double;
    *dblLowestTemp = __DBL_MAX__;
    
    double *dblAverageTemp = nullptr;
    dblAverageTemp = new double;
    *dblAverageTemp = 0;
    
    for (int month = JANUARY ; month <= DECEMBER ; month++)
    {
        *dblTotalRainfall += stcArr[month].dblRainfallTotal;
    }
    stcResults->dblTotalRainfallAnnual = *dblTotalRainfall;
    
    *dblAverageRainfall = *dblTotalRainfall / INT_MONTHS;
    stcResults->dblAverageMonthlyRainfall = *dblAverageRainfall;
    
    for (int month = JANUARY ; month <= DECEMBER ; month++)
    {
        *dblAverageTemp += stcArr[month].dblTempAverage;
        
        if (stcArr[month].dblTempHigh > *dblHighestTemp)
        {
            *dblHighestTemp = stcArr[month].dblTempHigh;
            *strHighestMonth = *convertEnumToString(month);
        }
        
        if (stcArr[month].dblTempLow < *dblLowestTemp)
        {
            *dblLowestTemp = stcArr[month].dblTempLow;
            *strLowestMonth = *convertEnumToString(month);
        }
    }
    
    stcResults->dblTempHighest = *dblHighestTemp;
    stcResults->strMonthHigh = *strHighestMonth;
    
    stcResults->dblTempLowest = *dblLowestTemp;
    stcResults->strMonthLow = *strLowestMonth;
    
    stcResults->dblAverageMonthlyTemp = *dblAverageTemp / INT_MONTHS;
    
    return stcResults;
}

void displayResults(StructWeatherResults *stcResults)
{
    cout << fixed << showpoint << setprecision(1) << endl;
    
    cout << "The average monthly rainfall was: " << stcResults->dblAverageMonthlyRainfall << endl;
    
    cout << "The total annual rainfall was: " << stcResults->dblTotalRainfallAnnual << endl;
    
    cout << "The highest temperature of the year was in ";
    cout << stcResults->strMonthHigh << ": " << stcResults->dblTempHighest << "F\n";
    
    cout << "The lowest temperature of the year was in ";
    cout << stcResults->strMonthLow << ": " << stcResults->dblTempLowest << "F\n";
    
    cout << "The average monthly temperature was: ";
    cout << stcResults->dblAverageMonthlyTemp << "F\n\n";
}

