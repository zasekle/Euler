#include <iostream>
#include <vector>

using namespace std;

//do size+1 for this
const long size = 1000000;

int main()
{
   vector<vector<int> > divis(size+1);
   vector<int> nums;
   long sum = 0;

   //get all divisors below size
   for( long i=1; i<=size; i++ )
   {
      for( long j=i; j*i <= size; j++ )
      {
         if( j!=i )
         {
            divis[i*j].push_back( i );
            divis[i*j].push_back( j );
         }
         else
            divis[i*j].push_back( j );
      }
   }

   /*
   for( long i=0; i<size; i++ )
   {
         cout << endl << i << ": "; 
      for( long j=0; j<divis[i].size(); j++ )
      {
         if( j!= 0 )
            cout << ',';
         cout << divis[i][j];
      }
   }
   cout << endl;*/

   //find sums of all digits
   for( long i=0; i<size; i++ )
   {
      sum = 0;
      for( long j=0; j<divis[i].size(); j++ )
      {
         sum = sum + divis[i][j];
      }

      sum = sum-i;
      divis[i].clear();

      divis[i].push_back( sum );

   }

   //find amicable numbers
   for( long i=2; i<size; i++ )
   {
      if( divis[i][0] < size && i == divis[divis[i][0]][0] && i != divis[i][0] )
      {
         nums.push_back( divis[i][0] );
      }
   }

   /*
   for( int i=0; i<nums.size(); i++ )
         cout <<  i << ": " << nums[i] << endl;*/ 
         

   sum = 0;

   for( long i=0; i< nums.size(); i++ )
      sum = sum + nums[i];

   cout << "Answer" << endl << sum << endl;

   return 0;
}
