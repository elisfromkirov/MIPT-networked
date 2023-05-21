#include <network/socket.hpp>

#include <enet/enet.h>

#include <iostream>

namespace network {

void Socket::Send(Packet packet) noexcept {
  assert(peer_);

  /* Channel 0 is used for reliable packets and channel 1 is used for others */
  auto channel = ((packet.packet_->flags & ENET_PACKET_FLAG_RELIABLE) == ENET_PACKET_FLAG_RELIABLE) ? 0 : 1;

  enet_peer_send(peer_.get(), channel, packet.packet_.get());

  packet.packet_.reset();
}

Socket::Socket(ENetPeer* socket)
    : peer_{socket} {
}

}  // namespace network