#include "Miner.h"

Miner::Miner(){
    tlv_to_be_mined.born_first_msg = true;
    tlv_to_be_mined.block = {1,static_cast<int>(time(nullptr)), 0,0, 0,1, -1};
}
void Miner::changeid(int ID)
{
    id = ID;
}

unsigned long Miner::mineBlock(){
    uint32_t crc;
    bool hasLeadingZeros = false;
    while (!hasLeadingZeros)
    {
        int readbytes = read(minerfd, &tlv_to_be_mined, sizeof(TLV)); // if the server send us a new block, we will check the new one and not the previous one
        if(readbytes != -1)
        {
            std::cout<<"Miner: New block received from server. Height: "<<tlv_to_be_mined.block.height<<std::endl;
            tlv_to_be_mined.block.relayed_by = id;
        }
        crc = calculateCRC32(tlv_to_be_mined.block);
        hasLeadingZeros = hasLeadingZeroBits(crc,tlv_to_be_mined.block.difficulty);
        if(hasLeadingZeros)
        {
            tlv_to_be_mined.block.hash = crc;
            write(serverfd, &tlv_to_be_mined, sizeof(TLV));
            MinerBlockMessage(tlv_to_be_mined.block);
        }
        tlv_to_be_mined.block.nonce++;
    }

    return crc;
}

void Miner::MinerBlockMessage(BLOCK_T block)
{
   std::cout<<"Miner "<<id<<"#"<<": Mined a new block #"<<block.height<<" with hash 0x";//+1 to skip the number before the class name
   std::cout<<std::hex<<block.hash<<std::endl;
   std::cout<<std::dec;
}

