#include <stdio.h>
#include <pthread.h>

void *my_pthread_fn(void *arg)
{
    // Thread body
    printf("\t\t\t\t\tHello World! I am a PThread!\n");

    return 0;
}

int main()
{
    printf("Hello World!\n");

    /*
    int pthread_create ( pthread_t *ID,
                     pthread_attr_t *attr,
                     void *(*body)(void *),
                     void * arg
 		      );
    */

    pthread_t myid;
    pthread_attr_t myattr;

    int err = pthread_attr_init(&myattr);
    //TODO interpret return code, and take necessary countermeasures
    
    err = pthread_create(
        &myid,          // Output parameter
        &myattr,        // Empty
        my_pthread_fn,  // Body fn
        (void *) 0      // (Null) param
    );
    err = pthread_attr_destroy(&myattr);

    // Here, I can do useful work
    printf("I am working...\n");
    printf("I am working again...\n");
    printf("I am still working...\n");
    printf("Guess what? I am working...\n");
    printf("I am working, but I'm nearly don...\n");

    /*
    int pthread_join ( pthread_t th,
                   void **thread_return);
    */

    void * retval;
    err = pthread_join(myid, &retval);
    //printf("Join returned %d\n", err);

    return 0;
}