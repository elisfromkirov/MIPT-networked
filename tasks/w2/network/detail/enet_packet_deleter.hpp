#pragma once

#include <network/detail/forward.hpp>

namespace network::detail {

class ENetPacketDeleter {
 public:
  void operator()(ENetPacket* packet) const noexcept;
};

}  // namespace network::detail