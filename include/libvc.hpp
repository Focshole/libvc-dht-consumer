#ifndef LIBVC_CONSUMER_HPP
#define LIBVC_CONSUMER_HPP

#include "versioningCompiler/CompilerImpl/SystemCompiler.hpp"
#include "versioningCompiler/Version.hpp"

#include <filesystem>
#include <iostream>

#ifndef CLANG_EXE_NAME
#define CLANG_EXE_NAME "clang"
#endif
#ifndef OPT_EXE_FULLPATH
#define OPT_EXE_FULLPATH "/bin/opt"
#endif
#ifndef LLVM_TOOLS_BINARY_DIR
#define LLVM_TOOLS_BINARY_DIR "/usr/bin"
#endif

// load a version from a file
vc::version_ptr_t fetchVersion(std::filesystem::path filePath,
                               std::vector<std::string> functionNames);
#endif // LIBVC_CONSUMER_HPP