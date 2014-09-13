#include <iostream>
#include <algorithm>

using namespace std;

int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

int getnum( int hun, int ten, int one );

int main()
{
   long long answer = 0;

   sort( nums, nums+10 );

   do
   {
      if( (getnum(1,2,3) % 2) == 0 && (getnum(2,3,4) % 3) == 0 && (getnum(3,4,5) % 5) == 0 && (getnum(4,5,6) % 7) == 0 
          && (getnum(5,6,7) % 11) == 0 && (getnum(6,7,8) % 13) == 0 && (getnum(7,8,9) % 17) == 0 )
         answer += nums[9] + 10*nums[8] + 10e1*nums[7] + 10e2*nums[6] + 10e3*nums[5] + 10e4*nums[4] + 10e5*nums[3] + 10e6*nums[2] + 10e7*nums[1] + 10e8*nums[0];

   }while( next_permutation( nums, nums+10 ) );

   cout << "Answer = " << answer << endl;

   return 0;
}

int getnum( int hun, int ten, int one )
{
   return (100*nums[hun]+10*nums[ten]+nums[one]);
}
