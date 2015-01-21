/*
 *  G:\leslie\01github\ofxUtils\ofxdate.cpp
 *
 *  Created by Leslie Yang on 2015-01-21
 *
 *
 *  Copyright 2015 https://github.com/LeslieFire All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *  OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  ************************************************************************************ */ 
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
