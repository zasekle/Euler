#include <iostream>
#include <cmath>

using namespace std;

int main()
{
   long long sum=1;
   int i, sqroot, multiple, j=50;

   while( multiple <=250 )
   {
      multiple=0;
      sum = (j*(j+1))/2;
      sqroot = sqrt(sum);

         cout << j << ": ";
      for( i=1; i<=sqroot; i++ )
      {
         if( sum % i == 0 )
         {
            multiple++;
            cout << i << ',' << j << ' ';
         }
         //cout << i << ' ' << sum << ' ' << sum % i << ' ' << multiple << endl;
      }

      cout << endl << endl;

      if( multiple > 0)
         //cout << j << ": " << ' ' << multiple << endl;

      j++;
   }

   cout << sum;

   return 0;
}

