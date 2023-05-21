#pragma once

#include <cstdint>

namespace input {

class AsyncInput {
 public:
  static std::uint64_t Poll(std::uint8_t* buffer, std::uint64_t size) noexcept;
};

}  // namespace input