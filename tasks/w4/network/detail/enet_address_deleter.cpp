#include <network/detail/enet_address_deleter.hpp>

#include <enet/enet.h>

namespace network::detail {

void ENetAddressDeleter::operator()(ENetAddress* address) const noexcept {
  delete address;
}

}  // namespace network::detail