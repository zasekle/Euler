#include <iostream>

using namespace std;

int main()
{
   //1 Jan 1900 was mon

   //31 jan, march, may, july, aug, oct, dec

   //30 monthdays april, june, spet, nov

   //28 monthdays feb (29 on all multiple of 4 years)

   //monmonthdays on first of month from Jan-1 1901 -> Dec-31 2000

   //days of the month 1-31
   int monthdays;

   //days of the week 1 is mon 7 is sun
   int weekdays=1;

   int test=0;
   int counter=0;

   //outter loop represents years
   //0 is 1900 100 is 2000
   for( int i=0; i<101; i++ )
   {
      //inner loop represents months
      //1 is january 12 is december
      for( int j=1; j<13; j++ )
      {
         //jan
         if( j==1 )
            monthdays = 32;
         //feb
         else if( j==2 && i % 4 == 0 )
            monthdays = 30;
         else if( j==2 )
            monthdays = 29;
         //march
         else if( j==3 )
            monthdays = 32;
         //april
         else if( j==4 )
            monthdays = 31;
         //may
         else if( j==5 )
            monthdays = 32;
         //june
         else if( j==6 )
            monthdays = 31;
         //july
         else if( j==7 )
            monthdays = 32;
         //aug
         else if( j==8 )
            monthdays = 32;
         //sept
         else if( j==9 )
            monthdays = 31;
         //oct
         else if( j==10 )
            monthdays = 32;
         //nov
         else if( j==11 )
            monthdays = 31;
         //dec
         else if( j==12 )
            monthdays = 32;

         //days of month
         for( int k=1; k<monthdays; k++ )
         {
            if( i > 0 && k == 1 && weekdays == 7 )
               counter++;

            //reset week day to mon every time it passes sun
            if( weekdays == 7 )
               weekdays = 0;

            test++;
            weekdays++;
         }

      }
      //cout << endl << i+1900 << ':' << test;
      //test=0;
   }

   cout << "Mondays on first of the month 1901-2000" << endl << counter << endl;

   return 0;
}
