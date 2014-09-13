#include <iostream>
#include <algorithm>
#include <cmath>
#include "pseive.h"

using namespace std;

pseive seive( 1e9 );

bool isprime( const int );

int main()
{
   int nums[9] = {1,2,3,4,5,6,7,8,9};
   int curnum, final=0;

   for( int j=2; j<10; j++ )
   {
      do {
         curnum = 0;
         for( int i=0; i<j; i++ )
            curnum += nums[j-1-i]*pow( 10, i );

         if( isprime( curnum ) )
            final = curnum;

      } while( next_permutation( nums, nums+j ) );
   }

   cout << "Answer" << endl << final << endl;

   return 0;
}

bool isprime( const int x )
{
   return !seive.getbit( x );
}
