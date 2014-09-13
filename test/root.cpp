#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

int limit = 1e5;

vector<vector<int> > rootv;

int main()
{
   int x;
   long long power;
   vector<int> temp;

   //high_resolution_clock::time_point t1 = high_resolution_clock::now();

   //start at ^4 and go to 
   for( int j=4; true; j++ )
   {
      power = pow( 2, j );

      if( power > limit )
         break;

      for( int i=3; power<=limit; i++ )
      {
         temp.push_back( power );
         power = pow( i, j );
      }

      temp.push_back( limit+1 );

      rootv.push_back( temp );

      temp.clear();
   }


   /*for( int i=0; i<rootv.size(); ++i )
     {
     for( int j=0; j<rootv[i].size(); ++j )
     cout << j+2 << '^' << i+4 << '=' << rootv[i][j] << ' ';

     cout << endl;
     }*/


   //want to find x^(1/y)
   //exponent is rootv[y-4]
   x;
   int y;
   int answer;

   while( true )
   {
      cout << "Enter a number below " << limit << endl;
      cin >> x;
      cout << "Enter a y for ^1/y" << endl;
      cin >> y;

      if( y-4 > rootv.size() )
         answer = 1;
      else
         for( int i=0; true; i++ )
            if( rootv[y-4][i]>x ) 
            {
               answer = i+1;
               break;
            }


      //high_resolution_clock::time_point t2 = high_resolution_clock::now();

      //duration<double> time_span = duration_cast<duration<double>> (t2-t1);

      //cout << "seconds" << endl << time_span.count() << endl; 

      cout << endl << x << "^(1/" << y << ')' << '=' << answer << endl;

   }
   return 0;
}
