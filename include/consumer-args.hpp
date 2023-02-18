#ifndef CONSUMER_ARGS_HPP
#define CONSUMER_ARGS_HPP
#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <opendht.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "consumer-utils.hpp"

dht_cons::params parseAndHandleParams(int argc, char **argv);
#endif // CONSUMER_ARGS_HPP