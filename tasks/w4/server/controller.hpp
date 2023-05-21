#pragma once

#include <entity/world.hpp>

#include <protocol/protocol.hpp>

#include <vector>

class Server;

class ServerController {
 public:
  ServerController(World& world);

  void SetupServer(Server* server);

  Entity SetupEntity();

  std::vector<Entity> Entities();

  void Update(std::uint32_t delta_time);

  void OnPlayerEntityMovedEvent(const PlayerEntityMovedEvent& event);

 private:
  World* world_;
  Server* server_;
  std::vector<std::uint64_t> server_controlled_entities_;
};