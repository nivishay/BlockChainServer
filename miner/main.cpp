#include "Miner.h"
int main()
{
    Miner miner;
    int id=0;
    int serverfd = open(SERVER_PATH,O_WRONLY);
    miner.serverfd = serverfd;
    int serverfd_for_miner = open(SERVER_PATH_FOR_MINER_PATH,O_RDONLY); // pipe to get the path for each miner 
    write(serverfd,&miner.tlv_to_be_mined,sizeof(TLV)); // first time write to server

    read(serverfd_for_miner,&id,sizeof(int));
    miner.changeid(id);
    char tmp[256];
    sprintf(tmp,"%s%d",MINER_PATH,id); //add miner id to path
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