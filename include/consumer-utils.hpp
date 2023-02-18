#include <opendht/crypto.h>
#include <opendht.h>

#include "networking.hpp"
#include "libvc.hpp"
#include "versioningCompiler/Version.hpp"

namespace dht_cons
{

    struct params
    {
        const dht::crypto::Identity identity;
        const std::string dht_bootstrap_socket;
        int dht_port;
    };
    // Fetch a version from a socket, then builds a version whose binary is created at where_to_save and returns the version pointer
    vc::version_ptr_t downloadVersion(const std::string &socket,
                                      const std::vector<std::string> &symbolNames, const std::filesystem::path &where_to_save);

    std::shared_ptr<dht::DhtRunner> bootstrapDHTNode(const params &bootstrapParams);
}