#ifndef _WIN32
#define _WIN32

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <zlib.h>
#include <list>
#include <ctime>
#include <pthread.h>
#include <iomanip>
#include <queue>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SERVER_PATH "/home/niv/LinuxCourse/mta_task_3/pipes/server"
#define SERVER_PATH_FOR_MINER_PATH "/home/niv/LinuxCourse/mta_task_3/pipes/servertmp"
#define MINER_PATH "/home/niv/LinuxCourse/mta_task_3/pipes/miner_pipe_" // gerneral path need to add the id of the miner

 typedef struct {
    int         	height;        // Incrementeal ID of the block in the chain
    int         	timestamp;    // Time of the mine in seconds since epoch
    unsigned int    hash;        // Current block hash value
    unsigned int    prev_hash;    // Hash value of the previous block
    int        	difficulty;    // Amount of preceding zeros in the hash
    int         	nonce;        // Incremental integer to change the hash value
    int         	relayed_by;    // Miner ID
 }BLOCK_T;

typedef struct {
   BLOCK_T block;
   bool born_first_msg = false; //when the miner is born for the first time 
}TLV;

bool hasLeadingZeroBits(unsigned int number, int x);
int countLeadingZeros(unsigned int number);
unsigned long calculateCRC32(const BLOCK_T& block);
int getDifficulty();

#endif //_WIN32
