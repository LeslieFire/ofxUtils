#include "ofxdate.h"

date::~date()
{
    //dtor
}

bool date::isleapyear()
{
    if(year%4==0 && year%100 !=0 || year%400==0) return true;
    else return false;
}

int date::getyeardays()
{
    if (isleapyear()) return 366;
    else return 365;
}

int date::getmonthdays()
{
    int n;
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
       n=31;
          break;
    case 4:
    case 6:
    case 9:
    case 11:
         n=30;
         break;
       case 2:
       if(isleapyear()) n=29;
       else n=28;
    }
    return n;
}

int date::datetonum()
{
    int n = 0;
    int tempyear = year;
    int tempmonth = month;
    for (month = 1;month < tempmonth; month++)
        n += getmonthdays();
    for (year = 1970; year < tempyear; year++)
        n += getyeardays();
    n += day;

    return n;
}

int ofxDate::getTimeDiff(int y1, int m1, int day1,
                        int y2, int m2, int day2){
    date d1(y1, m1, day1);
    date d2(y2, m2, day2);

    int ret = d2.datetonum() - d1.datetonum();
    if (ret < 0)
        ret = -1*ret;
    return ret;

}
