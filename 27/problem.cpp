#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>

using namespace std;

//find all the primes to this number
const int tonum = 200000;

int main()
{
   //clock
   clock_t t1, t2;
   t1=clock();

   //prime siv
   int nums[tonum][2];
   int final = sqrt(tonum);
   vector<int> primes;

   for( int i=0; i<tonum; i++ )
   {
      nums[i][0] = i;
      nums[i][1] = 1;
   }

   nums[0][1] = 0;
   nums[1][1] = 0;

   for( int i=2; i<final; i++ )
      for( int j=i; j*i<tonum; j++ )
         nums[i*j][1] = 0;
   
   for( int i=0; i<tonum; i++ )
      if( nums[i][1] == 1 )
         primes.push_back( nums[i][0] );
/*
   for( int i=0; i<primes.size(); i++ )
      cout << primes[i] << ',';*/

   int number;
   int answer=0;
   int size = primes.size();
   bool prime;
   int quad;
   int ab[2];

   for( int a=-1000; a<1000; a++ )
   {
      for( int b=primes[0], x=0; b<1000 && x<size; x++, b=primes[x] )
      {
         number = 0;
         prime = true;
         for( int n=0; prime == true; n++ )
         {
            quad = n*n+a*n+b;
            for( int i=0; i<size; i++ )
            {
               prime = false;

               if( primes[i] == quad )
               {
                  prime = true;
                  i = size;
                  number++;
               }
            }

            if( number > answer ) 
            {
               answer = number;
               ab[0] = a;
               ab[1] = b;
            }
         }
      }
   }
   
   t2=clock();
   float diff((float)t2-(float)t1);
   float seconds = diff / CLOCKS_PER_SEC;

   cout << "Time" << endl << seconds << " s" << endl << endl;

   cout << "Answer" << endl << "a=" << ab[0] << " b=" << ab[1] << endl << "Number of primes in a row: " << answer ;

   cout << endl;

   return 0;
}
