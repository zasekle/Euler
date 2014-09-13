#include <iostream>

using namespace std;

//decimal precision
const int precision=2000;

//check to this number
const int check=1000;

int main()
{
   int nums[precision];
   int forward;
   int setjto;
   int diff;
   bool repeat = false;
   bool cont = true;
   bool shown = false;
   int saved=0;
   int answer=0;

   for( int i=0; i<check; i++ )
   {
      forward = 10;
      setjto=0;
      while( i>=forward )
      {
         forward = forward*10;
         setjto++;
      }
      //run 1/(i+1) long division form
      for( int j=setjto; j<precision; j++ )
      {
         if( forward == 0 )
         {
            nums[j] = -1;
            j=precision-1;
         }
         else
         {
            nums[j] = forward/(i+1);
            forward = (forward % (i+1)) * 10;
         }
      }

      repeat = false;
      cont = true;
      shown = false;

      for( int j=0; j<(precision-1); j++ )
      {
         //check to see if decimal ends
         if( nums[j+1] == -1 )
            j=precision-1;

         for( int k=j+1; k<precision; k++ )
         {
            if( nums[j] == nums[k] )
            {
               diff=k-j;
               
               //check for .3333333...
               if( diff == 1 && k<precision-10 )
               {
                  cont = false;
                  for( int l=k; l<(k+10); l++ ) 
                     if( nums[l] != nums[j] )
                        cont = true;

                  if( cont == false )
                        j=precision-1;

               }
               //check for a repeat
               if( cont == true && diff>1 )
               {
                  repeat = true;
                  for( int l=j; l<k; l++ )
                  {
                     //if( i >= precision || j >= precision || k+(l-j) >= precision || l >= precision )
                        //cout << "i:" << i << " j:" << j << " k+(l-j):" << k+(l-j) << " l:" << l << " k:" << k <<  endl;

                     if( k+l-j < precision )
                     {
                        if( nums[l] != nums[k+l-j] )
                        {
                           repeat = false;
                           break;
                        }
                     }
                     else
                     {
                        repeat = false;
                        break;
                     }
                  }

                  if( repeat == true )
                     j=precision-1;

               }
               if( repeat == true && diff > saved )
               {
                  /*if( shown == false )
                  {
                     cout << i+1 << ' ' << diff << endl;
                     shown = true;
                  }*/

                  saved = diff;
                  answer = i+1;
               }
            }
         }
      }
   }

   cout << "Answer" << endl << answer << " has a repeat " << saved << " digits long" <<  endl;

   return 0;
}
