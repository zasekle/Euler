#include <iostream>
#include <vector>

using namespace std;

int main()
{
   vector<vector<int> > nums;
   vector<int> temp;
   vector<vector<int> > possib;
   bool exists;

   for( int i=10; i<100; i++ )
   {
      for( int j=10; j<100; j++ )
      {
         if( (i % 10 == j/10 || (i % 10 == j % 10 && i % 10 != 0) || i/10 == j/10) && j != i )
         {
            if( i<j )
            {
               temp.clear();
               temp.push_back( i );
               temp.push_back( j );
            }
            else
            {
               temp.clear();
               temp.push_back( j );
               temp.push_back( i );
            }

            exists = false;
            for( int k=0; k<possib.size(); k++ )
               if( temp == possib[k] )
                  exists = true;
            
            if( exists == false )
               possib.push_back( temp );
         }
      }
   }

   double numer;
   double denom;
   double divi;
   
   nums.clear();
   temp.clear();

   for( int i=0; i<possib.size(); i++ )
   {
      numer = possib[i][0];
      denom = possib[i][1];


      if( possib[i][0] % 10 == possib[i][1] % 10 )
      {
         divi = numer/denom;
         numer = possib[i][0]/10;
         denom = possib[i][1]/10;

         if( numer/denom == divi )
         {
            temp.clear();
            temp.push_back( possib[i][0] );
            temp.push_back( possib[i][1] );
            nums.push_back( temp );
         }

      }
      else if( possib[i][0]/10 == possib[i][1] % 10 )
      {

         divi = numer/denom;
         numer = possib[i][0] % 10;
         denom = possib[i][1]/10;

         if( numer/denom == divi )
         {
            temp.clear();
            temp.push_back( possib[i][0] );
            temp.push_back( possib[i][1] );
            nums.push_back( temp );
         }

      }
      else if( possib[i][0] % 10 == possib[i][1]/10 )
      {
         divi = numer/denom;
         numer = possib[i][0]/10;
         denom = possib[i][1] % 10;

         if( numer/denom == divi )
         {
            temp.clear();
            temp.push_back( possib[i][0] );
            temp.push_back( possib[i][1] );
            nums.push_back( temp );
         }

      }
      else if( possib[i][0]/10 == possib[i][1]/10 )
      { 

         divi = numer/denom;
         numer = possib[i][0] % 10;
         denom = possib[i][1] % 10;

         if( numer/denom == divi )
         {
            temp.clear();
            temp.push_back( possib[i][0] );
            temp.push_back( possib[i][1] );
            nums.push_back( temp );
         }

      }

   }

   cout << "Fractions that fit" << endl;

   for( int i=0; i<nums.size(); i++ )
      cout << i << ": " << nums[i][0] << ',' << nums[i][1] << endl;



   return 0;
}
