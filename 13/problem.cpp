#include <iostream>
#include <fstream>

using namespace std;

int main()
{
   ifstream fin("nums");
   char temp;
   int sum = 0;
   int input[50];
   int final[55];

   for( int i=0; i<55; i++ )
      final[i]=0;

   for( int j=0; j<100; j++ )
   {
      for( int i=49; i>=0; i-- )
      {
         fin >> temp;
         input[i] = temp - '0';
      }

      for( int i=0; i<55; i++ )
      {
         sum = sum+final[i];

         if( i<50 )
            sum = sum+input[i];

         if( sum > 9 )
         {
            final[i] = sum % 10;
            sum = sum/10;
         }
         else
         {
            final[i] = sum;
            sum = 0;
         }
      }
   }

   bool flag=false;
   int loop=0;

   for( int i=54; i>=0; i-- )
   {
      if( flag == false && final[i] != 0 )
      {
         flag = true;
         loop = (i+2) % 3;
      }

      if( flag != false )
      {
         if( loop == 3 )
         {
            cout << ' ';
            loop = 0;
         }

         cout << final[i];
         loop++;
      }
   }

   cout << endl;

   return 0;
}
