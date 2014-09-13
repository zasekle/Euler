#ifndef BIGNUMS_H
#define BIGNUMS_H

#include <vector>
#include <iostream>

using namespace std;

//handles positive integers only
class Bignum{

   public:
      //uses integers so initial input must fit in integer
      Bignum( int=0 );
      Bignum( const Bignum& );
      Bignum& operator=(const Bignum&);
      Bignum& operator=(const int&);
      const Bignum operator+(const Bignum&) const;
      const Bignum operator+(const int&) const;
      const Bignum operator*(const Bignum&) const;
      const Bignum operator*(const int&) const;
      //this does exponents for now
      const Bignum operator/(const int&) const;
      bool operator==(const Bignum&) const;
      int size();

      friend ostream& operator<<( ostream&, const Bignum&);

   private:
      vector<int> num;

};

#endif //BIGNUMS_H
