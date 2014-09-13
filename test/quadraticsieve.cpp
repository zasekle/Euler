#include <iostream>
#include <mpir.h>
#include <vector>
#include <stdint.h>

using namespace std;

vector<unsigned long long> factor_base;
vector<unsigned long long> start;
vector<unsigned long long> factor_base_index;

//ms == 'matrix size'
const int ms = 21000;
uint8_t vec[ms][ms];
uint8_t ident[ms][ms];

//dcs == 'data collection size'
unsigned long long dcs;
unsigned long long pointer = 0;
unsigned long long closenuf;

//solution found boolean
bool sol_found = false;

//T is used to calculate the threshold when sieving
double T;

void sieve(unsigned long long b1);
void refine(const mpz_t n);
void data_collection(const mpz_t n, mpz_t *tX, mpz_t *tY, mpz_t *zero, mpz_t xprog);
void solve_congruences(const mpz_t n);
void quadratic_sieve(mpz_t *zero, mpz_t *X, mpz_t *tX, mpz_t *Y, mpz_t *tY);
void build_matrix(mpz_t *B);
void forward_elimination();
void backwards_elimination();
void find_solution(const mpz_t n, mpz_t *Y, mpz_t *X);
void update_congruences();
void calculate_threshold(const mpz_t n);


int main(){
   //get n, the number to be factored
   mpz_t n;
   mpz_init(n);
   char input[1024];
   cout << "n = ";
   cin >> input;
   mpz_set_str(n, input, 10);

   //set xprog, used to save the progress of X, used for data collection
   mpz_t xprog;
   mpz_init(xprog);
   mpz_sqrt(xprog, n);
   mpz_add_ui(xprog, xprog, 1);

   //get b1, the upper boundary for the factor base
   unsigned long long b1;
   cout << "b1 = ";
   cin >> b1;

   //get T, used for calculating the threshold for sieving
   cout << "T = ";
   cin >> T;

   //sieve out all the composite numbers using the sieve of Eratosthenes
   cout << "Sieving for prime factors...\n";
   sieve(b1);
   cout << "Complete!\n";

   //refine the factor base, leaving only quadratic residues
   cout << "Searching for quadratic residues...\n";
   refine(n);
   cout << "Complete!\n";

   //set the data collection size to 1 greater than the size of the factor base
   dcs = factor_base.size() + 1;

   //use the values of T and n to calculate the sieving threshold
   calculate_threshold(n);

   //initialise arrays to be used for data collection
   unsigned long long i;

   mpz_t *X = new mpz_t[250000];
   mpz_t *Y = new mpz_t[250000];
   mpz_t *tX = new mpz_t[250000];
   mpz_t *tY = new mpz_t[250000];
   mpz_t *zero = new mpz_t[250000];
   mpz_t *B = new mpz_t[250000];

   for(i = 0; i < 250000; i++){
      mpz_init_set_str(X[i], "0", 10);
      mpz_init_set_str(Y[i], "0", 10);
      mpz_init_set_str(B[i], "0", 10);
      mpz_init_set_str(tX[i], "0", 10);
      mpz_init_set_str(tY[i], "0", 10);
      mpz_init_set_str(zero[i], "0", 10);
   }

   //the congruences are stored in the arrays 'start' and 'factor_base_index'
   //'start' contains the index value in the tY array to start the loop on
   //'factor_base_index' contains the value of p, the prime which the indexed value in tY is divisible by
   solve_congruences(n);

   cout << "Collecting data...\n";
   while(pointer <= dcs){
      data_collection(n, tX, tY, zero, xprog);
      quadratic_sieve(zero, X, tX, Y, tY);
      update_congruences();
   }

   for(i = 0; i <= dcs; i++){
      mpz_set(B[i], Y[i]);
   }

   //use the values from the B array for trial division to build the matrix
   cout << "Building matrix...\n";
   build_matrix(B);
   cout << "Complete!\n";

   mpz_clear(*tX);
   mpz_clear(*tY);
   mpz_clear(*B);

   while(sol_found == false){
      //call the gaussian elimination functions
      cout << "Reducing matrix...\n";
      forward_elimination();
      backwards_elimination();

      cout << "Looking for a solution...\n";
      find_solution(n, Y, X);
      cout << "fb: " << factor_base.size() << "\ndcs:" << dcs << "\n";
   }
//   system("pause");
   return 0;
}

void sieve(unsigned long long b1){
   //sieve of Eratosthenes
   vector<int> consecutive;
   unsigned long long p = 0; 
   unsigned long long i;
   cout << "Building Prime Base...\n";
   consecutive.push_back(0);
   consecutive.push_back(0);
   consecutive.push_back(2);
   for(i = 3; i <= b1; i+=2) { 
      consecutive.push_back(i);
      consecutive.push_back(0);
   }
   while(p <= b1) { 
      if(consecutive[p] != 0) { 
         p = consecutive[p]; 
         for(i = p; i <= b1; i+=p) { 
            if(i > p && consecutive[i] != 0) { 
               consecutive[i] = 0; 
            } 
         } 
      } 
      p++; 
   } 
   for(i = 0; i <= b1; i++) { 
      if(consecutive[i] != 0) { 
         factor_base.push_back(consecutive[i]); 
      }
   } 
   consecutive.erase(consecutive.begin(), consecutive.end()); 
} 

void refine(const mpz_t n){
   mpz_t temp;
   mpz_init(temp);
   unsigned long long i;

   //loop through the factor base, if the legendre symbol isn't +1, discard that factor
   for(i = 1; i < factor_base.size(); i++){
      mpz_set_ui(temp, factor_base[i]);
      if(mpz_legendre(n, temp) != 1){
         factor_base.erase(factor_base.begin()+i);
         i--;
      }
   }
   mpz_clear(temp);
}

void data_collection(const mpz_t n, mpz_t *tX, mpz_t *tY, mpz_t *zero, mpz_t xprog){
   mpz_t temp;
   mpz_init(temp);
   unsigned long long cntr = 0;

   //xprog saves the last value that X was set to, so we can start from where we left off
   //calculate x^2 - n and save value in the tX array if it is greater than 1
   //reset the zero array to... zero
   while(cntr < 250000){
      mpz_set(tX[cntr], xprog);
      mpz_mul(temp, xprog, xprog);
      mpz_sub(temp, temp, n);
      mpz_set_ui(zero[cntr], 0);
      if(mpz_cmp_ui(temp, 1) > 0){
         mpz_set(tY[cntr], temp);
         cntr++;
      }
      mpz_add_ui(xprog, xprog, 1);
   }

   mpz_clear(temp);
}

void solve_congruences(const mpz_t n){
   //calculate ceiling of square root of n
   mpz_t sqrt;
   mpz_init(sqrt);
   mpz_sqrt(sqrt, n);
   mpz_add_ui(sqrt, sqrt, 1);

   //solve the case of (X+sqrt)^2 - n = 0 (mod 2)
   unsigned long long X = 0;
   mpz_t temp;
   mpz_init(temp);

   //increment X until a solution is found
   while(1){
      mpz_add_ui(temp, sqrt, X);
      mpz_mul(temp, temp, temp);
      mpz_sub(temp, temp, n);
      mpz_mod_ui(temp, temp, 2);
      if(mpz_cmp_ui(temp, 0) == 0){
         start.push_back(X);
         factor_base_index.push_back(2);
         break;
      }
      X++;
   }

   //now iterate through the factor base, and solve (X+sqrt)^2 - n = 0 (mod p)
   //once solved, push X onto start array, and p onto factor_base_index. Repeat twice for both solutions.
   unsigned long long i;
   unsigned long long solved;

   for(i = 1; i < factor_base.size(); i++){
      X = 0;
      solved = 0;
      while(solved < 2){
         mpz_add_ui(temp, sqrt, X);
         mpz_mul(temp, temp, temp);
         mpz_sub(temp, temp, n);
         mpz_mod_ui(temp, temp, factor_base[i]);
         if(mpz_cmp_ui(temp, 0) == 0){
            start.push_back(X);
            factor_base_index.push_back(factor_base[i]);
            solved++;
         }
         X++;
      }
      cout << "Solved " << i << " of " << factor_base.size() << " congruences\r";
   }

   mpz_clear(sqrt);
   mpz_clear(temp);
}


void quadratic_sieve(mpz_t *zero, mpz_t *X, mpz_t *tX, mpz_t *Y, mpz_t *tY){
   mpz_t temp;
   mpz_init(temp);
   unsigned long long s;
   unsigned long long st;
   unsigned long long inc;
   unsigned long long cntr;
   mpz_t base2;
   mpz_init(base2);
   size_t sz;

   for(s = 0; s < start.size(); s++){
      //starting at st, and incrementing by inc, divide each value by inc
      inc = factor_base_index[s];
      mpz_set_ui(base2, inc);
      sz = mpz_sizeinbase(base2, 2);
      for(st = start[s]; st < 250000; st += inc){
         //increment the zero array by ~log2(inc)
         mpz_add_ui(zero[st], zero[st], sz);
      }
   }

   for(s = 0; s < 250000; s++){
      //values which are at or above the threshold (closenuf) enter the trial division stage
      if(mpz_cmp_ui(zero[s], closenuf) >= 0){
         //the potential smooth number is backed up in the X and Y arrays
         mpz_set(X[pointer], tX[s]);
         mpz_set(Y[pointer], tY[s]);

         //the potential smooth number is divided by each factor in the factor base
         for(cntr = 0; cntr < factor_base.size(); cntr++){
            mpz_mod_ui(temp, tY[s], factor_base[cntr]);
            while(mpz_cmp_ui(temp, 0) == 0){
               mpz_div_ui(tY[s], tY[s], factor_base[cntr]);
               mpz_mod_ui(temp, tY[s], factor_base[cntr]);
            }

            //if the number is smooth increment the pointer, otherwise the value in the X/Y arrays will be
            //overwritten on the next iteration of the loop
            if(mpz_cmp_ui(tY[s], 1) == 0){
               pointer++;
               cout << pointer << "/" << dcs << "                    \r";
               break;
            }
         }
      }
   }

   mpz_clear(temp);
   mpz_clear(base2);
}

void update_congruences(){
   unsigned long long difference;
   unsigned long long overlap;
   unsigned long long offset;
   unsigned long long i;

   for(i = 0; i < start.size(); i++){
      difference = 250000 - start[i];
      overlap = difference % factor_base_index[i];
      offset = factor_base_index[i] - overlap;
      start[i] = offset;
   }
}


void build_matrix(mpz_t *B){
   //initialise arrays
   unsigned long long outer;
   unsigned long long inner;

   for(outer = 0; outer < ms; outer++){
      for(inner = 0; inner < ms; inner++){
         vec[outer][inner] = 0;
         ident[outer][inner] = 0;
      }
   }

   for(outer = 0; outer < ms; outer++){
      ident[outer][outer] = 1;
   }

   //build matrix
   mpz_t temp;
   mpz_init(temp);
   uint8_t flipper = 0;
   unsigned long long row = 0;
   unsigned long long col = 0;

   for(outer = 0; outer < dcs; outer++){
      while(col < factor_base.size()){
         mpz_mod_ui(temp, B[outer], factor_base[col]);
         if(mpz_cmp_ui(temp, 0) == 0){
            flipper++;
            flipper = flipper % 2;
            vec[row][col] = flipper;
            mpz_div_ui(B[outer], B[outer], factor_base[col]);
         }
         else
         {
            col++;
            flipper = 0;
         }
      }
      if(mpz_cmp_ui(B[outer], 1) == 0){
         row++;
      }
      col = 0;
      flipper = 0;
      if(row > dcs){
         break;
      }
   }
   dcs = row;
   mpz_clear(temp);
}

void forward_elimination(){
   long int pivot;
   long int row;
   long int i;
   long int row_iterator;
   long int size;
   size = factor_base.size();

   for(pivot = 0; pivot < size; pivot++){
      cout << pivot << "/" << size << "\r";
      for(row = pivot; row < dcs-1; row++){
         if(vec[row][pivot] == 1){
            for(row_iterator = row+1; row_iterator < dcs; row_iterator++){
               if(vec[row_iterator][pivot] == 1){
                  for(i = 0; i < size; i++){
                     if(vec[row][i] == 1){
                        vec[row_iterator][i] += vec[row][i];
                        vec[row_iterator][i] = vec[row_iterator][i] % 2;
                     }
                  }
                  for(i = 0; i < dcs; i++){
                     if(ident[row][i] == 1){
                        ident[row_iterator][i] += ident[row][i];
                        ident[row_iterator][i] = ident[row_iterator][i] % 2;
                     }
                  }
               }
            }
         }
      }
   }
}

void backwards_elimination(){
   long int pivot;
   long int row;
   long int i;
   long int row_iterator;
   long int size;
   size = factor_base.size();

   for(pivot = size - 1; pivot >= 0; pivot--){
      cout << pivot << "/" << size << "\r";
      for(row = pivot; row > 0; row--){
         if(vec[row][pivot] == 1){
            for(row_iterator = row-1; row_iterator >= 0; row_iterator--){
               if(vec[row_iterator][pivot] == 1){
                  for(i = 0; i < size; i++){
                     if(vec[row][i] == 1){
                        vec[row_iterator][i] += vec[row][i];
                        vec[row_iterator][i] = vec[row_iterator][i] % 2;
                     }
                  }
                  for(i = 0; i < dcs; i++){
                     if(ident[row][i] == 1){
                        ident[row_iterator][i] += ident[row][i];
                        ident[row_iterator][i] = ident[row_iterator][i] % 2;
                     }
                  }
               }
            }
         }
      }
   }
}

void find_solution(const mpz_t n, mpz_t *Y, mpz_t *X){
   unsigned long long i;
   unsigned long long c;
   unsigned long long indexer;
   bool flag;

   vector<unsigned long long> luckydip;

   mpz_t Xt;
   mpz_t Yt;
   mpz_t temp;
   mpz_init(Xt);
   mpz_init(Yt);
   mpz_init(temp);

   for(i = 0; i < dcs; i++){
      mpz_set_ui(Xt, 1);
      mpz_set_ui(Yt, 1);
      flag = true;
      for(c = 0; c < factor_base.size(); c++){
         if(vec[i][c] != 0){
            flag = false;
            break;
         }
      }
      if(flag == true){
         for(c = 0; c < dcs; c++){
            if(ident[i][c] == 1){
               luckydip.push_back(c);
            }
         }
         for(indexer = 0; indexer < luckydip.size(); indexer++){
            mpz_mul(Xt, Xt, X[luckydip[indexer]]);
            mpz_mul(Yt, Yt, Y[luckydip[indexer]]);
         }
         mpz_sqrt(Yt, Yt);
         mpz_sub(temp, Xt, Yt);
         mpz_gcd(temp, temp, n);
         if(mpz_cmp_ui(temp, 1) != 0 && mpz_cmp(temp, n) != 0){
            mpz_out_str(stdout, 10, temp);
            cout << "\n\a";
            mpz_div(temp, n, temp);
            mpz_out_str(stdout, 10, temp);
            cout << "\n";
            sol_found = true;
            return;
         }
      }
      luckydip.erase(luckydip.begin(), luckydip.end());
   }
}

void calculate_threshold(const mpz_t n){
   unsigned long long target;
   size_t sz;
   mpz_t base2;
   mpz_init(base2);

   sz = mpz_sizeinbase(n, 2);
   target = sz / 2;
   mpz_set_ui(base2, 125000);
   sz = mpz_sizeinbase(base2, 2);
   target += sz;

   mpz_set_ui(base2, factor_base[factor_base.size() - 1]);
   sz = mpz_sizeinbase(base2, 2);
   closenuf = T * sz;
   closenuf = target - closenuf;

   cout << "TARGET = " << target << " bits\n";
   cout << "THRESHOLD = " << closenuf << " bits\n";
   cout << "T = " << T << endl;
   //system("pause");
}
