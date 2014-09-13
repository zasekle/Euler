#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//this checks for repeats in each row/column/box
void crossout( int board[9][9][10] );

//this prints the board
void printb( int board[9][9][10] );

//returns upper left box coordinate x for i and y for j
void getboxcoord( int &x, int &y, int i, int j );

//checks for repeating units that can cause cancelations in each row/column/box
void checkrepeats( int board[9][9][10] );

//checks for squares which only have one remaining number
void setfinalnums( int board[9][9][10] );

//searches for a single possibility in each row/column/box and sets the number to a final value if found
void setsingle( int board[9][9][10] );

//searches for comonalities between rows/cols and boxes 
void brcrelation( int board[9][9][10] );

//ending condition for primary loop
bool end( int board[9][9][10] );

//gets the pos of the smallest number
void getsmall( int board[9][9][10], int &x, int &y );

//saves board to backup
void makebackup( int backup[9][9][10], int board[9][9][10] );

//solves the problem?
void solve( int board[9][9][10] );

int main()
{
   int board[9][9][10], backup[9][9][10];
   bool cont = true;
   ifstream fin( "board1" );
   int x, y, small;

   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
         board[i][j][0] = fin.get() - '0';

      fin.get();
   }

   for( int i=0; i<9; i++ )
      for( int j=0; j<9; j++ )
         for( int k=1; k<10; k++ )
            board[i][j][k] = k;

   solve( board );

   printb( board );

   return 0;
}

void solve( int board[9][9][10] )
{
   int x=-1, y=-1;
   int backup[9][9][10];

   while( true )
   {
      for( int i=0; i<10; i++ )
      {
         crossout( board );
         checkrepeats( board );
         brcrelation( board );
         setsingle( board );
         setfinalnums( board );
      }

      if( end( board ) == false )
         return;

      getsmall( board, x, y );

      makebackup( backup, board );

      for( int k=1; k<10; k++ )
         if( board[x][y][k] != 0 )
         {
            small = board[x][y][k];
            board[x][y][k] = 0;
            break;
         }
   }


}

void crossout( int board[9][9][10] )
{

   int temp;

   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         if( board[i][j][0] != 0 )
         {
            temp = board[i][j][0];

            //columns
            for( int k=0; k<9; k++ )
               board[i][k][temp] = 0;

            //rows
            for( int k=0; k<9; k++ )
               board[k][j][temp] = 0;

            //boxes of nine
            for( int k=i-i%3; k<(i-i%3)+3; k++ )
            {
               for( int l=j-j%3; l<(j-j%3)+3; l++ )
               {
                  board[k][l][temp] = 0;
               }
            }
         }
      }
   }



}

void printb( int board[9][9][10] )
{

   int counter;

   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         counter = 0;

         for( int k=0; k<10; k++ )
         {
            if( k == 0 && board[i][j][k] != 0 )
            {
               cout << '-' << board[i][j][k] << '-';
               counter = counter + 3;
            }
            else if( board[i][j][k] != 0 && board[i][j][0] == 0 )
            {
               cout << board[i][j][k];
               counter++;
            }


         }
         while( counter < 6 )
         {
            cout << ' ';
            counter++;
         }

         if( j != 8 )
            cout << " |";

         if( (j+1)%3 == 0 && j != 0 && j != 8 )
            cout << "|| ";
         else
            cout << ' ';

      }

      if( (i+1)%3 == 0 && i != 8 )
      {
         cout << endl;

         for( int k=0; k<82; k++ )
            cout << '-';

      }

      cout << endl;
   }

}

void getboxcoord( int &x, int &y, int i, int j )
{
   x = i-i%3;
   y = j-j%3;
}

void checkrepeats( int board[9][9][10] )
{

   vector<int> cursor;
   vector<int> comparee;
   vector<vector<int> > seq;
   int x, y;

   //search for repeats
   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         if( board[i][j][0] == 0 )
         {
            cursor.clear();

            if( board[i][j][0] == 0 )
            {
               for( int k=1; k<10; k++ )
               {
                  if( board[i][j][k] != 0 )
                     cursor.push_back( k );
               }
            }

            if( !cursor.empty() )
            {
               seq.clear();

               //row
               for( int l=j+1; l<9; l++ )
               {

                  comparee.clear();

                  if( board[i][l][0] == 0 )
                  {
                     for( int k=1; k<10; k++ )
                     {
                        if( board[i][l][k] != 0 )
                           comparee.push_back( k );
                     }

                     if( comparee == cursor )
                        seq.push_back( comparee );
                  }

               }

               //row remove nums
               if( !seq.empty() && seq.size()+1 == seq[0].size() )
               {

                  for( int l=0; l<9; l++ )
                  {

                     if( board[i][l][0] == 0 )
                     {
                        comparee.clear();

                        for( int k=1; k<10; k++ )
                        {
                           if( board[i][l][k] != 0 )
                              comparee.push_back( k );
                        }

                        if( comparee != cursor )
                        {
                           for( int k=0; k<cursor.size(); k++ )
                              board[i][l][cursor[k]] = 0;

                        }
                     }
                  }
               }

               seq.clear();

               //column
               for( int l=i+1; l<9; l++ )
               {

                  comparee.clear();

                  if( board[l][j][0] == 0 )
                  {
                     for( int k=1; k<10; k++ )
                     {
                        if( board[l][j][k] != 0 )
                           comparee.push_back( k );
                     }

                     if( comparee == cursor )
                        seq.push_back( comparee );
                  }

               }

               //column remove nums
               if( !seq.empty() && seq.size()+1 == seq[0].size() )
               {

                  for( int l=0; l<9; l++ )
                  {

                     if( board[l][j][0] == 0 )
                     {
                        comparee.clear();

                        for( int k=1; k<10; k++ )
                        {
                           if( board[l][j][k] != 0 )
                              comparee.push_back( k );
                        }

                        if( comparee != cursor )
                        {
                           for( int k=0; k<cursor.size(); k++ )
                              board[l][j][cursor[k]] = 0;

                        }
                     }
                  }
               }

               seq.clear();

               getboxcoord( x, y, i, j );

               int l=j+1, m=i;

               if( l > y + 2 && m != x + 2 )
               {
                  l=y;
                  m++;
               }

               //box
               while( l < y+3 )
               {

                  comparee.clear();

                  if( board[m][l][0] == 0 )
                  {
                     for( int k=1; k<10; k++ )
                     {
                        if( board[m][l][k] != 0 )
                           comparee.push_back( k );
                     }

                     if( comparee == cursor )
                        seq.push_back( comparee );
                  }

                  if( l == y + 2 && m != x + 2 )
                  {
                     l=y-1;
                     m++;
                  }

                  l++;
               }

               //box remove nums
               if( !seq.empty() && seq.size()+1 == seq[0].size() )
               {
                  getboxcoord( x, y, i, j );

                  for( int l=x; l<x+3; l++ )
                  {
                     for( int m=y; m<y+3; m++ )
                     {

                        if( board[l][m][0] == 0 )
                        {
                           comparee.clear();

                           for( int k=1; k<10; k++ )
                           {
                              if( board[l][m][k] != 0 )
                                 comparee.push_back( k );
                           }

                           if( comparee != cursor )
                           {
                              for( int k=0; k<cursor.size(); k++ )
                                 board[l][m][cursor[k]] = 0;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

void setfinalnums( int board[9][9][10] )
{

   int finalnum;
   bool one, two;

   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         one = false;
         two = false;

         if( board[i][j][0] == 0 )
         {
            for( int k=1; k<10; k++ )
            {
               if( one == true && board[i][j][k] != 0 )
               {
                  two = true;
                  break;
               }

               if( board[i][j][k] != 0 && one == false )
               {
                  one = true;
                  finalnum = board[i][j][k];
               }

            }

            if( two == false )
               board[i][j][0] = finalnum;

            if( two == false && one == false )
               cout << "ERROR" << endl;
         }
      }
   }
}

void setsingle( int board[9][9][10] )
{

   int ipos, jpos, repeat;
   bool cont;

   //check rows for single possible digit
   for( int i=0; i<9; i++ )
   {
      for( int k=1; k<10; k++ )
      {
         cont = true;
         repeat = 0;
         jpos = -1;

         for( int j=0; j<9; j++ )
         {
            if( board[i][j][0] == 0 )
            {
               if( repeat != 0 && board[i][j][k] != 0 )
               {
                  cont = false;
                  break;
               }

               if( board[i][j][k] != 0 && repeat == 0 )
               {
                  repeat = k;
                  jpos = j;
               }
            }

            if( board[i][j][0] == k )
            {
               cont = false;
               break;
            }

         }

         if( cont == true && jpos != -1 )
            board[i][jpos][0] = repeat;

      }
   }

   //check columns for single possible digit
   for( int j=0; j<9; j++ )
   {
      for( int k=1; k<10; k++ )
      {
         cont = true;
         repeat = 0;
         ipos = -1;

         for( int i=0; i<9; i++ )
         {
            if( board[i][j][0] == 0 )
            {
               if( repeat != 0 && board[i][j][k] != 0 )
               {
                  cont = false;
                  break;
               }

               if( board[i][j][k] != 0 && repeat == 0 )
               {
                  repeat = k;
                  ipos = i;
               }
            }
            if( board[i][j][0] == k )
            {
               cont = false;
               break;
            }

         }

         if( cont == true && ipos != -1 )
            board[ipos][j][0] = repeat;

      }
   }

   int x,y;

   //check box for single possible digit
   //this loop is for box #
   for( int m=0; m<9; m++ )
   {
      for( int k=1; k<10; k++ )
      {
         cont = true;
         repeat = 0;
         ipos = -1;
         jpos = -1;

         x = (m/3)*3;

         for( int i=x; i<x+3; i++ )
         {
            y = (m%3)*3;

            for( int j=y; j<y+3; j++ )
            {
               if( board[i][j][0] == 0 )
               {
                  if( repeat != 0 && board[i][j][k] != 0 )
                  {
                     cont = false;
                     break;
                  }

                  if( board[i][j][k] != 0 && repeat == 0 )
                  {
                     repeat = k;
                     ipos = i;
                     jpos = j;
                  }
               }
               if( board[i][j][0] == k )
               {
                  cont = false;
                  break;
               }
            }

         }

         if( cont == true && ipos != -1 )
            board[ipos][jpos][0] = repeat;

      }
   }

}


void brcrelation( int board[9][9][10])
{

   int boxnum, x, y;
   bool cont;

   //rows to boxes
   for( int i=0; i<9; i++ )
   {
      for( int k=1; k<10; k++ )
      {
         boxnum = -1;
         cont = true;

         for( int j=0; j<9; j++ )
         {
            if( board[i][j][0] == 0 )
            {
               if( (board[i][j][k] != 0 && boxnum != -1) )
               {
                  if( (i/3)*3+j/3 != boxnum )
                  {
                     cont = false;
                     break;
                  }

               }
               else if( board[i][j][k] != 0 )
               {
                  boxnum = (i/3)*3+j/3;
               }
            }
            else if( board[i][j][0] == k )
            {
               cont = false;
               break;
            }
         }

         if( cont == true && boxnum != -1 )
         {
            //if pattern found remove all numbers k in this box besides the ones on this row
            x = (boxnum/3)*3;

            for( int l=x; l<x+3; l++ )
            {
               if( l==i )
                  l++;
               if( !(l<x+3) )
                  break;

               y = (boxnum%3)*3;

               for( int m=y; m<y+3; m++ )
               {
                  board[l][m][k] = 0;
               }
            }


         }
      }
   }

   //columns to boxes
   for( int j=0; j<9; j++ )
   {
      for( int k=1; k<10; k++ )
      {
         boxnum = -1;
         cont = true;

         for( int i=0; i<9; i++ )
         {
            if( board[i][j][0] == 0 )
            {
               if( (board[i][j][k] != 0 && boxnum != -1) )
               {
                  if( (i/3)*3+j/3 != boxnum )
                  {
                     cont = false;
                     break;
                  }

               }
               else if( board[i][j][k] != 0 )
               {
                  boxnum = (i/3)*3+j/3;
               }
            }
            else if( board[i][j][0] == k )
            {
               cont = false;
               break;
            }
         }

         if( cont == true && boxnum != -1 )
         {
            //if pattern found remove all numbers k in this box besides the ones on this row
            x = (boxnum%3)*3;

            for( int l=x; l<x+3; l++ )
            {
               if( l==j )
                  l++;
               if( !(l<x+3) )
                  break;

               y = (boxnum/3)*3;

               for( int m=y; m<y+3; m++ )
               {
                  board[m][l][k] = 0;
               }
            }
         }
      }
   }

   int rownum;

   //boxes to rows
   for( int m=0; m<9; m++ )
   {
      for( int k=1; k<10; k++ )
      {
         cont = true;
         rownum = -1;

         x = (m/3)*3;

         for( int i=x; i<x+3; i++ )
         {
            y = (m%3)*3;

            for( int j=y; j<y+3; j++ )
            {
               if( board[i][j][0] == 0 )
               {
                  if( board[i][j][k] != 0 && rownum != -1 )
                  {
                     if( i != rownum )
                     {
                        cont = false;
                        break;
                     }

                  }
                  else if( board[i][j][k] != 0 )
                  {
                     rownum = i;
                  }
               }
               else if( board[i][j][0] == k )
               {
                  cont = false;
                  break;
               }
            }

         }

         if( cont == true && rownum != -1 )
         {
            //if pattern found remove all numbers k in this row besides the ones in this box
            for( int l=0; l<9; l++ )
            {
               if( (rownum/3)*3+l/3 != m )
                  board[rownum][l][k] = 0;
            }
         }
      }
   }

   int colnum;

   //boxes to rows
   for( int m=0; m<9; m++ )
   {
      for( int k=1; k<10; k++ )
      {
         cont = true;
         colnum = -1;

         x = (m/3)*3;

         for( int i=x; i<x+3; i++ )
         {
            y = (m%3)*3;

            for( int j=y; j<y+3; j++ )
            {
               if( board[i][j][0] == 0 )
               {
                  if( board[i][j][k] != 0 && colnum != -1 )
                  {
                     if( j != colnum )
                     {
                        cont = false;
                        break;
                     }

                  }
                  else if( board[i][j][k] != 0 )
                  {
                     colnum = j;
                  }
               }
               else if( board[i][j][0] == k )
               {
                  cont = false;
                  break;
               }
            }

         }

         if( cont == true && colnum != -1 )
         {
            //if pattern found remove all numbers k in this column besides the ones in this box
            for( int l=0; l<9; l++ )
            {
               if( (l/3)*3+colnum/3 != m )
                  board[l][colnum][k] = 0;
            }
         }
      }
   }




}

bool end( int board[9][9][10] )
{
   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         if( board[i][j][0] == 0 )
            return true;
      }
   }

   return false;

}

void getsmall( int board[9][9][10], int &x, int &y )
{

   int ipos, jpos, counter;
   int largest = 9;

   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         counter = 9;

         for( int k=1; k<10; k++ )
         {
            if( board[i][j][0] == 0 )
               if( board[i][j][k] == 0 )
                  counter--;
         }

         if( counter < largest )
         {
            largest = counter;
            ipos = i;
            jpos = j;
         }
      }
   }

   x = ipos;
   y = jpos;
}

void makebackup( int backup[9][9][10], int board[9][9][10] )
{
   for( int i=0; i<9; i++ )
   {
      for( int j=0; j<9; j++ )
      {
         for( int k=0; k<10; k++ )
         {
            backup[i][j][k] = board[i][j][k];
         }
      }
   }
}
//manual creation of sudoku board
/*websudoku.com puzzle # 8 802 726 365
  board[0][3][0] = 6;
  board[0][7][0] = 3;
  board[1][0][0] = 6;
  board[1][1][0] = 4;
  board[1][7][0] = 1;
  board[1][8][0] = 8;
  board[2][2][0] = 3;
  board[2][3][0] = 1;
  board[2][7][0] = 2;
  board[3][0][0] = 8;
  board[3][4][0] = 7;
  board[3][6][0] = 3;
  board[4][3][0] = 2;
  board[4][5][0] = 9;
  board[5][2][0] = 4;
  board[5][4][0] = 3;
  board[5][8][0] = 9;
  board[6][1][0] = 3;
  board[6][5][0] = 2;
  board[6][6][0] = 5;
  board[7][0][0] = 2;
  board[7][1][0] = 1;
  board[7][7][0] = 8;
  board[7][8][0] = 4;
  board[8][1][0] = 9;
  board[8][5][0] = 5;
  board[8][5][0] = 5;
 */
