#include <iostream>
#include <cstring>

using namespace std;

int mylen( char word[120] );

int main()
{
   char word[120];
   int x=12, final=0;

   for( int i=0; i<1001; i++ )
   {
      word[0] = '\0';
      x=i;

      if( x == 1000 )
         strcat( word, "one thousand" );

      else if( x>99 && x<1000 )
      {
         //nine hundred
         if( x<1000 && x>899 )
            strcat( word, "nine hundred " );
         //eight hundred
         else if( x<900 && x>799 )
            strcat( word, "eight hundred " );
         //seven hundred
         else if( x<800 && x>699 )
            strcat( word, "seven hundred " );
         //six hundred
         else if( x<700 && x>599 )
            strcat( word, "six hundred " );
         //five hundred
         else if( x<600 && x>499 )
            strcat( word, "five hundred " );
         //four hundred
         else if( x<500 && x>399 )
            strcat( word, "four hundred " );
         //three hundred
         else if( x<400 && x>299 )
            strcat( word, "three hundred " );
         //two hundred
         else if( x<300 && x>199 )
            strcat( word, "two hundred " );
         //one hundred
         else if( x<200 && x>99 )
            strcat( word, "one hundred " );

         x = x % 100;

         if( x % 100 != 0 )
            strcat( word, "and " );
      }
      
      if( x<100 && x>0 )
      {
         //ninety
         if( x<100 && x>89 )
            strcat( word, "ninety " );
         //eighty
         else if( x<90 && x>79 )
            strcat( word, "eighty " );
         //seventy
         else if( x<80 && x>69 )
            strcat( word, "seventy " );
         //sixty
         else if( x<70 && x>59 )
            strcat( word, "sixty " );
         //fifty
         else if( x<60 && x>49 )
            strcat( word, "fifty " );
         //forty
         else if( x<50 && x>39 )
            strcat( word, "forty " );
         //thirty
         else if( x<40 && x>29 )
            strcat( word, "thirty " );
         //twenty
         else if( x<30 && x>19 )
            strcat( word, "twenty " );
         //teens
         else if( x<20 && x>9 )
         {
            //nineteen
            if( x==19 )
               strcat( word, "nineteen" );
            //eighteen
            if( x==18 )
               strcat( word, "eighteen" );
            //seventeen
            if( x==17 )
               strcat( word, "seventeen" );
            //sixteen
            if( x==16 )
               strcat( word, "sixteen" );
            //fifteen
            if( x==15 )
               strcat( word, "fifteen" );
            //fourteen
            if( x==14 )
               strcat( word, "fourteen" );
            //thirteen
            if( x==13 )
               strcat( word, "thirteen" );
            //twelve
            if( x==12 )
               strcat( word, "twelve" );
            //eleven
            if( x==11 )
               strcat( word, "eleven" );
            //ten
            if( x==10 )
               strcat( word, "ten" );

            x=0;
         }

         x = x % 10;
      }

      if( x<10 && x>0 )
      {
         //nine
         if( x==9 )
            strcat( word, "nine" );
         //eight
         if( x==8 )
            strcat( word, "eight" );
         //seven
         if( x==7 )
            strcat( word, "seven" );
         //six
         if( x==6 )
            strcat( word, "six" );
         //five
         if( x==5 )
            strcat( word, "five" );
         //four
         if( x==4 )
            strcat( word, "four" );
         //three
         if( x==3 )
            strcat( word, "three" );
         //two
         if( x==2 )
            strcat( word, "two" );
         //one
         if( x==1 )
            strcat( word, "one" );

      }

      final = final + mylen(word);
   }

   cout << "final" << endl << final << endl;
   return 0;
}

int mylen( char word[120] )
{
   int x=0;

   for( int i=0; word[i] != '\0'; i++ )
   {
      if( word[i] != ' ' )
         x++;
   }

   return x;
}
