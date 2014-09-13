#include <iostream>
#include <vector>

using namespace std;

//do size+1 for this
const int size = 27124;

int main()
{
   vector<vector<int> > divis(size+1);
   vector<int> nums;

   //get all divisors below size
   for( int i=1; i<=size; i++ )
   {
      for( int j=i; j*i <= size; j++ )
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

   
   /*for( int i=1; i<size; i++ )
   {
         cout << endl << i << ": "; 
      for( int j=0; j<divis[i].size(); j++ )
      {
         if( j!= 0 )
            cout << ',';
         cout << divis[i][j];
      }
   }*/

   int sum;

   //find sums of all digits
   for( int i=0; i<size; i++ )
   {
      sum = 0;
      for( int j=0; j<divis[i].size(); j++ )
      {
         sum = sum + divis[i][j];
      }

      sum = sum-i;

      nums.push_back( sum );

   }
   
  /* for( int i=0; i<nums.size(); i++ )
         cout << i << ": " << nums[i] << endl;*/ 

   divis[0].clear();

   //find all abundant numbers
   for( int i=0; i<size; i++ )
   {
      if( nums[i] > i )
      {
         divis[0].push_back( i );
      }
   }

   /*for( int i=0; i<divis[0].size(); i++ )
         cout << i+1 << ": " << divis[0][i] << endl;*/

   nums.clear();

   for( int i=0; i<size; i++ )
      nums.push_back( 1 );

   //find all non abundant numbers
   for( int j=0; j<divis[0].size(); j++ )
   {
      for( int i=j; divis[0][i]+divis[0][j]<size && i<divis[0].size(); i++ )
      {
            nums[divis[0][i]+divis[0][j]]=0;
            //cout << divis[0][i]+divis[0][j] << ' ';
      }

   }

   sum =0;
   for( int i=0; i<size; i++ )
   {
      if( nums[i] == 1 )
      {
         sum = sum + i;
         //cout << i << ": " << nums[i] << endl; 
      }
   }

   cout << "Answer" << endl << sum << endl;
   return 0;
}
