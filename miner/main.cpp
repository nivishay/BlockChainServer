#include "Miner.h"
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

    Miner miner;
    int id=0;
    std::cout<<server_path<<std::endl;

    int serverfd = open(server_path,O_WRONLY);
    miner.serverfd = serverfd;
    int serverfd_for_miner = open(server_pass_id_path,O_RDONLY); // pipe to get the path for each miner 
    write(serverfd,&miner.tlv_to_be_mined,sizeof(TLV)); // first time write to server

    read(serverfd_for_miner,&id,sizeof(int));
    miner.changeid(id);
    char tmp[MAX_PATH_LENGTH];
    sprintf(tmp,"%s%d",miner_path,id); //add miner id to path
    int Minerfd = open(tmp, O_RDONLY|O_NONBLOCK);
    miner.minerfd = Minerfd;
    if (Minerfd == -1)
    {
        perror("open");
        return 1;
    }
    while (true)
    {
        int readbytes = read(Minerfd,&(miner.tlv_to_be_mined),sizeof(TLV));
        miner.tlv_to_be_mined.block.relayed_by = id;
        miner.mineBlock();
    }
}