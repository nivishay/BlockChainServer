# Use a base image with C++ compiler and build tools
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y 

# Set the working directory
WORKDIR /mnt/mta

RUN touch /var/log/mtacoin.log

COPY build/funCoin /app

# Start the server
CMD ["sh", "-c", "/app > /var/log/mtacoin.log"]



