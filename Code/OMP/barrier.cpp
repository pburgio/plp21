#include <iostream>
using namespace std;
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(256)
    {
        // Ignore this CRITICAL! It's only for debug purposes
        #pragma omp critical
        {
            cout << omp_get_thread_num() << ": I am BEFORE the barrier" << endl;
        }

        if(omp_get_thread_num() == 15)
        {
            #pragma omp barrier
        }

        // Ignore this CRITICAL! It's only for debug purposes
        #pragma omp critical
        {
            cout << omp_get_thread_num() << ": I am AFTER the barrier" << endl;
        }
    } // Join

    cout << "I am after the parreg" << endl;

    return 0;
}