#include <iostream>
#include "Bignums.h"

using namespace std;

//digits the number should contain
const int digits = 1000;

int main()
{
   Bignum x(1);
   Bignum y(1);
   int answer;

   bool flag = true;

   for( int i=1; flag == true; i++ )
   {
      if( i % 2 == 0 )
         x=x+y;
      else
         y=x+y;

      if( x.size() >= digits || y.size() >= digits )
      {
         answer = i+2;
         flag = false;
      }
   }


   cout << "Answer" << endl << answer << endl;
   return 0;
}
