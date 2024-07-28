#include "Server.h"

int main()
{
    Server server;
    const char* fifo_path = "./Server_pipe";
    if (mkfifo(fifo_path, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
    int fd = open(fifo_path, O_RDONLY);
    
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    while (true)
    {
        
    }
    
    
}