#include <iostream>

using namespace std;

int main()
{
   int holder=2, final=0, output;
   long long sequence;

   for( int i=2; i<1000000; i++ )
   {
      holder=2;
      sequence = i;

      //cout << "1=" << i << ' ';

      while( sequence != 1 )
      {
         if( sequence % 2 == 0 )
            sequence = sequence/2;
         else
            sequence = 3*sequence+1;

         //cout << holder << '=' << sequence << ' ';

         holder++;
      }

      //cout << endl;

      if( final < holder )
      {
         final = holder;
         output = i;
         cout << "i = " << output << " holder = " << final << endl;
      }

   }

   

   cout << output << endl;

   return 0;
}
