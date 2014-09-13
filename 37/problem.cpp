#include <iostream>
#include <cmath>
#include <vector>
#include"pseive.h"

using namespace std;

pseive seive( 1e6 );

bool isprime( const int x );

int main()
{
   vector<int> trunc;
   int numholder, power, modnum;
   bool isnum;

   for( int i=11; i<1e6; i++ )
   {
      if( isprime( i ) )
      {
         numholder = i;
         isnum = true;

         numholder = numholder/10;

         while( 0 < numholder )
         {
            if( !isprime( numholder ) )
            {
               isnum = false;
               break;
            }

            numholder = numholder/10;
         }

         if( isnum == true )
         {
            numholder = i;

            for( int j=1; pow( 10, j )<i; j++ )
               power = j;

            modnum = pow( 10, power );
            numholder = numholder % modnum;
            modnum = modnum/10;
            
            while( 0 < numholder )
            {

               if( !isprime( numholder ) )
               {
                  isnum = false;
                  break;
               }
               numholder = numholder % modnum;
               modnum = modnum/10;
            }

            if( isnum == true )
               trunc.push_back( i );
         }
      }
   }

   numholder = 0;

   for( int i=0; i<trunc.size(); i++ )
      numholder += trunc[i];

   cout << numholder << endl;

   return 0;
}

bool isprime( const int x )
{
   return !seive.getbit( x );
}
