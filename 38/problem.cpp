#include <iostream>

using namespace std;

int main()
{
   bool nine[9];
   bool cont;
   int numholder, final=0;

   //there are reason for these limits on i
   for( int i=9202; i<9501; i++ )
   {
      numholder = i;
      cont = true;

      for( int j=0; j<9; j++ )
         nine[j] = false;

      for( int j=0; j<2; j++ )
      {
         if( numholder % 10 == 0 || numholder % 10 == 5 || numholder % 10 == 8 || (numholder % 10 == 1 && j == 0) )
            cont == false;
      }

      for( int j=0; j<4; j++ )
      {
         nine[(numholder%10)-1] = true;
         numholder = numholder / 10;
      }

      numholder = i*2;

      for( int j=0; j<5; j++ )
      {
         nine[(numholder%10)-1] = true;
         numholder = numholder / 10;
      }

      for( int j=0; j<9; j++ )
         if( nine[j] == false )
            cont = false;

      if( cont == true && i>final )
         final = i;

   }

   cout << final << final*2 << endl;

   return 0;
}

