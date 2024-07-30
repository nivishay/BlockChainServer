#include "BLOCK_T&Globals.h"

int countLeadingZeros(unsigned int number) {
    int leadingZeros = 0;
    for (int i = 31; i >= 0; --i) {
        if ((number & (1U << i)) == 0) {
            leadingZeros++;
        } else {
            break;
        }
    }
    return leadingZeros;
}
// Function to check if the number has exactly x leading zero bits
bool hasLeadingZeroBits(unsigned int number, int x) {
    return countLeadingZeros(number) == x;
}


unsigned long calculateCRC32(const BLOCK_T& block) 
{
    unsigned long crc = crc32(0, nullptr, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef*>(&block), sizeof(block));
    return crc;
}
int getDifficulty(){
    char* configpath = (char*)malloc(MAX_PATH_LENGTH);
    sprintf(configpath, "%s%s", MAIN_PATH, "mtacoin.conf");
    int difficulty = 0;
    std::cout<<"configpath: "<<configpath<<std::endl;
    FILE *file = fopen(configpath, "r");
    if (file == NULL)
    {
        perror("open");
        return 1;
    }
    fscanf(file, "%d", &difficulty);
    fclose(file);
    return difficulty;
}