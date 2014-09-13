#include "Bignums.h"

Bignum::Bignum( int x )
{
   bool flag = true;

   while( flag == true )
   {
      if( x > 9 )
      {
         num.push_back( x % 10 );
         x = x/10;
      }
      else
      {
         num.push_back( x );
         flag = false;
      }

   }
}

Bignum::Bignum( const Bignum& b )
{
   int final = b.num.size();

   for( int i=0; i<final; i++ )
      num.push_back( b.num[i] );

}

Bignum& Bignum::operator=( const Bignum& b )
{
   if( this != &b )
   {
      int final = b.num.size();
      num.clear();

      for( int i=0; i<final; i++ )
         num.push_back( b.num[i] );
   }

   return *this;
}

const Bignum Bignum::operator+( const Bignum& b) const
{
   Bignum result = *this;

   int final;
   int sum=0;
   int ressize = result.num.size();
   int bsize = b.num.size();

   if( ressize < bsize )
      final = bsize;
   else
      final = ressize;

   for( int i=0; i<final; i++ )
   {
      if( i<ressize && i<bsize )
      {
         sum = result.num[i] + b.num[i] + sum;

         if( sum > 9 )
         {
            result.num[i] = (sum % 10);
            sum = sum/10;
         }
         else
         {
            result.num[i] = sum;
            sum = 0;
         }
      }
      else if( i<ressize )
      {
         sum = result.num[i] + sum;

         if( sum > 9 )
         {
            result.num[i] = (sum % 10);
            sum = sum/10;
         }
         else
         {
            result.num[i] = sum;
            sum = 0;
         }
      }
      else if( i<bsize )
      {
         sum = b.num[i] + sum;

         if( sum > 9 )
         {
            result.num.push_back( sum % 10 );
            sum = sum/10;
         }
         else
         {
            result.num.push_back( sum );
            sum = 0;
         }
      }
   }

   if( sum != 0 )
      result.num.push_back( sum );


   return result;
}

const Bignum Bignum::operator+( const int& x) const
{
   Bignum result = *this;

   int final;
   int sum=0;
   int b = x;
   int nextnum;
   int bsize=0;
   int ressize = result.num.size();

   
   while( b>0 )
   {
      b = b/10;
      bsize++;
   }

   b = x;

   if( ressize < bsize )
      final = bsize;
   else
      final = ressize;

   for( int i=0; i<final; i++ )
   {
      if( i<ressize && i<bsize )
      {
         nextnum = b % 10;
         b = b/10;

         sum = result.num[i] + nextnum + sum;

         if( sum > 9 )
         {
            result.num[i] = (sum % 10);
            sum = sum/10;
         }
         else
         {
            result.num[i] = sum;
            sum = 0;
         }
      }
      else if( i<ressize )
      {
         sum = result.num[i] + sum;

         if( sum > 9 )
         {
            result.num[i] = (sum % 10);
            sum = sum/10;
         }
         else
         {
            result.num[i] = sum;
            sum = 0;
         }
      }
      else if( i<bsize )
      {
         nextnum = b % 10;
         b = b/10;

         sum = nextnum + sum;

         if( sum > 9 )
         {
            result.num.push_back( sum % 10 );
            sum = sum/10;
         }
         else
         {
            result.num.push_back( sum );
            sum = 0;
         }
      }
   }

   if( sum != 0 )
      result.num.push_back( sum );


   return result;
}

int Bignum::size()
{
   int x = num.size();
   return x;
}

ostream& operator<<( ostream& o, const Bignum& b )
{
   int final = b.num.size()-1;

   for( int i=final; i>=0; i-- )
   {
      o<<b.num[i];
   }

   return o;
}
