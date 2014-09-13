#ifndef PSEIV_H
#define PSEIV_H

#include <new>
#include <iostream>
#include <cmath>

using namespace std;

class pseive{

   public:
      pseive( int );
      ~pseive();
      void setbit( int );
      //0 is prime false is prime
      bool getbit( int );

   protected:
      unsigned **array;
      int blocksize;
      int blockcount;

};


#endif //PSEIV_H
