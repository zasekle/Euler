#include <iostream>
#include <stack>

using namespace std;

long long fakefac( long long );

int multi( int );

int main()
{
   cout << fakefac( 261800 ) << endl;

   cout << multi( 261800 ) << endl;

   return 0;
}

long long fakefac( long long x )
{
   while( x > 1 )
      return (2+fakefac(x-1));


   return 2;
   
}

int multi( int x )
{
   stack<int> sta;

   while( x>1 )
   {
      sta.push( 2 );
      x--;

   }

   x=2;

   while( !sta.empty() )
   {
      x=x+sta.top();
      sta.pop();
   }

   return x;

}
