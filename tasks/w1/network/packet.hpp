#pragma once

#include <infra/array.hpp>

#include <cstdint>

namespace network {

class Packet final {
 public:
  Packet() noexcept;

  Packet(const char* data, std::uint64_t size);

  Packet(const std::uint8_t* data, std::uint64_t size);

  Packet(infra::Array<std::uint8_t>&& payload) noexcept;

  std::uint8_t* Data() const noexcept;

  std::uint64_t Size() const noexcept;

  explicit operator bool() const noexcept;

  Packet Clone();

private:
  infra::Array<std::uint8_t> payload_;
};

}  // namespace network