#include "Server.h"

Server::Server()
 {

}
BLOCK_T Server::lastAddedBlock()
{
    return blockChain.back();
}
void Server::addBlock(BLOCK_T block)
 {
    blockChain.push_back(block);
    ServerBlockMessage(block); 
}

void Server::ServerBlockMessage(BLOCK_T block)
 {
    std::cout<<"Server: new block added by "<<block.relayed_by<<" attributes: height ("<<block.height<<"), Timestamp("<<block.timestamp<<"), hash (0x";
    std::cout<<std::hex<<block.hash<<"), prev_hash(0x"<<std::hex<<block.prev_hash<<"), difficulty (";
    std::cout<<std::dec<<block.difficulty<<"), nonce ("<<block.nonce<<")"<<std::endl;
}

bool Server::isValidHash(BLOCK_T block) 
{
    int hash =block.hash;
    block.hash = 0;
    if(hash == calculateCRC32(block)&&hasLeadingZeroBits(hash,block.difficulty))
    {
        block.hash = hash;
        return true;
    }
    block.hash = hash;
    return false;
}
