#include <network/detail/handle.hpp>

#include <utility>

#include <unistd.h>

namespace network::detail {

Handle::Handle(int handle) noexcept
    : handle_{handle} {
}

Handle::Handle(Handle&& other) noexcept
    : handle_{other.handle_} {
  other.handle_ = 0;
}

Handle& Handle::operator=(Handle&& other) noexcept {
  if (this != &other) {
    Handle handle{std::move(other)};
    Swap(handle);
  }
  return *this;
}

Handle::~Handle() noexcept {
  if (handle_ != 0) {
    close(handle_);
  }
}

void Handle::Swap(Handle& other) noexcept {
  std::swap(handle_, other.handle_);
}

}  // namespace network::detail