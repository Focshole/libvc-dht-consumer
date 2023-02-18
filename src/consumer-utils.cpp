#include "consumer-utils.hpp"

namespace dht_cons
{
    vc::version_ptr_t downloadVersion(const std::string &socket,
                                      const std::vector<std::string> &symbolNames, const std::filesystem::path &where_to_save)
    {
        auto status = downloadBinary(socket, where_to_save);
        if (where_to_save.empty() || status != 0)
        {
            std::cerr << "Error while downloading binary. Aborting code loading."
                      << std::endl;
            return nullptr;
        }
        return std::move(createVersionFromFile(where_to_save, symbolNames));
    }

    std::shared_ptr<dht::DhtRunner> bootstrapDHTNode(const params &bootstrapParams)
    {
        auto node = std::make_shared<dht::DhtRunner>();
        node->run(bootstrapParams.dht_port, bootstrapParams.identity, true);
        if (bootstrapParams.dht_bootstrap_socket != "")
            node->bootstrap(bootstrapParams.dht_bootstrap_socket);
        return std::move(node);
    }
}