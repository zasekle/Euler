#include <iostream>

using namespace std;

//NOTE BRUTE FORCE METHOD -- DOES NOT WORK IN A TIMELY FASHION

//size 3 is a 2x2 size 4 is a 3x3 ect.
const int size = 17;

int main()
{
   int matrix[size][size][2];
   long long paths = 1;
   int cursor[2] = {size-1,size-1};
   char x;

   /*[0] designates which ways are left to go, [1] says if it is part of the path
   for [0] 0 is both ways gone, 1 is only right gone, 2 is only down gone, 3 is neither way gone
   for [1] 0 means it is not part of the path, 1 means it is part of the path*/

   //set everything to proper values path goes across top right then down the right side
   for( int i=0; i<size; i++ )
   {
      for( int j=0; j<size; j++ )
      {
         if( j==(size-1) )
         {
            matrix[i][j][0] = 0;
            matrix[i][j][1] = 1;
         }
         else if( i==(size-1) )
         {
            matrix[i][j][0] = 2;
            matrix[i][j][1] = 0;
         }
         else if( i==0 )
         {
            matrix[i][j][0] = 1;
            matrix[i][j][1] = 1;
         }
         else
         {
            matrix[i][j][0] = 3;
            matrix[i][j][1] = 0;
         }
      }
   }

   while( matrix[0][0][0] >= 0 )
   {
      //puts cursor on the previously unused value in the grid
      while( matrix[cursor[0]][cursor[1]][0] == 0 && !(cursor[0] == 0 && cursor[1] == 0) )
      {
         if( cursor[0]==(size-1) && cursor[1]==(size-1) )
         {
            matrix[cursor[0]][cursor[1]][0] = 0;
            matrix[cursor[0]][cursor[1]][1] = 0;
         }
         else if( cursor[1]==(size-1) )
         {
            matrix[cursor[0]][cursor[1]][0] = 1;
            matrix[cursor[0]][cursor[1]][1] = 0;
         }
         else if( cursor[0]==(size-1) )
         {
            matrix[cursor[0]][cursor[1]][0] = 2;
            matrix[cursor[0]][cursor[1]][1] = 0;
         }
         else
         {
            matrix[cursor[0]][cursor[1]][0] = 3;
            matrix[cursor[0]][cursor[1]][1] = 0;
         }

         if( cursor[0] != 0 && matrix[cursor[0]-1][cursor[1]][1] == 1 )
         {
            cursor[0] = cursor[0]-1;
         }
         else if( cursor[1] != 0 && matrix[cursor[0]][cursor[1]-1][1] == 1 )
         {
            cursor[1] = cursor[1]-1;
         }
      }

      //ending condition
      if( cursor[0] == 0 && cursor[1] == 0 && matrix[0][0][0] == 0 )
         matrix[0][0][0] = -1;

      //finds an new path to the end
      else
      {
         while( cursor[0] != (size-1) || cursor[1] != (size-1) )
         {
            if( matrix[cursor[0]][cursor[1]][0] == 1 )
            {
               matrix[cursor[0]][cursor[1]][0] = 0;
               matrix[cursor[0]][cursor[1]][1] = 1;
               cursor[0]++;
            } 
            else if( matrix[cursor[0]][cursor[1]][0] == 2 )
            {
               matrix[cursor[0]][cursor[1]][0] = 0;
               matrix[cursor[0]][cursor[1]][1] = 1;
               cursor[1]++;
            }
            else if( matrix[cursor[0]][cursor[1]][0] == 3 )
            {
               matrix[cursor[0]][cursor[1]][0] = 1;
               matrix[cursor[0]][cursor[1]][1] = 1;
               cursor[1]++;
            }
            else if( matrix[cursor[0]][cursor[1]][0] == 0 )
            {
               cout << "ERROR" << endl;
            }
         }
         paths++;
      }

      /*cout << "cursor = " << cursor[0] << ',' << cursor[1] << endl;
      for( int i=0; i<size; i++ )
      {
         for( int j=0; j<size; j++ )
         {
            cout << matrix[i][j][0] << ',' << matrix[i][j][1] << ' ';
         }
         cout << endl;
      }
      cin >> x;
      cout << endl;*/
   }

   //prints final number of paths
   cout << endl << "Number of paths for grid size " << size-1 << endl << paths << endl;

   return 0;
}

