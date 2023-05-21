#include <platform/keyboard.hpp>

#include <raylib.h>

namespace platform {

bool Keyboard::IsKeyDown(VirtualKey key) noexcept {
  switch (key) {    
    case VirtualKey::kLeftArrow: {
      return ::IsKeyDown(KEY_LEFT);
    } break;
    case VirtualKey::kRightArrow: {
      return ::IsKeyDown(KEY_RIGHT);
    } break;
    case VirtualKey::kUpArrow: {
      return ::IsKeyDown(KEY_UP);
    } break;
    case VirtualKey::kDownArrow: {
      return ::IsKeyDown(KEY_DOWN);
    } break;
    default: {
      return false;
    }
  }
  return false; // __builtin_unreachable();
}

}  // namespace platform