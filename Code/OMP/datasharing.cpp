#include <iostream>
using namespace std;

#include <omp.h>

int main()
{
    int a = 5;

    #pragma omp parallel num_threads(4) private(a)
    {
        if(omp_get_thread_num() == 1)
            a = 11;

        cout << "a is " << a << endl;
    }

    return 0;
}