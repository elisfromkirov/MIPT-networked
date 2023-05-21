#pragma once

#include <network/detail/forward.hpp>
#include <network/detail/enet_packet_deleter.hpp>

#include <cassert>
#include <cstdint>

#include <memory>

namespace network {

class Packet final {  
  friend class Host;
  friend class Socket;

 public:
  Packet(std::uint64_t size, bool reliable) noexcept;

  std::uint8_t* Data() const noexcept;

  std::uint64_t Size() const noexcept;

   private:
  explicit Packet(ENetPacket* packet) noexcept;

 private:
  std::unique_ptr<ENetPacket, detail::ENetPacketDeleter> packet_;
};

}  // namespace network