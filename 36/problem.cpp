#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void getbinary( const int x, vector<int> &base );

int main()
{
   vector<int> base;
   vector<int> palindroms;
   int numholder;
   bool pal;

   for( int i=1; i<1e6; i++ )
   {
      numholder=i;
      base.clear();
      pal= true;

      while( numholder > 0 )
      {
         base.push_back( numholder % 10 );
         numholder = numholder/10;
      }

      for( int j=0; j<base.size(); j++ )
      {
         if( base[j] != base[base.size()-j-1] )
         {
            pal = false;
            break;
         }
      }
      
      if( pal == true )
      {
         getbinary( i, base );

         for( int j=0; j<base.size(); j++ )
         {
            if( base[j] != base[base.size()-j-1] )
            {
               pal = false;
               break;
            }
         }

         if( pal == true )
            palindroms.push_back( i );
      }

   }

   numholder=0;

   for( int i=0; i<palindroms.size(); i++ )
      numholder += palindroms[i];

   cout << numholder << endl;

   return 0;
}

void getbinary( const int x, vector<int> &base )
{

   base.clear();
   int cutoff;


   for( int i=0; pow( 2, i )<=x; i++ )
   {
      cutoff = pow( 2, i );

      cutoff &= x;

      if( cutoff == 0 )
         base.push_back( 0 );
      else
         base.push_back( 1 );

   }


}

