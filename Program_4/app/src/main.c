#include "helpers.h"
#include "linux_headers.h"
#include "standard_headers.h"

#define FDESC_SIZE (2)
#define DESC_READ (0)
#define DESC_WRITE (1)

static int s_file_descriptor_array[FDESC_SIZE];
/*
static void parent(void)
{
    close(s_file_descriptor_array[DESC_READ]);
    int32_t u32_my_lovely_number = 0;
    log_info("!!! Please give me your lucky number:");
    scanf("%d", &u32_my_lovely_number);
    write(s_file_descriptor_array[DESC_WRITE], &u32_my_lovely_number, sizeof(int32_t));
    log_info("Wrote %d, from PID: %d", u32_my_lovely_number, getpid());
    close(s_file_descriptor_array[DESC_WRITE]);
}

static void child(void)
{
    close(s_file_descriptor_array[DESC_WRITE]);
    int32_t u32_my_lovely_number_which_receive = 0;
    read(s_file_descriptor_array[0], &u32_my_lovely_number_which_receive, 
        sizeof(u32_my_lovely_number_which_receive));
    close(s_file_descriptor_array[DESC_READ]);  
    log_info("Read %d, from PID: %d, child PID: %d", u32_my_lovely_number_which_receive, getppid(), getpid()); 
}
*/

// Preprocessor definition to set array size and test prints

#define DEBUG_PRINTS

#define TAB_SIZE 10

static void parent(void)
{
    srand(time(NULL));

    close(s_file_descriptor_array[DESC_READ]);

    int8_t u8_tab[TAB_SIZE];

    for (int i = 0; i < TAB_SIZE; i++)
    {
        u8_tab[i] = rand() % 40;
    }

    write(s_file_descriptor_array[DESC_WRITE], &u8_tab, sizeof(int8_t) * TAB_SIZE);

#ifdef DEBUG_PRINTS
    for (int i = 0; i < TAB_SIZE; i++)
    {
        printf("Parent wrote %d, from PID: %d\n", u8_tab[i], getpid());
    }
#endif

    close(s_file_descriptor_array[DESC_WRITE]);
}

static void child(void)
{
    close(s_file_descriptor_array[DESC_WRITE]);
    int8_t u8_tab_receive[TAB_SIZE];

    for (int i = 0; i < TAB_SIZE; i++)
    {
        read(s_file_descriptor_array[0], &u8_tab_receive, sizeof(u8_tab_receive) / sizeof(u8_tab_receive[0]));
    }

#ifdef DEBUG_PRINTS
    for (int i = 0; i < TAB_SIZE; i++)
    {
        printf("Child read %d, from PID: %d\n", u8_tab_receive[i], getpid());
    }
#endif

    close(s_file_descriptor_array[DESC_READ]);
}

int main(void)
{
    // s_file_descriptor_array[0] - for READING
    // s_file_descriptor_array[1] - for WRITING

    if (pipe(s_file_descriptor_array) == -1)
    {
        log_error("Critical error using pipe(...)");
    }

    int forked_process_id = fork();

    if (0 == forked_process_id)
    {
        // We are having child process here
        child();
    }
    else
    {
        // Parent here
        parent();
    }

    return 0;
}
