#pragma once

#include <network/network.hpp>

#include <cstring>

namespace stream {

class Writer {
 public:
  Writer(network::Packet& packet);

  template <typename T>
  void Write(T value) noexcept;

 private:
  std::uint8_t* cursor_;
};

template <typename T>
void Writer::Write(T value) noexcept {
  std::memcpy(cursor_, &value, sizeof(T));
  cursor_ += sizeof(T);
}

}  // namespace stream