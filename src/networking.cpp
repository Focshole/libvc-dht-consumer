#include "networking.hpp"

const std::filesystem::path downloadBinary(std::string socket) {
  void *context = zmq_ctx_new();
  void *sock = zmq_socket(context, ZMQ_PULL);

  zmq_setsockopt(sock, ZMQ_SUBSCRIBE, "", 0);
  int rc = zmq_connect(sock, socket.c_str());
  assert(rc == 0);
  //  Configure socket to not wait at close time
  assert(rc == 0);
  uuid_t uuid;
  char tmp[128];
  uuid_generate(uuid);
  uuid_unparse(uuid, tmp);
  const std::filesystem::path bin_path =
      std::filesystem::u8path(std::string(tmp) + ".so");
  std::ofstream bin(bin_path, std::ios::binary);
  uint8_t buffer[CHUNK_SIZE];
  auto recvBytes = zmq_recv(sock, buffer, CHUNK_SIZE, 0);
  while (recvBytes > 0 && recvBytes == CHUNK_SIZE) {
    std::cout << "Received " << recvBytes << " bytes" << std::endl;
    bin.write((char *)buffer, recvBytes);
    recvBytes = zmq_recv(sock, buffer, CHUNK_SIZE, 0);
  }
  if (recvBytes == -1) {
    std::cerr << "Error while receiving file " << bin_path << ": "
              << zmq_strerror(zmq_errno()) << std::endl;
    bin.close();
    std::filesystem::remove(bin_path);
    return "";
  } else {
    bin.write((char *)buffer, recvBytes);
    bin.close();
  }
  return bin_path;
}