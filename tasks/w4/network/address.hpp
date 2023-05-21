#pragma once

#include <network/detail/forward.hpp>
#include <network/detail/enet_address_deleter.hpp>

#include <cassert>
#include <cstdint>

#include <memory>
#include <string_view>

namespace network {

class Address final {
  friend class Host;

 public:
  Address(std::string_view host, std::uint16_t port);

  Address(std::uint32_t host, std::uint16_t port);

  std::uint32_t Host() const noexcept;

  std::uint16_t Port() const noexcept;

 private:
  std::unique_ptr<ENetAddress, detail::ENetAddressDeleter> address_;
};

}  // namespace network