#pragma once

#include <cstdint>

namespace network {

class Endpoint final {
 public:
  Endpoint(const char* address, std::uint16_t port) noexcept;

  Endpoint(std::uint32_t address, std::uint16_t port) noexcept;

  std::uint32_t Address() const noexcept;

  std::uint16_t Port() const noexcept;

 private:
  std::uint32_t address_;
  std::uint16_t port_;
};

}  // namespace network