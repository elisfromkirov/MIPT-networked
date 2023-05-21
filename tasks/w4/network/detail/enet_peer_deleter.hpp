#pragma once

#include <network/detail/forward.hpp>

namespace network::detail {

class ENetPeerDeleter {
 public:
  void operator()(ENetPeer* socket) const noexcept;
};

}  // namespace network::detail