#include <iostream>

using namespace std;


int main()
{
   int temp, diff, answer=1, counter, digit, final=0;
   int stopdigit = 1;

   for( int i=1; i<1e6; i++ )
   {
      if( stopdigit < i )
         stopdigit=stopdigit*10;

      digit = 1;
      counter = 1;
      temp = i;

      while( temp > 9 )
      {
         temp = temp/10;
         counter++;
      }

      if( final < stopdigit && (counter + final) >= stopdigit )
      {
         diff = counter + final - stopdigit;
         temp = i;

         for( int j=0; j<=diff; j++ )
         {
            digit = temp % 10;
            temp = temp/10;
         }

      }

      final += counter;
      answer = answer*digit;
   }

   cout << "Answer" << endl << answer << endl;


   return 0;
}
