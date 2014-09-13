#include <utility>
#include <vector>
#include <iostream>

std::vector< std::pair<int, int> > factor_table;
void fill_sieve( int n )
{
   factor_table.resize(n+1);
   for( int i = 1; i <= n; ++i ) {
      if (i & 1)
         factor_table[i] = std::pair<int, int>(i, 1);
      else
         factor_table[i] = std::pair<int, int>(2, i>>1);
   }
   for( int j = 3, j2 = 9; j2 <= n; ) {
      if (factor_table[j].second == 1) {
         int i = j;
         int ij = j2;
         while (ij <= n) {
            factor_table[ij] = std::pair<int, int>(j, i);
            ++i;
            ij += j;
         }
      }
      j2 += (j + 1) << 2;
      j += 2;
   }
}

std::vector<int> factor( int num )
{
   std::vector<int> factors;
   factors.reserve(30);
   do {
      factors.push_back(factor_table[num].first);
      num = factor_table[num].second;
   } while (num != 1);
   return factors;
}

//const unsigned MAX = 1000;
const unsigned MAX = 10000001;

int main()
{
   fill_sieve(MAX);

   std::vector<int> factors;
   for (int k = 1; k < MAX; k++) {
      factor(k).swap(factors);
      for ( std::vector<int>::const_iterator i = factors.begin(); i != factors.end(); ++i )
         std::cout << *i << ' ';
      std::cout << std::endl;
   }
}
