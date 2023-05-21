#pragma once

#include <cstdint>

namespace platform {

enum class VirtualKey {
  kLeftArrow,
  kRightArrow,
  kUpArrow,
  kDownArrow
};

class Keyboard {
 public: 
  static bool IsKeyDown(VirtualKey key) noexcept;
};

}  // namespace platform