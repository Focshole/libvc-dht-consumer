#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <zmq.h>

#define CHUNK_SIZE 25000
namespace dht_cons
{
    // Downloads a binary from a socket. Returns 0 on success, -1 on failure
    int downloadBinary(std::string socket,const std::filesystem::path& where_to_save);
}