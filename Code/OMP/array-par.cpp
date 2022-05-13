#include <iostream>
using namespace std;

#include <omp.h>

#define NUM 19
int main()
{
	int arr[NUM], i;
	
	#pragma omp parallel num_threads(4) private(i) shared(arr)
	{
		// Knowing NUM
		int myid = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		
		int chunk = NUM / num_threads;
		int chunk_last;
		if(NUM % num_threads == 0)
		{
			chunk_last = chunk;
		}
		else
		{
			chunk ++;
			chunk_last = NUM % chunk;
		}
		
        // Ignore this CRITICAL! It's only for debug purposes
		#pragma omp critical
		{
			cout << "chunk is " << chunk << " chunk_last = " << chunk_last << endl;
		}
		
		int i_start = myid * chunk;
		int i_end;
		if(myid == num_threads - 1 && NUM % num_threads != 0)
			i_end = i_start + chunk_last;
		else
			i_end = i_start + chunk;
	
        // Ignore this CRITICAL! It's only for debug purposes
		#pragma omp critical
		{
			cout << "[Thread " << myid << "/" << num_threads << "]"
				 << " i_start is " << i_start << " i_end = " << i_end << endl;
		}
		
		for(i=i_start; i<i_end; i++)
		{
        	// Ignore this CRITICAL! It's only for debug purposes
			#pragma omp critical
			{
				cout << "[Thread " << myid << "/" << num_threads << "]"
				     << " Executing iteration " << i << endl;
			}

			arr[i] = i * 2;
		}
	}
		
	cout << "----------------" << endl;
	for(i=0; i<NUM; i++)
		cout << "arr[" << i << "] is  "<< arr[i] << endl;
	
	return 0;
}