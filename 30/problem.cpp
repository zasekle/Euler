#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
   int nums[10];
   int power = 5;
   vector<int> final;

   for( int i=0; i<10; i++ )
      nums[i] = pow( i, power );

   int max=0;

   for( int i=0; i<power+1; i++ )
      max += nums[9];

   int temp;
   int sum;

   for( int i=2; i<max; i++ )
   {
      temp = i;
      sum = 0;
      while( temp > 0 )
      {
         sum = sum + nums[temp % 10];
         temp = temp/10;
      }

      if( sum == i )
         final.push_back( sum );
   }

   int size = final.size();

   cout << "Numbers for power " << power << endl;

   for( int i=0; i<size; i++ )
      cout << final[i] << ',';

   sum = 0;

   for( int i=0; i<size; i++ )
      sum = sum + final[i];

   cout << endl << "Answer" << endl << sum << endl;

   return 0;
}
