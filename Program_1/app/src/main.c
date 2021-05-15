#include "helpers.h"
#include "linux_headers.h"
#include "standard_headers.h"

#define NUM_THREADS 100

void *perform_work(void *arguments) {
    int index      = *((int *)arguments);
    int sleep_time = 1 + rand() % NUM_THREADS;
    log_info("Thread: %d, Started.", index);
    log_info("Thread: %d, Will be sleeping for %d seconds.", index, sleep_time);
    sleep(sleep_time);
    log_info("Thread: %d, Ended.", index);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int       thread_args[NUM_THREADS];
    int       i;
    int       result_code;

    // Create all threads sequentially
    for (i = 0; i < NUM_THREADS; i++) {
        log_info("Creating thread %d.", i);
        thread_args[i] = i;
        result_code =
            pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    log_info("All threads are created.");

    // Join will wait for all threads to complete
    for (i = 0; i < NUM_THREADS; i++) {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        log_info("Thread %d has ended.", i);
    }

    log_info("Program has ended.");
    return 0;
}
