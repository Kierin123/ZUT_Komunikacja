#include "helpers.h"
#include "linux_headers.h"
#include "standard_headers.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

/*
 * Author: Marcin Kierinkiewicz
 *
 * Program creates to show mechanism of fifo queue. 
 * After start, program waits to open the fifo queue and start transmittion through the queue.
 * To test program need to open new terminal and use command: 
 * echo "Your text to read" > /tmp/my_fifo_name  
 * Program has no dynamically memmory menage. Program can read up to 100 signs. 
 * 
 */


uint8_t g_arr_read[100] = {0};

int main(void)
{
    // Firstly assign some name to our FIFO:
    const char sz_fifo_name[] = "/tmp/my_fifo_name";
    // We need permissions recognizable from Operating System:
    // 0777 - octal - R/W op. from anybody
    mode_t x_permission = 0777;
    // Create named FIFO and save error code:
    int error_code = mkfifo(sz_fifo_name, x_permission);
    
    if (-1 == error_code)
    {
        log_error("Error code: [%d], %s", errno, strerror(errno));
        if (errno != EEXIST)
        {
            log_error("Errno different than EEXIST!");
            exit(EXIT_FAILURE);
        }
    }

    log_info("Successfully created named FIFO with name: %s and perms: 0%o",
             sz_fifo_name, x_permission);

    int file_descriptor = open("/tmp/my_fifo_name", O_RDONLY);

    log_info("FIFO successfully opened with descriptor: %d", file_descriptor);
    size_t x_read_size = sizeof(g_arr_read) / sizeof(g_arr_read[0]);


    int char_elem = read(file_descriptor, g_arr_read, x_read_size);

    if (char_elem < 0)
    {
        log_error("Read failure with ptr: %p", g_arr_read);
        exit(EXIT_FAILURE);
    }

    log_info("Read with success of %d bytes. Read string: ", char_elem);

    int id = 0;
    while (g_arr_read[id] != '\0')
    {
        printf("%c", g_arr_read[id]);
        id++;
    }

    close(file_descriptor);
    log_info("Program successfully ended!");
    return 0;
}
