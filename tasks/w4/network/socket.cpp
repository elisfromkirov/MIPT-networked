#include <network/socket.hpp>

#include <enet/enet.h>

namespace network {

Address Socket::GetAddress() const {
  return Address{peer_->address.host, peer_->address.port};
}

void Socket::Send(Packet packet) noexcept {
  assert(peer_);

  /* Channel 0 is used for reliable packets and channel 1 is used for others */
  auto channel = ((packet.packet_->flags & ENET_PACKET_FLAG_RELIABLE) == ENET_PACKET_FLAG_RELIABLE) ? 0 : 1;

  enet_peer_send(peer_.get(), channel, packet.packet_.release());
}

Socket::Socket(ENetPeer* peer)
    : peer_{peer} {
}

}  // namespace network