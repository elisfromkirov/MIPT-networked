#include <protocol/protocol.hpp>

#include <stream/reader.hpp>
#include <stream/writer.hpp>

Tag TagOf(const network::Packet& packet) {
  return static_cast<Tag>(packet.Data()[0]);
}

network::Packet SerializeJoinGameRequest(const JoinGameRequest& request) {
  network::Packet packet{sizeof(Tag) + sizeof(JoinGameRequest), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kJoinGameRequest);
  writer.Write<std::uint32_t>(request.host);
  writer.Write<std::uint16_t>(request.port);
  return packet;
}

JoinGameRequest DeserializeJoinGameRequest(network::Packet packet) {
  JoinGameRequest request{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  request.host = reader.Read<std::uint32_t>();
  request.port = reader.Read<std::uint16_t>();
  return request;
}

network::Packet SerializeJoinGameResponse(const JoinGameResponse& response) {
  network::Packet packet{sizeof(Tag) + sizeof(JoinGameResponse), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kJoinGameResponse);
  writer.Write<std::uint64_t>(response.uuid);
  writer.Write<float>(response.x);
  writer.Write<float>(response.y);
  writer.Write<float>(response.r);
  return packet;
}

JoinGameResponse DeserializeJoinGameResponse(network::Packet packet) {
  JoinGameResponse response{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  response.uuid = reader.Read<std::uint64_t>();
  response.x = reader.Read<float>();
  response.y = reader.Read<float>();
  response.r = reader.Read<float>();
  return response;
}

network::Packet SerializeEntityAttachedEvent(const EntityAttachedEvent& event) {
  network::Packet packet{sizeof(Tag) + sizeof(EntityAttachedEvent), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kEntityAttachedEvent);
  writer.Write<std::uint64_t>(event.uuid);
  writer.Write<float>(event.x);
  writer.Write<float>(event.y);
  writer.Write<float>(event.r);
  return packet;
}

EntityAttachedEvent DeserializeEntityAttachedEvent(network::Packet packet) {
  EntityAttachedEvent event{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  event.uuid = reader.Read<std::uint64_t>();
  event.x = reader.Read<float>();
  event.y = reader.Read<float>();
  event.r = reader.Read<float>();
  return event;
}

network::Packet SerializeEntityDetachedEvent(const EntityDetachedEvent& event) {
  network::Packet packet{sizeof(Tag) + sizeof(EntityDetachedEvent), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kEntityDetachedEvent);
  writer.Write<std::uint64_t>(event.uuid);
  return packet;
}

EntityDetachedEvent DeserializeEntityDetachedEvent(network::Packet packet) {
  EntityDetachedEvent event{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  event.uuid = reader.Read<std::uint64_t>();
  return event;
}

network::Packet SerializeEntityMovedEvent(const EntityMovedEvent& event) {
  network::Packet packet{sizeof(Tag) + sizeof(EntityMovedEvent), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kEntityMovedEvent);
  writer.Write<std::uint64_t>(event.uuid);
  writer.Write<float>(event.delta_x);
  writer.Write<float>(event.delta_y);
  return packet;
}

EntityMovedEvent DeserializeEntityMovedEvent(network::Packet packet) {
  EntityMovedEvent event{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  event.uuid = reader.Read<std::uint64_t>();
  event.delta_x = reader.Read<float>();
  event.delta_y = reader.Read<float>();
  return event;
}

network::Packet SerializeEntityResizedEvent(const EntityResizedEvent& event) {
  network::Packet packet{sizeof(Tag) + sizeof(EntityResizedEvent), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kEntityResizedEvent);
  writer.Write<std::uint64_t>(event.uuid);
  writer.Write<float>(event.delta_r);
  return packet;
}

EntityResizedEvent DeserializeEntityResizedEvent(network::Packet packet) {
  EntityResizedEvent event{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  event.uuid = reader.Read<std::uint64_t>();
  event.delta_r = reader.Read<float>();
  return event;
}

network::Packet SerializePlayerEntityMovedEvent(const PlayerEntityMovedEvent& event) {
  network::Packet packet{sizeof(Tag) + sizeof(EntityMovedEvent), true};
  stream::Writer writer{packet};
  writer.Write<Tag>(Tag::kPlayerEntityMovedEvent);
  writer.Write<std::uint64_t>(event.uuid);
  writer.Write<float>(event.delta_x);
  writer.Write<float>(event.delta_y);
  return packet;
}

PlayerEntityMovedEvent DeserializePlayerEntityMovedEvent(network::Packet packet) {
  PlayerEntityMovedEvent event{};
  stream::Reader reader{packet};
  reader.Read<Tag>();
  event.uuid = reader.Read<std::uint64_t>();
  event.delta_x = reader.Read<float>();
  event.delta_y = reader.Read<float>();
  return event;
}