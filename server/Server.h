#ifndef SERVER_H
#define SERVER_H
#include "BLOCK_T&Globals.h"
#include <iostream>
#include <list>

class Server
{
private:
    std::list<BLOCK_T> blockChain;
    bool block_already_mined = false;
     void ServerBlockMessage(BLOCK_T block);
public:
     Server();

    ~Server()
    {

    };
    bool isValidHash(BLOCK_T block);
    void addBlock(BLOCK_T block);
    BLOCK_T lastAddedBlock();
};


#endif // SERVER_H