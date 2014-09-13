#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
   int div = 6;
   int base = 15625;
   float denom = div;
   float f=125,s=1/denom;
   div = pow( base, s );

   cout << "float:" << setprecision(13) << div << endl << "float:" << setprecision(26) << pow( f, s ) << endl;



   return 0;
}
