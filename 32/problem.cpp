#include <iostream>
#include <vector>

using namespace std;

int main()
{
   vector<int> nums;
   int multiplicand, multiplier, product;
   int compare[9][2];
   int temp;
   bool found = true;
   bool set = false;

   for( int i=0; i<9; i++ )
      compare[i][0] = i+1;

   for( int i=1; i<100; i++ )
   {
      found = true;

      for( int j=0; j<10000; j++ )
      {
         found = true;
         multiplicand = i;
         multiplier = j;
         product = i*j;

         //0 is unused 1 is used
         for( int k=0; k<9; k++ )
            compare[k][1] = 0;

         for( int k=0; k<9 && found == true; k++ )
         {
            temp = -1;
            if( multiplicand != 0 )
            {
               temp = multiplicand % 10;
               multiplicand = multiplicand/10;
            }
            else if( multiplier != 0 )
            {
               temp = multiplier % 10;
               multiplier = multiplier/10;
            }
            else if( product != 0 )
            {
               temp = product % 10;
               product = product/10;
            }
            if( temp != -1 )
            {
               for( int l=0; l<9; l++ )
               {
                  if( temp == compare[l][0] && compare[l][1] == 0 )
                     compare[l][1] = 1;
                  else if( temp == compare[l][0] && compare[l][1] == 1 )
                  {
                     found = false;
                     break;
                  }
               }
            }
            else
               found = false;

         }

         if( multiplicand == 0 && multiplier == 0 && product == 0 && found == true )
         {
            set = true;
            for( int l=0; l<9; l++ )
               if( compare[l][1] != 1 )
                  set = false;

            if( set == true )
            {
               nums.push_back( i );
               nums.push_back( j );
            }
         }
      }
   }

   vector<int> final;

   for( int i=0; i<nums.size(); i=i+2 )
   {
      set = true;
      for( int j=0; j<final.size(); j++ )
      {
         if( final[j] == nums[i]*nums[i+1] )
            set = false;
      }
      if( set == true )
         final.push_back( nums[i]*nums[i+1] );
   }

   int sum=0;

   for( int i=0; i<final.size(); i++ )
      sum += final[i];

   cout << "Answer" << endl << sum << endl;

   return 0;
}
