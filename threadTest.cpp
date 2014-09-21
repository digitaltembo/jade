#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS     2

int* j;
void *PrintHello(void *closure)
{
   int* i=(int*)closure;
   *i=*i+1;
   cout << "Hello World! number, " << *i << endl;
   pthread_exit(NULL);
}

int main ()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   j=new int;
   *j=5;
   for(int i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread" << endl;
      rc = pthread_create(&threads[i], NULL, 
                          PrintHello, (void *)j);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   cout << "And now: " << *j << endl;
   while(*j<7){}
   cout << "And then again now?" << *j << endl;
   pthread_exit(NULL);
}