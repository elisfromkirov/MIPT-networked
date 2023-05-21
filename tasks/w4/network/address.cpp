#include <network/address.hpp>

#include <enet/enet.h>

namespace network {

Address::Address(std::string_view host, std::uint16_t port)
    : address_{new ENetAddress{inet_addr(host.data()), port}} {
}

Address::Address(std::uint32_t host, std::uint16_t port)
    : address_{new ENetAddress{host, port}} {
}

std::uint32_t Address::Host() const noexcept {
  assert(address_);

  return address_->host;
}

std::uint16_t Address::Port() const noexcept {
  assert(address_);

  return address_->port;
}

}  // namespace network