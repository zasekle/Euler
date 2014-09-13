#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
   vector<long long> penta;
   bool end = false;
   bool sum, diff;
   int answer = 2146483647;
   long long tempsum, tempdiff, none;
   float floatsum, floatdiff;

   //push first pentagon # in vector
   penta.push_back( 1 );

   //set each penta number
   for( int x=2; end==false; x++ )
   {
      if( x % 1000 == 0 )
         cout << "x=" << x << endl;

      //add pentagon #s to vector
      penta.push_back((x*(3*x-1))/2);

      //check each number against every other number
      for( int y=0; y<x; y++ )
      {
         sum = false;
         diff = false;

         tempsum = penta[y]+penta[x-1];
         tempdiff = penta[x-1]-penta[y];

         floatsum = (sqrt( 24*tempsum+1)+1)/6;
         none = floatsum;

         if( floatsum - none == 0 )
            sum = true;

         floatdiff = (sqrt( 24*tempdiff+1)+1)/6;
         none = floatdiff;

         if( floatdiff - none == 0 )
            diff = true;

         if( sum == true && diff == true && diff < answer )
         {
            answer = tempdiff;
            cout << answer << " y=" << y << " x=" << x << endl;
         }

      }

      //end condition
      if( penta[x-1]-penta[x-2] > answer )
         end = true;

   }

   cout << answer << endl;

   return 0;
}

/*
   long long x,y,z;
   float algebra;
   int dummy, counter =0;
   vector<long long > penta;


   for( int i=1; i<10000; i++ )
      penta.push_back( (i*(3*i-1))/2 );

   for( int i=0; i<penta.size(); i++ )
      if( penta[i] < 0 )
      {
         cout << i;
         break;
      }
   for( int i=0; i<penta.size(); i++ )
   {
      for( int j=(i+1); j<penta.size(); j++ )
      {
         algebra = ( 1+sqrt(1+24*( penta[j]+penta[i] ) ) )/6.0;
         dummy = algebra;
         algebra = algebra - dummy;

         if( algebra == 0.0 ) 
         {
            //cout << i << '=' << penta[i] << ' ' << j << '=' << penta[j] << " | " << dummy << ' ' << algebra << endl;
            
            algebra = ( 1+sqrt(1+24*( abs(penta[j]-penta[i]) ) ) )/6;
            dummy = algebra;
            algebra = algebra - dummy;

            if( algebra == 0.0 )
               cout << penta[i] << ',' << penta[j] << endl;
            else
            {
               algebra = ( 1-sqrt(1+24*( abs(penta[j]-penta[i]) ) ) )/6;
               dummy = algebra;
               algebra = algebra - dummy;

               if( dummy >= 0 && algebra == 0.0 )
            }
         }
         else
         {
            algebra = ( 1-sqrt(1+24*( penta[j]+penta[i] ) ) )/6.0;
            dummy = algebra;
            algebra = algebra - dummy;

            if( dummy >= 0 && algebra == 0.0 ) 
            {
               //cout << i << '=' << penta[i] << ' ' << j << '=' << penta[j] << " | " << dummy << ' ' << algebra << endl;

               algebra = ( 1+sqrt(1+24*( abs(penta[j]-penta[i]) ) ) )/6;
               dummy = algebra;
               algebra = algebra - dummy;

               if( algebra == 0.0 )
                  cout << penta[i] << ',' << penta[j] << endl;
               else
               {
                  algebra = ( 1-sqrt(1+24*( abs(penta[j]-penta[i]) ) ) )/6;
                  dummy = algebra;
                  algebra = algebra - dummy;

                  if( dummy >= 0 && algebra == 0.0 )
                     cout << penta[i] << ',' << penta[j] << endl;
               }
            }
         }
      }
   }*/
