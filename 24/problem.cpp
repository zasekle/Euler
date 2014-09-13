#include <iostream>

using namespace std;

//permutation number that you want to find
const int numfind = 1000000;

//number of digits in number
const int digits = 10;

long long fac( int );

int main()
{
   int find = numfind;
   find--;

   int num[digits];
   int answer[digits];
   int incre;

   for( int i=0; i<digits; i++ )
   {
      num[i] = i;
      answer[i] = i;
   }

   for( int i=digits-1; i>=0; i-- )
   {
      incre = find/fac(i);
      find = find % fac(i); 

      answer[digits-1-i] = num[incre];

      for( int j=incre+1; j<digits; j++ )
      {
         num[j-1] = num[j];
         num[j-1] = num[j];
      }

   }

   cout << "Answer" << endl;

   for( int i=0; i<digits; i++ )
      cout << answer[i];

   cout << endl;


   return 0;
}

long long fac( int x )
{
   long long answer=1;

   while( x>0 )
   {
      answer = answer*x;
      x--;
   }

   return answer;

}
