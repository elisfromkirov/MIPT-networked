#include <network/socket.hpp>

#include <cstdint>
#include <cstring>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace network {

Socket Socket::Connect(Endpoint endpoint) {
  int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  assert(handle != -1);

  return Socket{handle, endpoint};
}

void Socket::Send(Packet packet) {
  sockaddr_in address = {
    .sin_family = AF_INET,
    .sin_port = htons(endpoint_.Port()),
    .sin_addr = { 
      .s_addr = htonl(endpoint_.Address())
    }
  };

  sendto(handle_, packet.Data(), packet.Size(), 0, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr_in));
}

Socket::Socket(int handle, Endpoint endpoint) noexcept
    : detail::Handle{handle},
      endpoint_{endpoint} {
}

}  // namespace network