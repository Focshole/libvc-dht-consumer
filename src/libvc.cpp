#ifndef LIBVC_CONSUMER_CPP
#define LIBVC_CONSUMER_CPP
#include "libvc.hpp"

vc::version_ptr_t fetchVersion(std::filesystem::path filePath,
                               std::vector<std::string> functionNames) {
  return vc::Version::Builder::createFromSO(
      filePath, functionNames, vc::make_compiler<vc::SystemCompiler>(), false);
}
#endif // LIBVC_CONSUMER_CPP