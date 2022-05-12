#include <iostream>
using namespace std;

#include <omp.h>

int main()
{
    // int omp_get_thread_num(void);
    int myid = omp_get_thread_num();
    cout << "Hello World, I am thread #" << myid << " and I am BEFORE the parreg" << endl;

    #pragma omp parallel num_threads (4)
    {
        // Uncomment this to avoid interleaving of write operations
        //   (we will see how the CRITICAL pragma works next lesson
        //#pragma omp critical
        //{
            int myid = omp_get_thread_num();
            cout << "\t\t\t\tHello world, I am thread #" << myid << " and I am INSIDE the parreg" << endl;
        //}
    } // Implicit barrier
    
    myid = omp_get_thread_num(); // Unnecessary...we'll see this soon
    cout << "Hello world, I am thread #" << myid << " and I am AFTER the parreg" << endl;

    return 0;
}