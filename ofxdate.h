#ifndef OFXDATE_H
#define OFXDATE_H
#include <iostream>
using namespace std;


class date;
class ofxDate{
    public:
    static int getTimeDiff(int y1, int m1, int d1,
                        int y2, int m2, int d2);
};
class date
{
    public:
        date(int y=1, int m=1, int d=1):year(y),month(m),day(d){}
        virtual ~date();

        int year;
        int month;
        int day;

        bool isleapyear ();
        int getyeardays ();
        int getmonthdays ();
        int datetonum();


    protected:
    private:
};

#endif // OFXDATE_H
