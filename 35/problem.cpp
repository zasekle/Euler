#include <iostream>
#include <vector>
#include <cmath>
#include "pseive.h"

using namespace std;

const int limit = 1e6;

pseive seive( limit );

bool isprime( const int );

int main()
{
   int numholder, circular, power;
   bool works;
   vector<int> primes;

   for( int i=2; i<limit; i++ )
   {
      if( isprime( i ) )
      {
         numholder=i;
         power = -1;
         works = true;

         while( numholder > 0 )
         {
            power++;
            numholder = numholder/10;
         }

         numholder=i;

         circular = numholder % 10;
         numholder = numholder/10;

         numholder = numholder + (circular * pow( 10, power ));

         if( !isprime( numholder ) )
            works = false;

         while( numholder != i )
         {

            circular = numholder % 10;
            numholder = numholder/10;

            numholder = numholder + (circular * pow( 10, power ));

            if( !isprime( numholder ) )
               works = false;
         }

         if( works == true )
            primes.push_back( i );

      }
   }

   cout << primes.size() << endl;
   return 0;
}

bool isprime( const int x )
{
   return !seive.getbit( x );
}
