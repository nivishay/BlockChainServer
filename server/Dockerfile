# Use a base image with C++ compiler and build tools
FROM ubuntu:22.04

# Install build tools
RUN apt-get update && apt-get install -y 

# Set the working directory
COPY build/funCoin /app
WORKDIR /var/log
RUN touch mtacoin.log
WORKDIR /mnt/mta
RUN touch mtacoin.config
RUN echo "12" > mtacoin.config
# Copy the CMakeLists.txt file

# Start the server
#CMD ["/app/funCoin", ">", "/var/log/mtacoin.log"]