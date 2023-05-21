#pragma once

#include <network/detail/forward.hpp>

namespace network::detail {

class ENetAddressDeleter {
 public:
  void operator()(ENetAddress* address) const noexcept;
};

}  // namespace network::detail