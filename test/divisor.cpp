#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int tonum = 61;

//the number to find the multiples of
const int findnum = 60;

vector<int> primes;   
vector<vector<int> > divisors( tonum );

void factors( int, vector<vector<int> >&, vector<int>, int=0, int=2 );

bool isprime( int x );

int main()
{
   int size = sqrt( tonum);
   //prime number stuff
   int nums[tonum];

   primes.push_back( 2 );

   for( int i=0; i<tonum; i++ )
      nums[i] = 1;

   for( int i=2; i<size; i++ )
      for( int j=2; j*i<tonum; j++ )
         nums[i*j] = 0;

   for( int i=2; i<tonum; i++ )
      if( nums[i] == 1 )
         primes.push_back( i );

/*   for( int i=0; i<primes.size(); i++ )
     cout << primes[i] << ' ';
*/
   //gets divisors
   for( int i=2; i<tonum; i++ )
   {
      size = sqrt( i );

      //divisors[i].push_back( i );
      //divisors[i].push_back( 1 );

      for( int j=i; j*i<tonum; j++ )
      {
         if( j != i )
         {
            divisors[i*j].push_back( i );
            divisors[i*j].push_back( j );
         }
         else
            divisors[i*j].push_back( j );

      }

   }

   for( int i=0; i<divisors.size(); i++ )
      sort( divisors[i].begin(), divisors[i].end() );

   //shows divisors
   
      for( int i=1; i<divisors.size(); i++ )
      {
      cout << i << ": ";

      for( int j=0; j<divisors[i].size(); j++ )
      {
      cout << divisors[i][j] << ',';
      }
      cout << endl;
      }

   vector<vector<int> > mynum;
   vector<int> newv;

   //the ending statement for this is inefficient is has to run the function an extra time
   //however this way I can avoid storing prime numbers to check and see if the final array is
   //all prime
   for( int i=2; ; i++ )
   {
      size = mynum.size();
      factors( findnum, mynum, newv, 0, i );

      if( size == mynum.size() )
         break;
   }

   cout << "Combinations of divisors of " << findnum << endl;

   for( int i=0; i<mynum.size(); i++ )
   {
      cout << i+1 << ": ";

      for( int j=0; j<mynum[i].size(); j++ )
      {
         if( j!=0 )
            cout << ',' << mynum[i][j];
         else
            cout << mynum[i][j];
      }

      cout << endl;
   }

   return 0;
}

void factors( int x, vector<vector<int> > &mynum, vector<int> prev, int min, int div )
{

   vector<int> tempv;
   double denom = div;
   double root = 1/denom;
   int size = pow( x, root );
   int temp;
   int newn;
   int i;

   for( i=0; i<divisors[x].size() && divisors[x][i]<=size; i++ )
   {
      if( min <= divisors[x][i] && div==2 )
      {
         temp = divisors[x][i];
         newn = x/temp;

         tempv.clear();

         for( int j=0; j<prev.size(); j++ )
            tempv.push_back( prev[j] );

         tempv.push_back( temp );
         tempv.push_back( newn );

         mynum.push_back( tempv );
      }
      else if( min<=divisors[x][i] && div>2 )
      {
         temp = divisors[x][i];
         newn = x/temp;

         prev.push_back( temp );

         factors( newn, mynum, prev, temp, div-1 );

         prev.pop_back();
      }
   }
}

bool isprime( int x )
{

   for( int i=0; i<primes.size(); i++ )
      if( primes[i] == x )
         return true;

   return false;

}

/*   tempv.push_back( 1 );
     vector<int> nvec;
     tempv.push_back( findnum );

     mynum.push_back( tempv );

     size = ceil( pow( findnum, 1/2. ) );

//2 multiplies
for( int i=0; i<divisors[findnum].size() && divisors[findnum][i]<size; i++ )
{
tempv.clear();

tempv.push_back( divisors[findnum][i] );
tempv.push_back( findnum/divisors[findnum][i] );

if( findnum ==  findnum/divisors[findnum][i] * divisors[findnum][i] )
mynum.push_back( tempv );

}

size = ceil( pow( findnum, 1/3. ) );

//3 multiplies
for( int i=0; i<divisors[findnum].size() && divisors[findnum][i]<size; i++ )
{
for( int j=i; j<divisors[findnum].size() && divisors[findnum][j]<=size; j++ )
{
tempv.clear();

tempv.push_back( divisors[findnum][i] );
tempv.push_back( divisors[findnum][j] );
tempv.push_back( findnum/(divisors[findnum][i]*divisors[findnum][j]) );

if( findnum == ( findnum/(divisors[findnum][i]*divisors[findnum][j]) * divisors[findnum][i]*divisors[findnum][j] ) )
mynum.push_back( tempv );

}
}

size = ceil( pow( findnum, 1/4. ) );

//4 multiplies
for( int i=0; i<divisors[findnum].size() && divisors[findnum][i]<size; i++ )
{
for( int j=i; j<divisors[findnum].size() && divisors[findnum][j]<=size; j++ )
{
for( int k=j; k<divisors[findnum].size() && divisors[findnum][k]<=size; k++ )
{
tempv.clear();

//cout << "i:" << i << " j:" << j << " k:" << k << endl;
//cout << "~i:" << divisors[findnum][i] << " j:" << divisors[findnum][j] << " k:" << divisors[findnum][k] << endl;
if( findnum == ( findnum/(divisors[findnum][i]*divisors[findnum][j]*divisors[findnum][k]) * divisors[findnum][i]*divisors[findnum][j]*divisors[findnum][k])
&& findnum/(divisors[findnum][i]*divisors[findnum][j]*divisors[findnum][k]) > divisors[findnum][k] )
{
tempv.push_back( divisors[findnum][i] );
tempv.push_back( divisors[findnum][j] );
tempv.push_back( divisors[findnum][k] );
{
tempv.push_back( findnum/(divisors[findnum][i]*divisors[findnum][j]*divisors[findnum][k]) );

mynum.push_back( tempv );
}
}
}
}
}
cout << "Combinations of divisors of " << findnum << endl;

  for( int i=0; i<mynum.size(); i++ )
  {
  cout << i+1 << ": ";

  for( int j=0; j<mynum[i].size(); j++ )
  {
  cout << mynum[i][j] << ',';

  }
  cout << endl;
  }
  newv.push_back( 2 );
  newv.push_back( 3 );
  newv.push_back( 2 );
  newv.push_back( 5 );


  for( int i=0; i<newv.size()-1; i++ )
  {
  for( int j=i+1; j<newv.size(); j++ )
  {
  tempv.clear();

  tempv.push_back( newv[i]*newv[j] );

  for( int k=0; k<newv.size(); k++ )
  {
  if( k != j && k != i )
  tempv.push_back( newv[k] );
  }

  mynum.push_back( tempv );

  }
  }
  if( mynum[k][2] % mynum[i][0] == 0 )
  {
  if( i==0 && j == 0 && k == 1 )
  cout << mynum[k][2]/mynum[i][0] << ' ' << mynum[k-1][1];

  if( k>0 && mynum[k][2]/mynum[i][0]>mynum[k-1][1] )
  {
  tempv.clear();

  tempv.push_back( mynum[i][0] );
  tempv.push_back( mynum[i][0] );
  tempv.push_back( mynum[j][1] );
  tempv.push_back( mynum[k][2]/mynum[i][0] );

  mynum.push_back( tempv );
  }

  else if( k>0 )
  break;
  }

//3 multiples
for( int i=0; i<size; i++ )
{
for( int j=i; j<size; j++ )
{
if( mynum[j][1] % mynum[i][0] == 0 )
{
if( ( j>0 && mynum[j][1]/mynum[i][0]>mynum[j-1][0] ) || ( j==0 && mynum[j][1]/mynum[i][0]>mynum[j][0] ) )
{
tempv.clear();

tempv.push_back( mynum[i][0] );
tempv.push_back( mynum[j][0] );
tempv.push_back( mynum[j][1]/mynum[i][0] );

mynum.push_back( tempv );
}
else if( j>0 )
break;

}
}
}
 

   int cursor=0;
   bool copy = true;
   bool cont = false;
   int newi;
   int move=0;
   size = mynum.size()-1;
   for( int i=0; i< mynum[size].size(); i++ )
      if( !(isprime(mynum[size][i])) )
      {
         cont = true;
         break;
      }

   size = 0;

   while( cont == true )
   {
      start = size;

      size = mynum.size();

      for( int i=start; i<size; )
      {
         //for( int j=0; j<mynum[i].size()-1; j++ )
         {
            for( int k=i; k<size; k++ )
            {
               if( mynum[k].back() % mynum[i][0] == 0 )
               {
                  if( mynum[k].back()/mynum[i][0] >= mynum[k][mynum[k].size()-2] )// ||
                     //( k==start && mynum[k].back()/mynum[i][j] > mynum[k][mynum[k].size()-2] ) )
                  {
                     copy = true;

                     /for( int l=0; l<j; l++ )
                       if( mynum[i][l] == mynum[i][j] )
                       copy = false;/

                     if( copy == true )
                     {
                        //cout << "i,j:" << i << ',' << j << " k:" << k << endl;

                        tempv.clear();

                        for( int l=0; l<mynum[k].size()-1; l++ )
                           tempv.push_back( mynum[k][l] );

                        tempv.push_back( mynum[k].back()/mynum[i][0] );
                        tempv.push_back( mynum[i][0] );

                        sort( tempv.begin(), tempv.end() );

                        mynum.push_back( tempv );
                     }
                  }
                  else
                     break;
               }
            }
         }
         i++;

         while( i<size && mynum[i][0] == mynum[i-1][0] )
            i++;
      }
      cont = false;
      cursor = mynum.size()-1;

      for( int i=0; i<mynum[cursor].size(); i++ )
      {
         if( !(isprime( mynum[cursor][i] )) )
         {
            cont = true;
            break;
         }
      }
   }
   for( int i=1; i<newv.size(); i++ )
     {
     tempv.clear();

     tempv.push_back( newv[i]*newv[i-1] );

     for( int j=0; j<newv.size(); j++ )
     if( j != i && j != i-1 )
     tempv.push_back( newv[j] );

     while( newv[i+1] == newv[i] && i<(newv.size()-1) )
     i++;

     mynum.push_back( tempv );
     }*/
