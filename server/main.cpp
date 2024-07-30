#include "Server.h"
//find /home/niv/LinuxCourse/mta_task_3/pipes -type p -exec rm {} +
int difficulty = 0;

int main()
{
    char* server_path = {MAIN_PATH};
    char* server_pass_id_path = {MAIN_PATH};
    strcat(server_path,SERVER_PATH);
    strcat(server_pass_id_path,SERVER_PATH_FOR_MINER_PATH);

    int difficulty = getDifficulty();
    int num_of_miners = 1;
    Server server;
    std::vector<int> alive_miners = {}; // fd of every miner
    
    char *tmp = (char *)malloc(strlen(MINER_PATH));
    TLV tlv_to_check;
    TLV  tlv_to_send;
    tlv_to_send.born_first_msg = false;
    tlv_to_send.block = {1,static_cast<int>(time(nullptr)), 0,0, difficulty,1, -1}; 
    if (mkfifo(SERVER_PATH, 0666) == -1) { // server reads from 
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
       if (mkfifo(SERVER_PATH_FOR_MINER_PATH, 0666) == -1) { //server writes path of miner pipe
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
    int serverfd = open(SERVER_PATH,O_RDONLY);//server reads and miners write
    if (serverfd == -1)
    {
        perror("open");
        return 1;
    }
    int serverfd_for_miner = open(SERVER_PATH_FOR_MINER_PATH, O_WRONLY);

    if(serverfd_for_miner == -1)
    {
        perror("open");
        return 1;
    }
     std::cout<<"server started"<<std::endl;
    while (true)
    {
        std::cout<<"please stop"<<std::endl;
        int readbytes = read(serverfd,&tlv_to_check, sizeof(TLV)); // every time will read single tlv 
        if(tlv_to_check.born_first_msg)
        {
            write(serverfd_for_miner,&num_of_miners,sizeof(int));         
            sprintf(tmp,"%s%d",MINER_PATH,num_of_miners); //add miner id to path
                if (mkfifo(tmp, 0666) == -1)
                 {
                    if (errno != EEXIST) {
                        perror("mkfifo");
                            return 1;
                    }
                 }
            int fd_miner = open(tmp, O_WRONLY);
                if (fd_miner == -1) {
                    perror("Error opening FIFO");
                    return 1;
                    }
            alive_miners.push_back(fd_miner);
            write(alive_miners.back(),&tlv_to_send,sizeof(TLV));
           num_of_miners++;
        }
        else
        {
            BLOCK_T latest_in_chain = server.lastAddedBlock();
            if(!server.isValidHash(tlv_to_check.block))
            {
                std::cout<<"Server: invalid hash, block: ";
                std::cout<<std::hex<<tlv_to_check.block.hash;
                std::cout<<std::endl;
                std::cout<<std::dec;
            }

            //TODO: not entering this          
            else if(tlv_to_check.block.height>latest_in_chain.height)// block not mined yet(meaning +1 in height)
            {
                server.addBlock(tlv_to_check.block);
                tlv_to_send.block = {tlv_to_check.block.height + 1,static_cast<int>(time(nullptr)), 0,tlv_to_check.block.hash, difficulty,1, -1};
                for (int i = 0; i < num_of_miners-1; i++)
                {
                    write(alive_miners[i], &tlv_to_send, sizeof(TLV));
                }
            }
            else
            {
                std::cout<<"Server: block: #";
                std::cout<<tlv_to_check.block.height;
                std::cout<<" already mined, block with hash: 0x";
                std::cout<<std::hex<<tlv_to_check.block.hash;
                std::cout<<std::dec;
                std::cout<<" not added"<<std::endl;
            }
        }
    }
}




 
