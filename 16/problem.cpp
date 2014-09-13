#include <iostream>

using namespace std;

//size of the final number
const int size=1200;

//power going to
const int pow=1000;

int main()
{
   int matrix[size];
   int tempi;
   int carry=0;

   for( int i=0; i<size; i++ )
      matrix[i] = 0;

   //using [0] as the smallest digit and size-1 as the biggest digit
   matrix[0] = 2;

   for( int j=pow; j>1; j-- )
   {
      for( int i=0; i<size; i++ )
      {
         tempi = (2*matrix[i]) + carry;

         if( tempi > 9 )
         {
            matrix[i] = tempi % 10;
            carry = tempi/10;
         }
         else
         {
            matrix[i] = tempi;
            carry = 0;
         }
      }
   }

   bool flag = false;

   cout << "2^" << pow << endl;

   for( int i=(size-1); i>=0; i-- )
   {
      if( matrix[i] != 0 && flag == false )
      {
         flag = true;
      }
      if( flag == true )
      {
         cout << matrix[i];
      }
   }

   int final=0;

   for( int i=0; i<size; i++ )
   {
      final = final + matrix[i];
   }

   cout << endl << endl << "Final Answer" << endl << final << endl;
   return 0;
}
