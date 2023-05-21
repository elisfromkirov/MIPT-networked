#pragma once

#include <network/packet.hpp>

#include <cstring>

namespace protocol {

enum class Tag : std::uint8_t {
  kJoinLobbyRequest,
  kStartGameRequest,
  kGameStartedEvent,
  kJoinGameRequest,
  kJoinGameResponse,
  kPingRequest,
  kPingResponse,
  kPlayerJoinedGameEvent,
  kPlayerPingEvent,
  kGameServerTimeEvent
};

struct JoinLobbyRequest {
  std::uint32_t lobby_client_host;
  std::uint16_t lobby_client_port;
};

struct StartGameRequest {
};

struct GameStartedEvent {
  std::uint32_t game_server_host;
  std::uint16_t game_server_port;
};

struct JoinGameRequest {
  std::uint32_t game_client_host;
  std::uint16_t game_client_port;
};

struct JoinGameResponse  {
  std::uint64_t uuid;
  std::uint8_t name[128];
};

struct PingRequest  {
  std::uint32_t game_server_time;
};

struct PingResponse {
  std::uint64_t uuid;
  std::uint32_t game_server_time;
};

struct PlayerJoinedGameEvent  {
  std::uint64_t uuid;
};

struct PlayerPingEvent {
  std::uint64_t uuid;
  std::uint32_t ping;
};

struct GameServerTimeEvent  {
  std::uint32_t time;
};

static auto TagOf(const network::Packet& packet) noexcept {
  return static_cast<Tag>(packet.Data()[0]);
}

template <typename T>
static auto Cast(const network::Packet& packet) noexcept {
  return reinterpret_cast<T*>(packet.Data() + sizeof(Tag));
}

template <typename T, typename... TArgs>
static auto MakeMessage(Tag tag, TArgs&&... args) {
  auto packet = network::Packet{sizeof(T) + sizeof(Tag), false};
  packet.Data()[0] = static_cast<std::uint8_t>(tag);
  new (packet.Data() + sizeof(Tag)) T{std::forward<TArgs>(args)...};
  return packet;
}

template <typename T, typename... TArgs>
static auto MakeReliableMessage(Tag tag, TArgs&&... args) {
  auto packet = network::Packet{sizeof(T) + sizeof(Tag), true};
  packet.Data()[0] = static_cast<std::uint8_t>(tag);
  new (packet.Data() + sizeof(Tag)) T{std::forward<TArgs>(args)...};
  return packet;
}

}  // namespace protocol