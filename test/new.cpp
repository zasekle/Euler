#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <chrono>
#include "pseive.h"

using namespace std;
using namespace chrono;

const int limit = 1e4;

//this clears the vector sent to it
void getCombos( int, vector<vector<int> >& );

void getDivisors( int, vector<int>& );

void primeFactors( int, vector<int>& );

void possDivisors( vector<int>&, vector<int>&, int, int=1 );

void factors( int, vector<vector<int> >&, vector<int>, int=0, int=2 );

bool isprime( int x );

high_resolution_clock::time_point t1, t2;
duration<double> time_span_other;
duration<double> time_span_divisors;

pseive seive( limit );

vector<int> primelist;

int main()
{
   time_span_other = time_span_divisors = duration<double>::zero();

   vector<vector<int> > mynum;
   vector<int> newv;
   int input;
   int size = sqrt( limit );

   for( int i=2; i<=size; i++ )
      if( isprime( i ) )
         primelist.push_back( i );

   cout << "Enter number" << endl;
   cin >> input;

   t1=high_resolution_clock::now();;
   //for( int i=2; i<limit; i++ )
   {
      mynum.clear();
      getCombos( input, mynum ); 
   }

   t2=high_resolution_clock::now();
   time_span_other += duration_cast<duration<double>>(t2-t1);

   cout << "Combinations of divisors of ";

   int multi=1;

   if( !mynum.empty() )
      for( int i=0; i<mynum[0].size(); i++ )
         multi = multi * mynum[0][i];

   cout << multi << endl;

   for( int i=0; i<mynum.size(); i++ )
   {
      cout << i+1 << ": ";

      for( int j=0; j<mynum[i].size(); j++ )
      {
         if( j!=0 )
            cout << ',' << mynum[i][j];
         else
            cout << mynum[i][j];
      }

      cout << endl;
   }

   cout << endl << "Divisors time " << endl << time_span_divisors.count() << endl;
   cout << endl << "Other stuff time " << endl << time_span_other.count() << endl;

   return 0;
}

void getCombos( int x, vector<vector<int> > &mynum )
{

   vector<int> newv;
   int size;

   mynum.clear();

   //the ending statement for this is inefficient is has to run the function an extra time
   //however this way I can avoid storing prime numbers to check and see if the final array is
   //all prime
   for( int i=2; true; i++ )
   {
      size = mynum.size();
      factors( x, mynum, newv, 0, i );

      if( size == mynum.size() )
         break;
   }

}

void getDivisors( int x, vector<int> &divis )
{
   vector<int> primef;

   divis.clear();

   primeFactors( x, primef );

   int size = primef.size()/2;

   possDivisors( divis, primef, size );

   sort( divis.begin(), divis.end() );

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
   int temp;
   for (int i = 0; primelist[i] <= sqrt(n); ++i)
   {
      temp = primelist[i];

      // While i divides n divide n
      while (n%temp == 0)
      {
         if( primes.empty() || primes[primes.size()-2] != temp )
         {
            primes.push_back( temp );
            primes.push_back( 1 );
         }
         else
            ++primes[primes.size()-1];

         n = n/temp;

         if( n == 1 )
            return;
      }

      if( isprime( n ) )
      {
         primes.push_back( n );
         primes.push_back( 1 );
         return;
      }
   }

   if( isprime( n ) )
   {
      primes.push_back( n );
      primes.push_back( 1 );
   }
}

void factors( int x, vector<vector<int> > &mynum, vector<int> prev, int min, int div )
{

   vector<int> tempv;
   vector<int> divisors;
   double denom = div;
   double root = 1/denom;
   int size = pow( x, root );
   int temp;
   int newn;
   int i;

   t2 = high_resolution_clock::now();
   time_span_other += duration_cast<duration<double>>(t2-t1);
   t1 = high_resolution_clock::now();
   getDivisors( x, divisors );
   t2 = high_resolution_clock::now();
   time_span_divisors += duration_cast<duration<double>>(t2-t1);
   t1 = high_resolution_clock::now();

   for( i=0; divisors[i]<=size; i++ )
   {
      if( min <= divisors[i] && div==2 )
      {
         temp = divisors[i];
         newn = x/temp;

         tempv.clear();

         for( int j=0; j<prev.size(); j++ )
            tempv.push_back( prev[j] );

         tempv.push_back( temp );
         tempv.push_back( newn );

         mynum.push_back( tempv );
      }
      else if( min<=divisors[i] && div>2 )
      {
         temp = divisors[i];
         newn = x/temp;

         prev.push_back( temp );

         factors( newn, mynum, prev, temp, div-1 );

         prev.pop_back();
      }
   }
}

bool isprime( int x )
{
   return !seive.getbit( x );  
}
