#include <network/packet.hpp>

#include <enet/enet.h>

namespace network {

Packet::Packet(std::uint64_t size, bool reliable) noexcept
    : packet_{enet_packet_create(nullptr, size, (reliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNSEQUENCED))} {
  assert(packet_);
}

std::uint8_t* Packet::Data() const noexcept {
  assert(packet_);

  return packet_->data;
}

std::uint64_t Packet::Size() const noexcept {
  assert(packet_);

  return packet_->dataLength;
}

Packet::Packet(ENetPacket* packet) noexcept
    : packet_{packet} {
}


}  // namespace network