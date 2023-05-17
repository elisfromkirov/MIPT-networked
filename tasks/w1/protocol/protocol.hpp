#pragma once

#include <network/endpoint.hpp>
#include <network/packet.hpp>

#include <cstdint>
#include <string>

namespace protocol {

enum class Message : std::uint8_t {
  kJoinRequest,
  kDatagram,
  kKeepAlive
};

network::Packet PackJoinRequest(network::Endpoint endpoint);

network::Packet PackDatagram(const std::string& string);

network::Packet PackKeepAlive();

network::Endpoint UnpackJoinRequest(network::Packet& packet);

}  // namespace protocol