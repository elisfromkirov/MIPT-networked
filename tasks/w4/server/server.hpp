#pragma once

#include <entity/world.hpp>

#include <network/network.hpp>

#include <protocol/protocol.hpp>

#include <vector>

class ServerController;

class Server final : public network::IHandler {
 public:
  Server(network::Address address, ServerController& controller);

  bool IsConnected(const network::Socket& socket) const noexcept;

  void Update();

  void Broadcast(const EntityAttachedEvent& event);

  void Broadcast(const EntityDetachedEvent& event);

  void Broadcast(const EntityMovedEvent& event);

  void Broadcast(const EntityResizedEvent& event);

 private:
  void OnConnect(network::Socket socket) override;

  void OnReceive(network::Packet packet) override;

 private:
  network::Host host_;
  std::vector<network::Socket> clients_;
  ServerController* controller_;
};