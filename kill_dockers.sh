#!/bin/bash
containers=$(sudo docker ps -q)

# Kill each container
for container in $containers; do
    sudo docker kill $container
done
