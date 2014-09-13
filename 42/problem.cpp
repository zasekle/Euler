#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int > trianums;

int charval( const char );

bool istriannum( string );

int getwordval( string );

int main()
{
   char word[99] = "SKYS";
   ifstream fin( "words.txt" );
   int finalval = 0;

   for( int i=1; (i*(i+1))/2 < 26*30; i++ )
     trianums.push_back( (i*(i+1))/2 ); 

   while ( fin.good() )
   {
      fin.getline( word, 99, ',' );

      if( istriannum( word ) == true )
         finalval++;

   }

   cout << "Answer = " << finalval << endl;
}

bool istriannum( string word )
{
   int wordval = getwordval( word );

   for( int i=0; i<trianums.size(); i++ )
      if( wordval == trianums[i] )
         return true;

   
   return false;

}

int getwordval( string word )
{
   int wordval = 0;

   for( int i=0; word[i] != '\0'; i++ )
      wordval += charval( word[i] );

   return wordval;
}

int charval( const char x )
{
   if( x != '"' )
      return (x - '0' - 16);

   return 0;
}
