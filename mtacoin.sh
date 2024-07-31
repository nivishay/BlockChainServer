#!/bin/bash 

sudo docker pull nivishay/block_miner:3.0
sudo docker pull nivishay/blockchain_server:3.0

sudo docker run -d -v  /tmp/mtacoin/:/mnt/mta nivishay/blockchain_server:3.0
sleep 1

sudo docker run -d -v  /tmp/mtacoin/:/mnt/mta nivishay/block_miner:3.0
sudo docker run -d -v  /tmp/mtacoin/:/mnt/mta nivishay/block_miner:3.0
sudo docker run -d -v  /tmp/mtacoin/:/mnt/mta nivishay/block_miner:3.0
