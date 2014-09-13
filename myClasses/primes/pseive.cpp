#include "pseive.h"

pseive::pseive( int x )
{

   if( x<=100000*64 )
   {
      blocksize=ceil(x/64.0);
      blockcount = 1;
   }
   else
   {
      blocksize=100000;
      blockcount=ceil(x/64.0/blocksize);
   }

   array= new unsigned*[blockcount];

   for( int i=0; i<blockcount; i++ )
   {
      array[i] = NULL;
      array[i] = new (std::nothrow) unsigned[blocksize];

      if( array[i] == NULL )
      {
         cout << "Unable to allocate memory past " << i * blocksize << endl;
         for( int j = 0; j<i; ++j )
            delete array[j];
         delete array;
         break;
      }

   }

   for( int i=0; i<blockcount; i++ )
      for( int j=0; j<blocksize; j++ )
         array[i][j]=0;

   int size = sqrt( x );

   setbit( 1 );

   for( int i=2; i<=size; i++ )
   {
      if( !getbit( i ) )
         for( int j=2*i; j<=x; j+=i )
            if( j%2==1 )
               setbit( j );
   }
}

pseive::~pseive()
{
   for( int j=0; j<blockcount; j++ )
      delete array[j];

   delete array;
}

void pseive::setbit( int x )
{
   unsigned mask = 1;
   int bit = ((x/2)%32)+1;
   int rows = x/(blocksize*64);
   int columns = (x-rows*blocksize*64)/64;

   mask <<= bit;

   array[rows][columns] |= mask;

}

bool pseive::getbit( int x )
{
   if( x == 2 )
      return false;
   if( x % 2 == 0 )
      return true;

   unsigned mask = 1;
   int bit = ((x/2)%32)+1;
   int rows = x/(blocksize*64);
   int columns = (x-rows*blocksize*64)/64;

   mask <<= bit;

   mask &= array[rows][columns];

   return( mask != 0 );

}
