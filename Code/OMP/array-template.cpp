#include <iostream>
using namespace std;
#include <omp.h>

#define NUM 19
int main()
{
	int arr[NUM], i;
	
	// #pragma omp parallel num_threads(4) private(i) shared(arr)
	{
		// Knowing NUM
		// int myid = omp_get_thread_num();
		// int numthreads = omp_get_num_threads();
		//
		// // Find i_start and i_end to use in the loop, as follows
		// int i_start = ???;
		// int i_end = ???;	
		//
		// for(i=istart; i<iend; i++)
		//   arr[i] = i * 2;
			
		
		for(i=0; i<NUM; i++)
			arr[i] = i * 2;
	}
	
	cout << "----------------" << endl;
	for(i=0; i<NUM; i++)
		cout << "arr[" << i << "] is  "<< arr[i] << endl;
	
	return 0;
}