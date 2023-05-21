#include <network/detail/enet_host_deleter.hpp>

#include <enet/enet.h>

namespace network::detail {

void ENetHostDeleter::operator()(ENetHost* host) const noexcept {
  if (host != nullptr) {
    enet_host_destroy(host);
  }
}

}  // namespace network::detail