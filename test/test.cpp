#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include "pseive.h"
#include <queue>

using namespace std;
using namespace chrono;

const int limit = 1e5;

//this clears the vector sent to it
void getCombos( const int, vector<vector<int> >& );

int getDivisors( const int, vector<int>& );

void primeFactors( int, vector<int>& );

void possDivisors( vector<int>&, const vector<int>&, const int, const int=1 );

void factors( const int, vector<vector<int> > &, vector<int>, const vector<int>&, const int=0, const int=2 );

void facCombos( const int, vector<vector<int> > & );

bool isprime( const int x );

high_resolution_clock::time_point t1, t2, t3;
duration<double> time_span_other;
duration<double> time_span_divisors;

pseive seive( limit );

vector<int> primelist;

vector<vector<int> > rootv;

int main()
{
   time_span_other = time_span_divisors = duration<double>::zero();

   vector<vector<int> > mynum;
   vector<int> temp;
   int input;
   int size = sqrt( limit );
   long long power;

   //push primes onto a stack up to sqrt of limit
   for( int i=2; i<=size; i++ )
      if( isprime( i ) )
         primelist.push_back( i );


   //find all the possible roots up to limit 
   for( int j=4; true; j++ )
   {
      power = pow( 2, j );

      if( power > limit )
         break;

      for( int i=3; power<=limit; i++ )
      {
         temp.push_back( power );
         power = pow( i, j );
      }

      temp.push_back( limit+1 );

      rootv.push_back( temp );

      temp.clear();
   }

   cout << "Enter number" << endl;
   cin >> input;

   t1=high_resolution_clock::now();;
   //for( int i=2; i<=limit; i++ )
   {
      mynum.clear();
      //no recursion (slower)
      cout << "No Recursion" << endl;
      getCombos( input, mynum ); 
      //recursion (faster)
      cout << endl << "Recursion" << endl;
      facCombos( input, mynum ); 
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

      for( int j=0; j<mynum[i].size(); ++j )
      {
         if( j!=0 )
            cout << ',' << mynum[i][j];
         else
            cout << mynum[i][j];
      }

      cout << endl;
   }

   cout << endl << "My algorithm time " << endl << time_span_divisors.count() << endl;
   cout << endl << "Other stuff time " << endl << time_span_other.count() << endl;

   return 0;
}

void getCombos( const int x, vector<vector<int> > &mynum )
{

   queue<vector<int> > holder;
   vector<int> divisors, tempv;
   int qsize, size, end, btempv, temp, newn, min;
   int counter = 0;

   mynum.clear();

   end = getDivisors( x , divisors );

   t2 = high_resolution_clock::now();
   time_span_other += duration_cast<duration<double>>(t2-t1);
   t1 = high_resolution_clock::now();

   tempv.push_back( 1 );
   tempv.push_back( x );
   mynum.push_back( tempv );

   //this loop goes through each level 2 divisors then 3 ect...
   for( int i=2; i<=end; i++ )
   {
      tempv.clear();
      tempv.push_back( x );
      holder.push( tempv );

      //this loop goes through each level of divisors up to the limit set by i
      for( int l=i; l!=1; l-- )
      {
         qsize = holder.size();

         //this loopgoes thru the queue to each set of divisors
         for( int m=0; m<qsize; m++ )
         {
            tempv = holder.front();
            holder.pop();

            btempv = tempv.back();
            tempv.pop_back();

            if( tempv.size() > 1 )
               min = tempv.back();
            else
               min = 0;

            if( l == 2 )
               size = sqrt( btempv );
            else if( l == 3 )
               size = cbrt( btempv );
            else
            {
               if( l-4 > rootv.size() )
                  size = 1;
               else
                  for( int j=0; true; j++ )
                     if( rootv[l-4][j]>btempv ) 
                     {
                        size = j+1;
                        break;
                     }
            }

            //this loop goes through each factor
            for( int j=0; divisors[j]<=size; j++ )
            {
               while( btempv % divisors[j] != 0 )
                  j++;
               if( divisors[j] > size )
                  break;

               if( min<=divisors[j] )
               {
                  temp = divisors[j];
                  newn = btempv/temp;

                  tempv.push_back( temp );
                  tempv.push_back( newn );

                  holder.push( tempv );

                  tempv.pop_back();
                  tempv.pop_back();
                  cout << temp << ',' << newn << endl;
                  counter++;
               }
            }
            cout << counter << endl;
            counter = 0;
         }
      }

      //loop to copy queue to vector
      while( !holder.empty() )
      {
         tempv = holder.front();
         mynum.push_back( tempv );
         holder.pop();
      }

   }

   t2 = high_resolution_clock::now();
   time_span_divisors += duration_cast<duration<double>>(t2-t1);
   t1 = high_resolution_clock::now();

}

void facCombos( const int x, vector<vector<int> > &mynum )
{

   vector<int> newv;
   vector<int> divisors;
   int size;
   int end;

   end = getDivisors( x , divisors );

   mynum.clear();

   for( int i=2; i<=end; i++ )
      factors( x, mynum, newv, divisors, 0, i );

}

int getDivisors( const int x, vector<int> &divis )
{
   vector<int> primef;

   divis.clear();

   primeFactors( x, primef );

   int size = primef.size()/2;

   int end = 0;

   for( int i=1; i<primef.size(); i=i+2 )
      end = end + primef[i];

   possDivisors( divis, primef, size );

   sort( divis.begin(), divis.end() );

   return end;

}

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

void possDivisors( vector<int> &divis, const vector<int> &primes, const int loop, const int div )
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

void factors( const int x, vector<vector<int> > &mynum, vector<int> prev, const vector<int>&divisors, const int min, const int div )
{

   vector<int> tempv;
   int size;
   int temp;
   int newn;
   int counter=0;

   if( div == 2 )
      size = sqrt( x );
   else if( div == 3 )
      size = cbrt( x );
   else
   {
      if( div-4 > rootv.size() )
         size = 1;
      else
         for( int i=0; true; i++ )
            if( rootv[div-4][i]>x ) 
            {
               size = i+1;
               break;
            }
   }

   for( int i=0; divisors[i]<=size; i++ )
   {
      while( x % divisors[i] != 0 )
         i++;
      if( divisors[i] > size )
         break;

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
         cout << temp << ',' << newn << endl;
         counter++;
      }
      else if( min<=divisors[i] && div>2 )
      {
         temp = divisors[i];
         newn = x/temp;

         if( !isprime( newn ) )
         {
            prev.push_back( temp );

            factors( newn, mynum, prev, divisors, temp, div-1 );

            prev.pop_back();
         }
         cout << temp << ',' << newn << endl;
         counter++;
      }
   }
   cout << counter << endl;

}

bool isprime( const int x )
{
   return !seive.getbit( x );  
}

