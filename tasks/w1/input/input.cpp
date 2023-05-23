#include <input/input.hpp>

#include <sys/select.h>

#include <unistd.h>

namespace input {

std::uint64_t AsyncInput::Poll(std::uint8_t* buffer, std::uint64_t size) noexcept {
  fd_set rfds{};
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  timeval timeout = { 0, 0 };

  auto stdin_ready = select(1, &rfds, nullptr, nullptr, &timeout);
  if (stdin_ready) {
    auto read_bytes = read(0, buffer, size);
    if (read_bytes) {
      return read_bytes;
    }
  }
  return 0;
}

}  // namespace input