#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <uuid/uuid.h>
#include <zmq.h>

#define CHUNK_SIZE 25000
const std::filesystem::path downloadBinary(std::string socket);