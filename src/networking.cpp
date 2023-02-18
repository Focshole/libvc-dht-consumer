#include "networking.hpp"
namespace dht_cons
{
  int downloadBinary(std::string socket, const std::filesystem::path &where_to_save)
  {
    void *context = zmq_ctx_new();
    void *sock = zmq_socket(context, ZMQ_PULL);

    zmq_setsockopt(sock, ZMQ_SUBSCRIBE, "", 0);
    int rc = zmq_connect(sock, socket.c_str());
    assert(rc == 0);
    //  Configure socket to not wait at close time
    assert(rc == 0);
    std::ofstream bin(where_to_save, std::ios::binary);
    uint8_t buffer[CHUNK_SIZE];
    auto recvBytes = zmq_recv(sock, buffer, CHUNK_SIZE, 0);
    while (recvBytes > 0 && recvBytes == CHUNK_SIZE)
    {
      bin.write((char *)buffer, recvBytes);
      recvBytes = zmq_recv(sock, buffer, CHUNK_SIZE, 0);
    }
    if (recvBytes == -1)
    {
      zmq_close(sock);
      zmq_ctx_destroy(context);
      bin.close();
      std::filesystem::remove(where_to_save);
      return -1;
    }
    else
    {
      zmq_close(sock);
      zmq_ctx_destroy(context);
      bin.write((char *)buffer, recvBytes);
      bin.close();
    }
    return 0;
  }
}