#pragma once

#include <network/detail/forward.hpp>

namespace network::detail {

class ENetHostDeleter {
 public:
  void operator()(ENetHost* host) const noexcept;
};

}  // namespace network::detail