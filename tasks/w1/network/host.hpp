#pragma once

#include <network/endpoint.hpp>
#include <network/packet.hpp>

#include <network/detail/handle.hpp>

namespace network {

class Host final : private detail::Handle {
 public:
  static Host Bind(Endpoint endpoint);

 public:
  Packet Receive();

 private:
  explicit Host(int handle) noexcept;
};

}  // namespace network