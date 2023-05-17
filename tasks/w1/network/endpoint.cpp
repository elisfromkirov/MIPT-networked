#include <network/endpoint.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace network {

Endpoint::Endpoint(const char* address, std::uint16_t port) noexcept
    : address_{ntohl(inet_addr(address))},
      port_{port} {  
}

Endpoint::Endpoint(std::uint32_t address, std::uint16_t port) noexcept
    : address_{address},
      port_{port} {
}

std::uint32_t Endpoint::Address() const noexcept {
  return address_;
}

std::uint16_t Endpoint::Port() const noexcept {
  return port_;
}

}  // namespace network