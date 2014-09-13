#include <iostream>
#include <vector>

using namespace std;

//factorial number use numbers greater than 2
const int fac = 100;

int main()
{
   //vector containing factorial
   vector<vector<int> > num;

   int carry, muldigit, store, facdigits, tempnum;

   facdigits = 2;
   tempnum = fac;

   while( tempnum > 0 )
   {
      tempnum = tempnum/10;
      facdigits++;
   }

   num.resize( facdigits ); 

   num[0].push_back( 1 );

   for( int i=2; i<fac+1; i++ )
   {
      store = i;
      carry = 0;
   
      //multiplier
      for(int k=1; store > 0; k++ )
      {
         muldigit = store % 10;
         store = store/10;
         num[k].clear();

         for( int j=1; j<k; j++ )
            num[k].push_back( 0 );

         for( int j=0; j<num[0].size(); j++ )
         {
            
            carry = (muldigit * num[0][j]) + carry;

            if( carry > 9 )
            {
               num[k].push_back( carry % 10 );
               carry = carry/10;
            }
            else
            {
               num[k].push_back( carry );
               carry = 0;
            }
            if( j+1 == num[0].size() && carry != 0 )
            {
               num[k].push_back( carry );
               carry = 0;
            }

         }

      }
      //clear first row of digits
      num[0].clear();

      //set first row equal to second row
      for( int j=0; j<num[1].size(); j++ )
         num[0].push_back( num[1][j] );

      //adder
      for( int j=2; !( num[j].empty() ); j++ )
      {

         for( int k=0; k<num[j].size(); k++ )
         {
            if( k>=num[0].size() )
            {
               if( carry != 0 )
               {
                  num[0].push_back( num[j][k]+carry );
                  carry = 0;
               }
               else
                  num[0].push_back( num[j][k] );

            }
            else
            {
               carry = num[0][k] + num[j][k]+ carry;
               //cout << endl << num[j+1][k] << '+' << num[j][k];

               if( carry > 9 )
               {
                  num[0][k] = carry % 10;
                  carry = carry/10;
               }
               else
               {
                  num[0][k] = carry;
                  carry = 0;
               }

            }

         }

         if( carry != 0 )
            num[0].push_back( carry );

      }
      if( num[0][num[0].size()-1] == 0 )
         num[0].pop_back();

   }

   cout << endl << fac << '!' << endl;
   store = num[0].size() % 3;

   if( store == 0 )
      store = 3;

   for( int j=num[0].size()-1; j>=0; j-- )
   {
      if( store == 0 )
      {
         cout << ',';
         store = 3;
      }

      cout << num[0][j];

      store--;
   }

   int answer=0;

   cout << endl << endl << "Sum of digits" << endl;

   for( int j=num[0].size()-1; j>=0; j-- )
      answer = answer + num[0][j];

   cout << answer << endl;

   return 0;
}
