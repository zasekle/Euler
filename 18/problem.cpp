#include <iostream>
#include <fstream>

using namespace std;

//height of triangle
const int size=12;

int main()
{
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

   cout << endl << "Answer" << endl << triangle[0][0] << endl;

   fin.close();

   return 0;
}
