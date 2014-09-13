#include <iostream>
#include <fstream>

using namespace std;

int main()
{
   ifstream fin("nums");
   int nums[20][20];

   for( int j=0; j<20; j++ )
   {
      for( int i=0; i<20; i++ )
      {
         fin >> nums[j][i];
      }
   }

   int product=0;
   int final=0;
   
   for( int j=0; j<20; j++ )
   {
      for( int i=0; i<20; i++ )
      {
         //horizontal
         if( i<=16 )
            product=nums[j][i+1]*nums[j][i+2]*nums[j][i+3]*nums[j][i];

         if( product>final )
            final = product;

         //vertical
         if( j<=16 )
            product=nums[j][i]*nums[j+1][i]*nums[j+2][i]*nums[j+3][i];

         if( product>final )
            final = product;

         //to bottom left
         if( i<=16 && j<=16 )
            product=nums[j][i]*nums[j+1][i+1]*nums[j+2][i+2]*nums[j+3][i+3];

         if( product>final )
            final = product;

         //to bottom right
         if( i>2 && j<=16 )
            product=nums[j][i]*nums[j+1][i-1]*nums[j+2][i-2]*nums[j+3][i-3];

         if( product>final )
            final = product;
      }
   }

   cout << final;

   return 0;
}
