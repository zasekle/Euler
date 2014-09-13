#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
   ifstream fin( "names" );
   string temps;
   vector<string> names;
   vector<int> sums;
   int i,j;

   //import from file
   for( i=0; fin.good(); i++ )
   {
      getline(fin, temps, ',');

      if( fin.good() )
         names.push_back( temps );

   }

  /* for( int i=0; i<names.size(); i++ )
      cout << names[i] << endl;*/

   //sort into alphabetical order
   for( i=1; i<names.size(); i++ )
   {
      temps = names[i];

      for( j=i-1; j>=0 && temps < names[j]; j-- )
        names[j+1] = names[j];

      names[j+1] = temps;
   }

   int sum=0;

   for( j=0; j<names.size(); j++ )
   {
      sum = 0;

      for( i=0; names[j][i] != NULL; i++ )
      {
         if( names[j][i] != '"' )
         {
            sum = sum + names[j][i] - 'A'+1;
         }

      }
      sums.push_back( sum ); 
   }

   sum = 0;

   for( i=0; i<sums.size(); i++ )
      sum = sum + (sums[i]*(i+1));

   cout << "Answer" << endl << sum << endl;

   fin.close();

   return 0;
}
