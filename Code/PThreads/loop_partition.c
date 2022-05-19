#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct thread_param {
    int  s;
    int  e;
    int  tid;
    int* arr;
} thread_param_t;

pthread_mutex_t mtx_stdout;

void * thread_main (void * args) {

    thread_param_t params = *((thread_param_t *) args);

    for (int i = params.s; i < params.e; i++) {
        
        params.arr[i] = 2*i;

        pthread_mutex_lock  (&mtx_stdout);
        printf("thread %d: arr[%d] = %d\n", params.tid, i, params.arr[i]);
        pthread_mutex_unlock(&mtx_stdout);
    }

    return args;
}

int main (int argc, char ** argv) {

    int N = atoi(argv[1]);
    int T = atoi(argv[2]);

    int            * arr     = malloc(N*sizeof(int));
    pthread_t      * threads = malloc(T*sizeof(pthread_t));
    thread_param_t * params  = malloc(T*sizeof(thread_param_t));

    pthread_mutex_init(&mtx_stdout, NULL); 

    int is_multiple = N % T == 0; 
    int chunk       = is_multiple ? N / T : N / T + 1;

    for (int i = 0; i < T; i++) {

        params[i].s = i * chunk;
        if (!is_multiple && (i == T-1)) {
            params[i].e = params[i].s + N % chunk;
        }
        else{
            params[i].e = params[i].s + chunk;
        }
        params[i].tid = i;
        params[i].arr = arr;

        pthread_create(&threads[i], NULL, thread_main, (void *) &params[i]);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    // printf("arr = [ ");
    // for (int i = 0; i < N; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("]\n");

    pthread_mutex_destroy(&mtx_stdout); 

    free(arr);
    free(params);
    free(threads);

    return EXIT_SUCCESS;
}