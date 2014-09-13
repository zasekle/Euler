#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
   float a;
   int dummy;
   vector<long long > pre;

   pre.push_back( 5 );
   pre.push_back( 35 );

   a = ( 1+sqrt(1+24*(pre[0]+pre[1]) ) )/6.0;
   dummy = a;

   cout << a << ' ' << dummy << endl;

   return 0;
}
