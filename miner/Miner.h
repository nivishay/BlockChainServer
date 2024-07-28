#ifndef MINER_H
#define MINER_H
#include "BLOCK_T&Globals.h"

class Miner
{
    protected:
    int id;
    
    //calculating the hash//
    public:
    virtual unsigned long mineBlock();
    Miner() = default;
    
    void* start(void* arg);
    void MinerBlockMessage(BLOCK_T block);
    void relayMinedBlock(BLOCK_T& block);

    ~Miner()
    {

    }

};
class FakeMiner : public Miner
{
    public:
        FakeMiner():Miner(){}
    
    unsigned long mineBlock() override;
};


#endif // MINER_H
