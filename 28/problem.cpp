#include <iostream>

using namespace std;

//size of the array
const int size = 1001;

int main()
{
   int matrix[size][size];

   for( int i=0; i<size; i++ )
      for( int j=0; j<size; j++ )
         matrix[i][j] = 0;

   int final = size*size;
   int x= size/2;
   int y=size/2;
   int number=2;
   int moves=1;

   matrix[x][y]=1;

   for( int i=1; number<final; i++ )
   {
      for( int j=0; j<moves; j++ )
      {
         if( i % 4 == 0 )
            x--;
         else if( i % 4 == 1 )
            y++;
         else if( i % 4 == 2 )
            x++;
         else if( i % 4 == 3 )
            y--;

         matrix[x][y]=number;
         number++;
      }

      if( i % 2 == 0 )
         moves++;
   }

   int sum=0;
   final = size;

   for( int i=0, j=0; i<final; i++, j++ )
      sum = sum + matrix[i][i];

   for( int i=size-1, j=0; j<final; i--, j++ )
      sum = sum + matrix[i][j];

   sum--;

   cout << "Sum" << endl << sum << endl;
}
