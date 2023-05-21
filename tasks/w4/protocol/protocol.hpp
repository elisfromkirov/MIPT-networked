#pragma once

#include <network/network.hpp>

enum class Tag : std::uint8_t {
  kJoinGameRequest,
  kJoinGameResponse,  
  kEntityAttachedEvent,
  kEntityDetachedEvent,
  kEntityMovedEvent,
  kEntityResizedEvent,
  kPlayerInput,

  kPlayerEntityMovedEvent
};

Tag TagOf(const network::Packet& packet);

struct JoinGameRequest {
  std::uint32_t host;
  std::uint16_t port;
};

network::Packet SerializeJoinGameRequest(const JoinGameRequest& request);
JoinGameRequest DeserializeJoinGameRequest(network::Packet packet);

struct JoinGameResponse {
  std::uint64_t uuid;
  float x;
  float y;
  float r;
};

network::Packet SerializeJoinGameResponse(const JoinGameResponse& response);
JoinGameResponse DeserializeJoinGameResponse(network::Packet packet);

struct EntityAttachedEvent {
  std::uint64_t uuid;
  float x;
  float y;
  float r;
};

network::Packet SerializeEntityAttachedEvent(const EntityAttachedEvent& event);
EntityAttachedEvent DeserializeEntityAttachedEvent(network::Packet packet);

struct EntityDetachedEvent {
  std::uint64_t uuid;
};

network::Packet SerializeEntityDetachedEvent(const EntityDetachedEvent& event);
EntityDetachedEvent DeserializeEntityDetachedEvent(network::Packet packet);

struct EntityMovedEvent {
  std::uint64_t uuid;
  float delta_x;
  float delta_y;
};

network::Packet SerializeEntityMovedEvent(const EntityMovedEvent& event);
EntityMovedEvent DeserializeEntityMovedEvent(network::Packet packet);

struct EntityResizedEvent {
  std::uint64_t uuid;
  float delta_r;
};

network::Packet SerializeEntityResizedEvent(const EntityResizedEvent& event);
EntityResizedEvent DeserializeEntityResizedEvent(network::Packet packet);

struct PlayerEntityMovedEvent {
  std::uint64_t uuid;
  float delta_x;
  float delta_y;
};

network::Packet SerializePlayerEntityMovedEvent(const PlayerEntityMovedEvent& event);
PlayerEntityMovedEvent DeserializePlayerEntityMovedEvent(network::Packet packet);