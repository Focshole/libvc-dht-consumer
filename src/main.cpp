#include <filesystem>
#include <iostream>
#include <opendht.h>
#include <string>
#include <vector>

#include "consumer-args.hpp"
#include "libvc.hpp"
#include "networking.hpp"

const std::string exampleFunctionName = "sha256";

typedef std::string (*sha256_signature_t)(const std::string);

void downloadAndLoadBinary(const std::string &socket,
                           const std::string &functionName) {
  // Download the binary and load it
  auto bin_path = downloadBinary(socket);
  if (bin_path.empty()) {
    std::cerr << "Error while downloading binary. Aborting code loading."
              << std::endl;
    return;
  }
  std::cout << "Downloaded binary at " << bin_path << std::endl;
  // Load the binary
  auto version = fetchVersion(bin_path, {functionName});
  if (!version->compile()) {
    std::cerr << "version from " << bin_path << " failed to compile"
              << std::endl;
    if (version->hasGeneratedBin()) {
      std::cerr << "version from " << bin_path << " has binary "
                << version->getFileName_bin() << std::endl;
    }
    if (version->hasLoadedSymbol()) {
      std::cerr << "version from " << bin_path << " has loaded symbol"
                << std::endl;
    }
    exit(-1);
  }
  // Check that all symbols have been correctly loaded
  if (!version->hasLoadedSymbol()) {
    std::cerr << "version from " << bin_path << " hasn't loaded symbol"
              << std::endl;
    exit(-1);
  }
  // Call the function
  auto sha256 = (sha256_signature_t)version->getSymbol();
  if (!sha256) {
    std::cerr << "Something bad happened, the symbol " << functionName <<" is not available "<<std::endl;
    return;
  }
  std::cout << "Calling " << functionName << " on \"Hello World!\""
            << std::endl;
  std::cout << sha256("Hello World!") << std::endl;
}

bool dhtCallBack(const std::vector<std::shared_ptr<dht::Value>> &values) {
  // Callback called when values are found
  if (values.empty()) {
    std::cerr << "Called callback with no value! Returning." << std::endl;
    return false;
  }
  if (values.size() > 1) {
    std::cerr << "Warning: Multiple values found! Attempting with the first one"
              << std::endl;
  }
  const std::string socket(values[0]->data.begin() + 1, values[0]->data.end());
  std::cout << "Found a socket supplying " << exampleFunctionName << ": "
            << socket << std::endl;
  // Download the binary and load it
  downloadAndLoadBinary(socket, exampleFunctionName);
  return true;
}
int main(int argc, char **argv) {
  auto p = parseAndHandleParams(argc, argv);
  dht::DhtRunner node;
  // Launch a dht node on a new thread, using a
  // generated EC key pair, and listen on port 4224.
  // It is possible to use sockets too.
  node.run(p.dht_port, p.identity, true);

  std::cout << "DHT node started on port " << p.dht_port << std::endl;

  // Join the network through any running node,
  // here using a known bootstrap node.
  // It is possible to use sockets too.
  if (p.dht_bootstrap_socket != "")
    node.bootstrap(p.dht_bootstrap_socket);
  // Wait for the binary code to be available
  node.get(exampleFunctionName, dhtCallBack);
  sleep(10);
  node.join();
  return 0;
}
