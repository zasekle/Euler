#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

//height of triangle
const int size=120;

int main()
{
   high_resolution_clock::time_point t1 = high_resolution_clock::now();

   ifstream fin( "nums" );
   int i, j, x=1;
   int triangle[size][size];

   for( i=0; i<size; i++ )
   {
      for( j=0; j<size; j++ )
         triangle[i][j] = 0;
   }

   i=0;
   j=0;

   while( fin.good() )
   {
      if( i == x )
      {
         i=0;
         j++;
         x++;
      }

      fin >> triangle[j][i];
      i++;
   }

   
   /*for( i=0; i<size; i++ )
   {
      x=0;
      for( j=0; j<size; j++ )
      {
         if( triangle[i][j] >0 && triangle[i][j] <10 )
            cout << '0';
         if( triangle[i][j] != 0 )
            cout << triangle[i][j] << ' ';
         x = x + triangle[i][j];
      }

      if( x != 0 )
         cout << endl;
   }*/

   //height
   for( i=(size-1); i>0; i-- )
   {
      //width
      for( j=0; j<i; j++ )
      {
         if( triangle[i][j] > triangle[i][j+1] )
            triangle[i-1][j] = triangle[i-1][j] + triangle[i][j];
         else
            triangle[i-1][j] = triangle[i-1][j] + triangle[i][j+1];
      }
   }

   high_resolution_clock::time_point t2 = high_resolution_clock::now();

   cout << endl << "Answer" << endl << triangle[0][0] << endl;

   duration<double> time_span = duration_cast<duration<double>>( t2-t1 );

   cout << "duration " << time_span.count() << endl;

   fin.close();

   return 0;
}
