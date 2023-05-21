#pragma once

#include <network/packet.hpp>
#include <network/socket.hpp>

namespace network {

class IHandler {
 public:
  virtual ~IHandler() noexcept = default;

  virtual void OnConnect(Socket socket) = 0;

  virtual void OnReceive(Packet packet) = 0;
};

}  // namespace network