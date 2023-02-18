#include <filesystem>
#include <iostream>
#include <opendht.h>
#include <string>
#include <vector>

#include "consumer-args.hpp"
#include "libvc.hpp"

const std::string exampleFunctionName = "sha256";
typedef std::string (*sha256_signature_t)(const std::string);

bool exampleDhtCallBack(const std::vector<std::shared_ptr<dht::Value>> &values)
{
  // Callback called when values are found
  if (values.empty())
  {
    std::cerr << "Called callback with no value! Returning." << std::endl;
    return false;
  }
  if (values.size() > 1)
  {
    std::cerr << "Warning: Multiple values found! Attempting with the first one"
              << std::endl;
  }
  const std::string socket(values[0]->data.begin() + 1, values[0]->data.end());
  std::cout << "Found a socket supplying " << exampleFunctionName << ": "
            << socket << std::endl;
  // Download the binary and load it

  // grenerate a random name for the binary
  uuid_t uuid;
  char tmp[128];
  uuid_generate(uuid);
  uuid_unparse(uuid, tmp);
  const std::filesystem::path where_to_save = std::filesystem::u8path(std::string(tmp) + ".so");

  std::cout << "Downloading version and loading binary" << exampleFunctionName << ": "
            << where_to_save << std::endl;
  auto version = dht_cons::downloadVersion(socket, {exampleFunctionName}, where_to_save);
  if (version == nullptr)
  {
    std::cerr << "Something bad happened, the version is not available " << std::endl;
    return false;
  }
  // Return the first symbol only
  auto sha256 = (sha256_signature_t)version->getSymbol();
  if (!sha256)
  {
    std::cerr << "Something bad happened, the symbol " << exampleFunctionName << " is not available " << std::endl;
    return false;
  }
  std::cout << "Calling " << exampleFunctionName << " on \"Hello World!\""
            << std::endl;
  std::cout << sha256("Hello World!") << std::endl;
  return true;
}

int main(int argc, char **argv)
{
  auto p = parseAndHandleParams(argc, argv);
  auto node = dht_cons::bootstrapDHTNode(p);
  std::cout << "DHT node started on port " << p.dht_port << std::endl;
  // Wait for the binary code to be available
  node->get(exampleFunctionName, exampleDhtCallBack);
  // Wait for the binary code for 10 seconds
  sleep(10);
  node->join();
  return 0;
}
