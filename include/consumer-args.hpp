#ifndef CONSUMER_ARGS_HPP
#define CONSUMER_ARGS_HPP
#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <opendht.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

struct params {
  const dht::crypto::Identity identity;
  const std::string dht_bootstrap_socket;
  int dht_port;
};
params parseAndHandleParams(int argc, char **argv);
#endif // CONSUMER_ARGS_HPP