#include <new>
#include <iostream>

using namespace std;

int main()
{
   int blocksize = 100000;
   int blockcount = 1000000000/blocksize*sizeof(bool)/sizeof(int);
   int **array = new int*[blockcount];
   for ( int i = 0; i < blockcount; ++i )
   {
      array[i] = NULL;
      array[i] = new (std::nothrow) int[blocksize];
      if ( array[i] == NULL )
      {
         cout << "Unable to allocate memory past " << i * blocksize << endl;
         for ( int j = 0; j < i; ++j )
            delete array[j];
         delete array;
         return -1;
      }
   }
   cout << "Successfully created " << blocksize * blockcount << endl;
   for ( int j = 0; j < blockcount; ++j )
      delete array[j];
   delete array;

   return 0;
}
