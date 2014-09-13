#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//the coins value can be 1, 2, 5, 10, 20, 50, 100, or 200
const int coin = 200;

//searches for 2 1's if it finds them it removes them and adds a 2
void combtwo( vector<int>& );

//saves the vector to the double array vector
void save( vector<int>, vector<int>, vector<vector<int> > &);

int main()
{
   vector<int> combo;
   vector<int> extra;
   vector<vector<int> > final;
   int counter = 1;
   int size = coin;
   int blank;
   int type = 0;
   int cointype;

   for( int i=0; i<coin; i++ )
      combo.push_back( 1 );

   save( combo, extra, final );

   for( int twohund=1; !combo.empty(); twohund++ )
   {
      for( int hund=1; !combo.empty(); hund++ )
      {
         for( int fifties=1; !combo.empty(); fifties++ )
         {
            for( int twenties=1; !combo.empty(); twenties++ )
            {
               for( int tens=1; !combo.empty(); tens++ )
               {
                  for( int fives=1; !combo.empty(); fives++ )
                  {
                     while( combo.size() > 1 && combo[0] != 2 && combo[1] != 2 )
                     {
                        //1 and 2 loop
                        combtwo( combo );

                        counter++;
                        save( combo, extra, final );
                     }
                     //5 loop
                     combo.clear(); 

                     for( int i=0; i<coin-(5*fives)-(10*(tens-1))-(20*(twenties-1))-(50*(fifties-1))-(100*(hund-1))-(200*(twohund-1)); i++ )
                        combo.push_back( 1 );

                     extra.clear();

                     for( int i=0; i<fives; i++ )
                        extra.push_back( 5 );

                     for( int i=0; i<(tens-1); i++ )
                        extra.push_back( 10 );

                     for( int i=0; i<(twenties-1); i++ )
                        extra.push_back( 20 );

                     for( int i=0; i<(fifties-1); i++ )
                        extra.push_back( 50 );

                     for( int i=0; i<(hund-1); i++ )
                        extra.push_back( 100 );

                     for( int i=0; i<(twohund-1); i++ )
                        extra.push_back( 200 );

                     if( coin >= 5 )
                        save( combo, extra, final );

                  }
                  //10 loop
                  combo.clear();

                  for( int i=0; i<coin-(10*tens)-(20*(twenties-1))-(50*(fifties-1))-(100*(hund-1))-(200*(twohund-1)); i++ )
                     combo.push_back( 1 );

                  extra.clear();

                  for( int i=0; i<tens; i++ )
                     extra.push_back( 10 );

                  for( int i=0; i<(twenties-1); i++ )
                     extra.push_back( 20 );

                  for( int i=0; i<(fifties-1); i++ )
                     extra.push_back( 50 );

                  for( int i=0; i<(hund-1); i++ )
                     extra.push_back( 100 );

                  for( int i=0; i<(twohund-1); i++ )
                     extra.push_back( 200 );


                  if( coin >= 10 )
                     save( combo, extra, final );

               }
               //20 loop
               combo.clear();

               for( int i=0; i<coin-(20*twenties)-(50*(fifties-1))-(100*(hund-1))-(200*(twohund-1)); i++ )
                  combo.push_back( 1 );

               extra.clear();

               for( int i=0; i<twenties; i++ )
                  extra.push_back( 20 );

               for( int i=0; i<(fifties-1); i++ )
                  extra.push_back( 50 );

               for( int i=0; i<(hund-1); i++ )
                  extra.push_back( 100 );

               for( int i=0; i<(twohund-1); i++ )
                  extra.push_back( 200 );

               if( coin >= 20 )
                  save( combo, extra, final );

            }
            //50 loop
            combo.clear();

            for( int i=0; i<coin-(50*fifties)-(100*(hund-1))-(200*(twohund-1)); i++ )
               combo.push_back( 1 );

            extra.clear();

            for( int i=0; i<fifties; i++ )
               extra.push_back( 50 );

            for( int i=0; i<(hund-1); i++ )
               extra.push_back( 100 );

            for( int i=0; i<(twohund-1); i++ )
               extra.push_back( 200 );

            if( coin >= 50 )
               save( combo, extra, final );
         }
         //100 loop
         combo.clear();

         for( int i=0; i<coin-(100*hund)-(200*(twohund-1)); i++ )
            combo.push_back( 1 );

         extra.clear();

         for( int i=0; i<hund; i++ )
            extra.push_back( 100 );

         for( int i=0; i<(twohund-1); i++ )
            extra.push_back( 200 );

         if( coin >= 100 )
            save( combo, extra, final );
      }

      //200 loop
      combo.clear();

      for( int i=0; i<coin-(200*twohund); i++ )
         combo.push_back( 1 );

      extra.clear();

      for( int i=0; i<twohund; i++ )
         extra.push_back( 200 );

      if( coin >= 200 )
         save( combo, extra, final );
   }
   
   /*
   for( int i=0; i<final.size(); i++ )
   {
      cout << i+1 << ": ";
      for( int j=0; j<final[i].size(); j++ )
      {
         if( j != 0 )
            cout << ',' << final[i][j];
         else
            cout << final[i][j];
      }
      cout << endl;
   }*/

   cout << endl << "Answer" << endl << final.size() << endl;

   return 0;
}

void combtwo( vector<int> &v )
{
   int pos[2]={-1,-1};
   bool found = false;

   for( int i=0; i<v.size(); i++ )
   {
      if( v[i] == 1 )
      {
         if( pos[0] == -1 )
            pos[0] = i;
         else if( pos[1] == -1 )
         {
            pos[1] = i;
            found = true;
            break;
         }
      }
   }

   if( found == true )
   {
      sort( pos, pos+1 );
      v.erase(v.begin() + pos[0]);
      v.erase(v.begin() + pos[1]-1);
      v.push_back( 2 );
   }  

}

void save( vector<int> v, vector<int> e, vector<vector<int> > &comb )
{
   vector<int> temp;

   for( int i=0; i<e.size(); i++ )
      temp.push_back( e[i] );

   for( int i=0; i<v.size(); i++ )
      temp.push_back( v[i] );

   //sorts in reverse order
   sort( temp.rbegin(), temp.rend() );

   int sum=0;

   for( int i=0; i<temp.size(); i++ )
      sum += temp[i];

   if( sum == coin )
      comb.push_back( temp );

}

