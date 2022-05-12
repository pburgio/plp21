#include <iostream>
using namespace std;

int main()
{
    #pragma omp parallel num_threads (4)
    {
        cout << "Hello Parallel World!" << endl;

        // Same as
        // cout << "Hello World!";
        // cout << endl;

    } // Implicit barrier

    return 0;
}