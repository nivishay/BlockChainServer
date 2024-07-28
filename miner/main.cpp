#include "Miner.h"

char MinerConter = '1';
int main()
{
    Miner miner;
    char * tmp = "./Miner_pipe_";
    sprintf(tmp, "%s%d", tmp, MinerConter);
    const char* fifo_path = tmp;
    MinerConter++;
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
        read(fd, &block_to_be_mined, sizeof(block_to_be_mined));
        miner.MinerBlockMessage(block_to_be_mined);
        miner.relayMinedBlock(mined_blocks.back());
    }

}