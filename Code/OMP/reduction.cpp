#include <iostream>
using namespace std;

#include <omp.h>

#define N 64

int main()
{
    int a[N];

    for(int i=0; i<N; i++)
        a[i] = 1;

    int sum = 0;

    #pragma omp parallel num_threads(16) reduction(+:sum)
    {
        int myid = omp_get_thread_num();

        // TODO remove '4' and make more generic using omp_get_num_threads ()
        for(int i = myid * 4; i < (myid + 1) * 4; i++)
        {
            sum += a[i];
        }

        cout << "Thread #" << myid << ": my partials sum is " << sum << endl;
    }

    cout << "sum is " << sum << endl;

    return 0;
}