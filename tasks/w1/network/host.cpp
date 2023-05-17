#include <network/host.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace network {

Host Host::Bind(Endpoint endpoint) {
  int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  assert(handle != -1);

  sockaddr_in address = {
    .sin_family = AF_INET,
    .sin_port = htons(endpoint.Port()),
    .sin_addr = { 
      .s_addr = htonl(endpoint.Address())
    }
  };

  int result = bind(handle, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr_in));
  assert(result != -1);

  return Host{handle};
}

Packet Host::Receive() {
  constexpr const std::uint64_t size = 1024;
  std::uint8_t buffer[size] = {};

  auto bytes_received = recvfrom(handle_, buffer, size, 0, nullptr, nullptr);
  if (bytes_received > 0) {
    return Packet{buffer, static_cast<std::uint64_t>(bytes_received)};
  }
  return Packet{};
}

Host::Host(int handle) noexcept
    : detail::Handle{handle} {
}

}  // namespace network