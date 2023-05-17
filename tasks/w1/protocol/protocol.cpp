#include <protocol/protocol.hpp>

#include <cstring>

namespace protocol::detail {

constexpr auto kMessageSize = sizeof(Message);

constexpr auto kAddressSize = sizeof(std::declval<network::Endpoint>().Address());

constexpr auto kPortSize = sizeof(std::declval<network::Endpoint>().Port());

}  // namespace protocol::detail

namespace protocol {

network::Packet PackJoinRequest(network::Endpoint endpoint) {
  infra::Array<std::uint8_t> payload{detail::kMessageSize + detail::kAddressSize + detail::kPortSize};

  payload[0] = static_cast<std::uint8_t>(Message::kJoinRequest);

  auto address = endpoint.Address();
  std::memcpy(payload.Data() + detail::kMessageSize, &address, detail::kAddressSize);

  auto port = endpoint.Port();
  std::memcpy(payload.Data() + detail::kMessageSize + detail::kAddressSize, &port, detail::kPortSize);

  return network::Packet{std::move(payload)};
}

network::Packet PackDatagram(const std::string& string) {
  infra::Array<std::uint8_t> payload{detail::kMessageSize + string.size()};

  payload[0] = static_cast<std::uint8_t>(Message::kDatagram);

  std::memcpy(payload.Data() + detail::kMessageSize, string.data(), string.size());

  return network::Packet{std::move(payload)};
}

network::Packet PackKeepAlive() {
  infra::Array<std::uint8_t> payload{detail::kMessageSize};

  payload[0] = static_cast<std::uint8_t>(Message::kKeepAlive);

  return network::Packet{std::move(payload)};
}

network::Endpoint UnpackJoinRequest(network::Packet& packet) {
  std::uint32_t address{};
  std::memcpy(&address, packet.Data() + detail::kMessageSize, detail::kAddressSize);

  std::uint16_t port{};
  std::memcpy(&port, packet.Data() + detail::kMessageSize + detail::kAddressSize, detail::kPortSize);

  return network::Endpoint{address, port};
}

}  // namespace protocol