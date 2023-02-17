set(LibVersioningCompilerCons_SOURCE_PATH @PROJECT_SOURCE_DIR@)
set(LibVersioningCompilerCons_BINARY_PATH @PROJECT_BINARY_DIR@)
set(LibVersioningCompilerCons_INSTALL_PATH @CMAKE_INSTALL_PREFIX@)
# check for headers
find_path(
  LibVersioningCompilerCons_INCLUDE_DIRS versioningCompilerCons/networking.hpp
  PATHS ${LibVersioningCompilerCons_INSTALL_PATH}/include ${LibVersioningCompilerCons_SOURCE_PATH}/include
        /usr/local/include /usr/include ${CMAKE_EXTRA_INCLUDES}
  NO_DEFAULT_PATH)

if(LibVersioningCompilerCons_INCLUDE_DIRS-NOTFOUND)
  set(LibVersioningCompilerCons_FOUND FALSE)
  if(LibVersioningCompilerCons_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find LibVersioningCompilerCons headers!")
  endif(LibVersioningCompiler_FIND_REQUIRED)
endif(LibVersioningCompilerCons_INCLUDE_DIRS-NOTFOUND)
# check for the libVersioningCompilerCons library
find_library(
  LibVersioningCompilerCons_LIBRARY VersioningCompilerCons
  PATHS ${LibVersioningCompilerCons_INSTALL_PATH}/lib ${LibVersioningCompilerCons_BINARY_PATH} /usr/local/lib /usr/lib
        /lib ${CMAKE_EXTRA_LIBRARIES}
  NO_DEFAULT_PATH)

if(LibVersioningCompilerCons_LIBRARY-NOTFOUND)
  set(LibVersioningCompilerCons_FOUND FALSE)
  if(LibVersioningCompilerCons_LIBRARY_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find LibVersioningCompilerCons library!")
  endif(LibVersioningCompilerCons_LIBRARY_FIND_REQUIRED)
endif(LibVersioningCompilerCons_LIBRARY-NOTFOUND)

get_filename_component(LibVersioningCompilerCons_LIBRARY_DIR ${LibVersioningCompilerCons_LIBRARY} PATH)

set(LibVersioningCompilerCons_LIBRARIES ${LibVersioningCompilerCons_LIBRARY} ${UUID_LIBRARY} ${CMAKE_DL_LIBS})

# Check for libVersioningCompiler
find_package(LibVersioningCompiler REQUIRED)
set(LibVersioningCompilerCons_INCLUDE_DIRS "${LibVersioningCompilerCons_INCLUDE_DIRS}" "${LIBVC_INCLUDE_DIRS}")
set(LibVersioningCompilerCons_LIBRARIES "${LibVersioningCompilerCons_LIBRARIES}" "${LIBVC_LIBRARIES}")

# Check that opendht is installed
find_package(GnuTLS REQUIRED)
if(NOT GNUTLS_FOUND)
  message(FATAL_ERROR "GnuTLS not found")
endif(NOT GNUTLS_FOUND)
set(LibVersioningCompilerCons_INCLUDE_DIRS "${LibVersioningCompilerCons_INCLUDE_DIRS}" "${GNUTLS_INCLUDE_DIR}")
set(LibVersioningCompilerCons_LIBRARIES "${LibVersioningCompilerCons_LIBRARIES}" "${GNUTLS_LIBRARIES}")
find_package(opendht REQUIRED)
if(NOT opendht_FOUND)
  message(FATAL_ERROR "opendht not found")
endif(NOT opendht_FOUND)
set(LibVersioningCompilerCons_LIBRARIES ${LibVersioningCompilerCons_LIBRARIES} "opendht")

find_package(libzmq REQUIRED)
if(NOT LIBZMQ_FOUND)
  message(FATAL_ERROR "libzmq not found")
endif(NOT LIBZMQ_FOUND)
set(LibVersioningCompilerCons_INCLUDE_DIRS "${LibVersioningCompilerCons_INCLUDE_DIRS}" "${LIBZMQ_INCLUDE_DIRS}")
set(LibVersioningCompilerCons_LIBRARIES "${LibVersioningCompilerCons_LIBRARIES}" "${LIBZMQ_LIBRARIES}")
set(LibVersioningCompilerCons_LIBRARIES ${LibVersioningCompilerCons_LIBRARIES} "-lzmq" )


get_filename_component(LibVersioningCompilerCons_LIBRARY_DIR ${LibVersioningCompilerCons_LIBRARY} PATH)


list(REMOVE_DUPLICATES LibVersioningCompilerCons_INCLUDE_DIRS)
list(REMOVE_DUPLICATES LibVersioningCompilerCons_LIBRARIES)


# set also standard cmake variable names
if(LibVersioningCompilerCons_FOUND)
  set(LibVersioningCompilerCons_INCLUDES ${LibVersioningCompilerCons_INCLUDE_DIRS})
  set(LibVersioningCompilerCons_LIBS ${LibVersioningCompilerCons_LIBRARIES})
endif(LibVersioningCompilerCons_FOUND)
