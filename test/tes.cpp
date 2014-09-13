#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include "pseive.h"

using namespace std;
using namespace chrono;

const int limit = 1e8;

high_resolution_clock::time_point t1 = high_resolution_clock::now();

pseive seive( limit );

vector<int> primelist;

//this clears the vector sent to it
void getDivisors( int, vector<int>& );

void possDivisors( vector<int>&, vector<int>&, int, int=1 );

void primeFactors( int n, vector<int>&primes );

bool isprime( int );

int main()
{
   int size = sqrt( limit );
   vector<int> myvec;

   for( int i=2; i<=size; i++ )
      if( isprime( i ) )
         primelist.push_back( i );

   //for( int i=2; i<limit; ++i )
   //{
      //myvec.clear();
      //getDivisors( i, myvec );
   //}

   cout << "(1) 1,";

   int sum;

   for( int i=2; i<101; i++ )
   {
      myvec.clear();

      sum =0;

      primeFactors( i, myvec );

      cout << '(' << i << ") ";

      for( int j=0; j<myvec.size(); j++ )
      {
         sum += myvec[j];
         //cout << myvec[j] << ',';
      }

      cout << sum << ' ';


      if( (i) % 10 == 0 && i != 2 )
         cout << endl;

   }

   cout << endl;

   high_resolution_clock::time_point t2 = high_resolution_clock::now();

   duration<double> time_span = duration_cast<duration<double>>(t2-t1);

   cout << "seconds" << endl << time_span.count() << endl;

   return 0;
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


bool isprime( int x )
{
   return !seive.getbit( x );  
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
         primes.push_back( temp );

         n = n/temp;

         if( n == 1 )
            return;
      }

      if( isprime( n ) )
      {
         primes.push_back( n );
         return;
      }
   }

   if( isprime( n ) )
   {
      primes.push_back( n );
   }
}

