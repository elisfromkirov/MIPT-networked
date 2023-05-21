#pragma once

#include <network/packet.hpp>

#include <network/detail/forward.hpp>
#include <network/detail/enet_peer_deleter.hpp>

#include <cassert>
#include <cstdint>

#include <memory>

namespace network {

class Socket {
  friend class Host;

 public:
  void Send(Packet packet) noexcept;

 private:
  explicit Socket(ENetPeer* socket);

 private:
  std::unique_ptr<ENetPeer, detail::ENetPeerDeleter> peer_;
};

}  // namespace network