#include "helpers.h"
#include "linux_headers.h"
#include "standard_headers.h"

#define THREAD_COUNT (uint32_t)100UL

static uint32_t volatile sv_u32_global_counter = 0;
//static uint32_t volatile sv_u32_global_counter1 = 0;
pthread_mutex_t mutex_var = PTHREAD_MUTEX_INITIALIZER;

static pthread_t x_thread_object_pool[THREAD_COUNT] = {0};

void *thread_worker_up(void *pv_args)
{
    UNUSED(pv_args);
//    pthread_mutex_lock(&mutex_var);
   
    sv_u32_global_counter++;
// pthread_mutex_unlock(&mutex_var);
//    sv_u32_global_counter1++;
    
    pthread_exit(NULL);
}

int main(void)
{

 //   pthread_mutex_init(&mutex_var, &sv_u32_global_counter);
    for (uint32_t u32_idx = 0; u32_idx < THREAD_COUNT; u32_idx++)
    {
        pthread_create(&x_thread_object_pool[u32_idx], NULL, thread_worker_up,
                       NULL);
    }

    for (uint32_t u32_idx = 0; u32_idx < THREAD_COUNT; u32_idx++)
    {
        pthread_join(x_thread_object_pool[u32_idx], NULL);
    }
    log_info("Value of sv_u32_global_counter= %d %d, after all threads executed",
             sv_u32_global_counter, sv_u32_global_counter1);
    return 0;
}
