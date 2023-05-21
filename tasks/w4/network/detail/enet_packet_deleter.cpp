#include <network/detail/enet_packet_deleter.hpp>

#include <enet/enet.h>

namespace network::detail {

void ENetPacketDeleter::operator()(ENetPacket* packet) const noexcept {
  if (packet != nullptr) {
    enet_packet_destroy(packet);
  }
}

}  // namespace network::detail