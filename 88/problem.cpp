#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

//do not run 0 or 1 in this its a problem with the primeFactors function
//const int findnum = 371651280;

//this clears the vector sent to it
void getCombos( int, vector<vector<int> >& );

void getDivisors( int, vector<int>& );

void primeFactors( int, vector<int>& );

void possDivisors( vector<int>&, vector<int>&, int, int=1 );

void factors( int, vector<vector<int> >&, vector<int>, int=0, int=2 );

int main()
{
   vector<vector<int> > mynum;
   vector<int> newv;
   int answer=0;
   int sum;
   int counter = 1;
   int multi;
   bool found = false;
   bool end = false;
   clock_t t1, t2;

   t1=clock();

   for( int i=2; end == false; i++ )
   {
      getCombos( i, mynum );
      found = false;

      for( int j=0; j<mynum.size(); j++ )
      {
         sum = 0;
         for( int k=0; k<mynum[j].size(); k++ )
         {
            sum = sum + mynum[j][k];
         }
         if( sum <= i )
         {
            counter++;
            if( found == false )
            {
               answer = answer + i;
               newv.push_back( i );
               found = true;
            }
            if( counter >= 12 )
            {
               end = true;
               break;
            }
         }
         cout << "Combinations of divisors of ";

         multi=1;

         if( !mynum.empty() )
            for( int l=0; l<mynum[0].size(); l++ )
               multi = multi * mynum[0][l];

         cout << multi << endl;

         for( int l=0; l<mynum.size(); l++ )
         {
            cout << l+1 << ": ";

            for( int k=0; k<mynum[l].size(); k++ )
            {
               if( k!=0 )
                  cout << ',' << mynum[l][k];
               else
                  cout << mynum[l][k];
            }

            cout << endl;
         }
         cout << "counter:" << counter << " sum:" << sum << endl << endl;
      }

   }

   t2=clock();
   float diff( (float)t2-(float)t1 );
   float seconds = diff/CLOCKS_PER_SEC;

         cout << "Combinations of divisors of ";

         multi=1;

         if( !mynum.empty() )
            for( int l=0; l<mynum[0].size(); l++ )
               multi = multi * mynum[0][l];

         cout << multi << endl;

         for( int l=0; l<mynum.size(); l++ )
         {
            cout << l+1 << ": ";

            for( int k=0; k<mynum[l].size(); k++ )
            {
               if( k!=0 )
                  cout << ',' << mynum[l][k];
               else
                  cout << mynum[l][k];
            }

            cout << endl;
         }
         cout << "counter:" << counter << " sum:" << sum << endl << endl;
   cout << "Answer" << endl << answer << endl;

   cout << endl << "Seconds" << endl << seconds << endl;

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

   newv.clear();

   newv.push_back( 1 );
   newv.push_back( x );

   mynum.push_back( newv );

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

   getDivisors( x, divisors );

   for( i=0; i<divisors.size() && divisors[i]<=size; i++ )
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
/*cout << "Combinations of divisors of ";

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
  }*/
