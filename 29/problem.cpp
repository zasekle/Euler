#include <iostream>
#include <vector>
#include "Bignums.h"

using namespace std;

//note this is just a brute force method its not very efficient

int main()
{
   Bignum x;
   Bignum y;
   vector<Bignum> numbers;
   bool exists;
   int size;
   
   for( int a=2; a<101; a++ )
   {
      x = a;
      for( int b=2; b<101; b++ )
      {
         x = a;
         x = x/b;

         size = numbers.size();
         for( int i=0; i<size; i++ )
         {
            exists = false;

            if( x == numbers[i] )
            {
               exists = true;
               i=size;
            }
         }

         if( exists == false )
            numbers.push_back( x );

      }

   }

   size = numbers.size();

   /*for( int i=0; i<size; i++ )
      cout << numbers[i] << ',';
*/
   cout << endl << "Size" << endl << size << endl;

   return 0;
}
