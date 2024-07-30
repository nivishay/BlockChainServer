# Use a base image with C++ compiler and build tools
FROM ubuntu:22.04

# Install build tools
RUN apt-get update && apt-get install -y 

# Set the working directory
WORKDIR /miner

# Copy the CMakeLists.txt file
COPY build .

# Expose the port
EXPOSE 8080

# Start the server
CMD ["./funCoin"]