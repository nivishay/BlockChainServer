#include "Server.h"
//find /home/niv/LinuxCourse/mta_task_3/pipes -type p -exec rm {} +
int difficulty = 0;

int main()
{
    char* server_path = (char*)malloc(MAX_PATH_LENGTH);
    char* server_pass_id_path = (char*)malloc(MAX_PATH_LENGTH);
    char* miner_path = (char*)malloc(MAX_PATH_LENGTH);
    
    strcpy(server_path, MAIN_PATH);
    strcpy(server_pass_id_path, MAIN_PATH);
    strcpy(miner_path, MAIN_PATH);
    strcat(server_path, SERVER_PATH);
    strcat(server_pass_id_path, SERVER_PATH_FOR_MINER_PATH);
    strcat(miner_path, MINER_PATH);

    std::cout<<server_path<<std::endl;
    std::cout<<"reading mnt/mta/config.txt"<<std::endl;
    int difficulty = getDifficulty();
    std::cout<<"difficulty set to: "<<difficulty<<std::endl;
    int num_of_miners = 1;
    Server server;
    std::vector<int> alive_miners = {}; // fd of every miner

    char *tmp = (char *)malloc(MAX_PATH_LENGTH);
    TLV tlv_to_check;
    TLV  tlv_to_send;
    tlv_to_send.born_first_msg = false;
    tlv_to_send.block = {1,static_cast<int>(time(nullptr)), 0,0, difficulty,1, -1}; 

    if (mkfifo(server_path, 0666) == -1) { // server reads from 
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
       if (mkfifo(server_pass_id_path, 0666) == -1) { //server writes path of miner pipe
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }
    int serverfd = open(server_path,O_RDONLY);//server reads and miners write
    
    if (serverfd == -1)
    {
        perror("open");
        return 1;
    }
    int serverfd_for_miner = open(server_pass_id_path, O_WRONLY);

    if(serverfd_for_miner == -1)
    {
        perror("open");
        return 1;
    }
     std::cout<<"server started listening on /mnt/mta/server_pipe"<<std::endl;
    while (true)
    {
        int readbytes = read(serverfd,&tlv_to_check, sizeof(TLV)); // every time will read single tlv 
        if(tlv_to_check.born_first_msg)
        {
            write(serverfd_for_miner,&num_of_miners,sizeof(int));         
            sprintf(tmp,"%s%d",miner_path,num_of_miners); //add miner id to path
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
            std::cout<<"Received connection request from client. ID: "<<num_of_miners<<"pipe path: "<<tmp<<std::endl;
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




 
