#include <network/packet.hpp>

#include <cstring>

namespace network {


Packet::Packet() noexcept 
    : payload_{} {
}

Packet::Packet(const char* data, std::uint64_t size)
    : payload_{size} {
  std::memcpy(payload_.Data(), data, size);
}

Packet::Packet(const std::uint8_t* data, std::uint64_t size) 
    : payload_{size} {
  std::memcpy(payload_.Data(), data, size);
}

Packet::Packet(infra::Array<std::uint8_t>&& payload) noexcept
    : payload_{std::move(payload)} {
}

std::uint8_t* Packet::Data() const noexcept {
  return payload_.Data();
}

std::uint64_t Packet::Size() const noexcept {
  return payload_.Size();
}

Packet::operator bool() const noexcept {
  return payload_.Data() != nullptr;
}

Packet Packet::Clone() {
  return Packet{payload_.Data(), payload_.Size()};
}

}  // namespace network