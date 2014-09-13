#include <iostream>

using namespace std;

int fac( int );

int main()
{
   int numhold;
   long long final;

   for( int i=3; i<1e6; i++ )
   {
      numhold = i;
      final = 0;

      while( numhold > 9 )
      {
         final += fac(numhold % 10);
         numhold = numhold/10;
      }

      final += fac(numhold);

      if( final == i )
         cout << i << endl;

   }


   return 0;
}

int fac( int x )
{
   if( x > 1 )
      return x*fac( x-1 );

   return 1;

}
