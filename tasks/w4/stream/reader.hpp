#pragma once

#include <network/network.hpp>

#include <cstring>

namespace stream {

class Reader {
 public:
  Reader(network::Packet& packet) noexcept;

  template <typename T>
  T Read() noexcept;

 private:
  std::uint8_t* cursor_;
};

template <typename T>
T Reader::Read() noexcept {
  T value{};
  std::memcpy(&value, cursor_, sizeof(T));
  cursor_ += sizeof(T);
  return value;
}

}  // namespace stream