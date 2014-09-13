#include <iostream>

using namespace std;

//size 3 is a 2x2 size 4 is a 3x3 ect.
const int size = 17;

int main()
{
   long long matrix[size][size];

   for( int i=0; i<size; i++ )
   {
      matrix[i][0] = 1;
      matrix[0][i] = 1;
   }

   for( int i=1; i<size; i++ )
   {
      for( int j=1; j<size; j++ )
      {
         matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
      }
   }

   cout << endl << "Number of paths for grid size " << size-1 << endl << matrix[size-1][size-1] << endl;

   return 0;
}

