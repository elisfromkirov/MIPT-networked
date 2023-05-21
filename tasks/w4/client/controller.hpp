#pragma once

#include <client/client.hpp>

#include <entity/world.hpp>

class Client;

class ClientController {
 public:
  explicit ClientController(World& world);

  void Update(std::uint32_t delta_time);

  void SetupClient(Client* clinet);

  void SetupControlledEntity(const Entity& entity);

  void OnEntityAttachedEvent(EntityAttachedEvent event);

  void OnEntityDetachedEvent(EntityDetachedEvent event);

  void OnEntityMovedEvent(EntityMovedEvent event);

  void OnEntityResizedEvent(EntityResizedEvent event);

 private:
  World* world_;
  Client* client_;
  std::uint64_t controlled_entity_;
};