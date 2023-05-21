#pragma once

#include <network/address.hpp>
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
  Address GetAddress() const;

  void Send(Packet packet) noexcept;

 private:
  explicit Socket(ENetPeer* port);

 private:
  std::unique_ptr<ENetPeer, detail::ENetPeerDeleter> peer_;
};

}  // namespace network