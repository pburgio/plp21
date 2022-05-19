#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct thread_param {
    int  s;
    int  e;
    int  tid;
    int* arr;
    float* shared_var;
} thread_param_t;

pthread_mutex_t mtx_shared;

void * thread_main (void * args) {

    thread_param_t params = *((thread_param_t *) args);

    int local_sum = 0;

    for (int i = params.s; i < params.e; i++) {
        local_sum += params.arr[i];
    }

    // critical section
    pthread_mutex_lock  (&mtx_shared);
    *(params.shared_var) += local_sum;
    pthread_mutex_unlock(&mtx_shared);

    return args;
}

float mean_reduce (int* arr, int N, int T) {
    
    pthread_t      * threads = malloc(T*sizeof(pthread_t));
    thread_param_t * params  = malloc(T*sizeof(thread_param_t));

    int chunk = N / T;

    // variabile condivisa
    float mean = 0;

    for (int i = 0; i < T; i++) {

        params[i].tid = i;
        params[i].s   = i*chunk;
        params[i].e   = params[i].s + chunk;
        params[i].arr = arr;
        params[i].shared_var = &mean;

        pthread_create(&threads[i], NULL, thread_main, (void *) &params[i]);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    free(params );
    free(threads);

    return mean /= N;
}

int main (int argc, char ** argv) {

    int N = atoi(argv[1]);
    int T = atoi(argv[2]);

    int * arr = malloc(N*sizeof(int));

    // init array
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }

    pthread_mutex_init(&mtx_shared, NULL); 

    printf("mean: %f\n", mean_reduce (arr, N, T));

    pthread_mutex_destroy(&mtx_shared); 

    free(arr);

    return EXIT_SUCCESS;
}