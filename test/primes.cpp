#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "pseive.h"

using namespace std;

const int findnum = 999;

pseive seiv( findnum );

void primeFactors( int, vector<int>& );

void possDivisors( vector<int>&, vector<int>&, int, int=1 );

int main()
{

   vector<int> primef;
   vector<int> divisors;
   int divisor;
   bool sub;
   int size, in;

   for( int j=2; j<20; j++ )
   {
      primeFactors( j, primef );

      size = primef.size()/2;

      //possDivisors( divisors, primef, size );

      //sort( divisors.begin(), divisors.end() );

      in = 0;

      for( int i=0; i<primef.size(); i+=2 )
      {
         in = primef[i+1];
      }

      if( in > 1 )
      {
         cout << in << ' ';/* << j << ": ";

         for( int i=0; i<primef.size(); i+=2 )
         {
            cout << primef[i] << '^';
            cout << primef[i+1] << ' ';
            in += primef[i+1];
         }

         cout << in << endl;*/
      }

      primef.clear();
   }

   cout << endl;

   return 0;
}

void possDivisors( vector<int> &divis, vector<int> &primes, int loop, int div )
{
   if( loop != 0 )
   {
      int pos = loop*2-2;
      int temp = div;

      for( int i=primes[pos+1]; i>=0; i-- )
      {
         temp = temp * pow( primes[pos], ( primes[pos+1]-i ) );
         possDivisors( divis, primes, loop-1, temp );
         temp = div;
      }
   }
   else
   {
      if( div != 1 )
         divis.push_back( div );
   }


}

// A function to print all prime factors of a given number n
void primeFactors( int n, vector<int>&primes )
{
   // Print the number of 2s that divide n
   while (n%2 == 0)
   {
      if( primes.empty() )
      {
         primes.push_back( 2 );
         primes.push_back( 1 );
      }
      else
         ++primes[primes.size()-1];

      n = n/2;
   }


   // n must be odd at this point.  So we can skip one element (Note i = i +2)
   for (int i = 3; i <= sqrt(n); i = i+2)
   {
      // While i divides n, print i and divide n
      while (n%i == 0)
      {
         if( primes.empty() || primes[primes.size()-2] != i )
         {
            primes.push_back( i );
            primes.push_back( 1 );
         }
         else
            ++primes[primes.size()-1];

         n = n/i;
      }
   }


   // This condition is to handle the case whien n is a prime number
   // greater than 2
   if (n > 2)
   {
      primes.push_back( n );
      primes.push_back( 1 );
   }

}

