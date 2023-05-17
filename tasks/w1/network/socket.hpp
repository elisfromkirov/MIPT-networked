#pragma once

#include <network/endpoint.hpp>
#include <network/packet.hpp>

#include <network/detail/handle.hpp>

namespace network {

class Socket final : private detail::Handle {
 public:
  static Socket Connect(Endpoint endpoint);

 public:
  void Send(Packet packet);

 private:
  Socket(int handle, Endpoint endpoint) noexcept;

 private:
  Endpoint endpoint_;
};

}  // namespace network