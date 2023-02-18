#ifndef LIBVC_CONSUMER_CPP
#define LIBVC_CONSUMER_CPP
#include "libvc.hpp"

vc::version_ptr_t createVersionFromFile(std::filesystem::path filePath,
                                        std::vector<std::string> functionNames)
{
    vc::version_ptr_t version = vc::Version::Builder::createFromSO(
        filePath, functionNames, vc::make_compiler<vc::SystemCompiler>(), false);
    if (version->compile() && version->hasLoadedSymbol())
        return version;
    else
        return nullptr;
}
#endif // LIBVC_CONSUMER_CPP