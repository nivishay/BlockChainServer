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
    TLV tlv_to_be_mined;
    Miner();
    int minerfd;
    int serverfd;
    void MinerBlockMessage(BLOCK_T block);
    void relayMinedBlock(BLOCK_T& block);
    void changeid(int ID);
    int geID()
    {
        return id;
    }
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
