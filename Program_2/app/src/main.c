#include "helpers.h"
#include "linux_headers.h"
#include "standard_headers.h"

#define THREAD_COUNT (uint32_t)100UL

static uint32_t volatile sv_u32_global_counter      = 0;
static pthread_t x_thread_object_pool[THREAD_COUNT] = {0};

void *thread_worker_up(void *pv_args) {
    UNUSED(pv_args);
    sv_u32_global_counter++;
    sleep(10);
    pthread_exit(NULL);
}

void *thread_worker_down(void *pv_args) {
    UNUSED(pv_args);
    sv_u32_global_counter--;
    pthread_exit(NULL);
}

int main(void) {

    for (uint32_t u32_idx = 0; u32_idx < THREAD_COUNT; u32_idx++) {
        pthread_create(&x_thread_object_pool[u32_idx], NULL, thread_worker_up,
                       NULL);
    }

    for (uint32_t u32_idx = 0; u32_idx < THREAD_COUNT; u32_idx++) {
        pthread_join(x_thread_object_pool[u32_idx], NULL);
    }
    log_info("Value of sv_u32_global_counter=%d, after all threads executed",
             sv_u32_global_counter);
    return 0;
}
