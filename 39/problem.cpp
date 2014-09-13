#include <iostream>
#include <cmath>

//brute force

using namespace std;

int main()
{
   int subtrac, counter;
   float c;
   int final[2]={0,0};

   //sqrt(1000-1^2-1^2)=31.5
   //this loop is the perimiter
   for( int i=1; i<1001; i++ )
   {
      counter = 0;
      //this loop is a
      for( int j=1; j<i; j++ )
      {
         //this loop is b
         for( int k=j; k<i; k++ )
         {
            //a^2 + b^2
            subtrac = pow( j, 2 ) + pow( k, 2 );

            if( subtrac > 0 )
            {
               c = sqrt( subtrac );

               if( ceil( c ) == floor( c ) && j+k+c==i )
                  counter++;

            }
         }
      }

      if( final[0] < counter )
      {
         final[0] = counter;
         final[1] = i;
      }
   }

   cout << final[1] << endl;

   return 0;
}
