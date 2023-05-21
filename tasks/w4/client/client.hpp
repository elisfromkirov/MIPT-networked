#pragma once

#include <entity/world.hpp>

#include <network/network.hpp>

#include <protocol/protocol.hpp>

#include <optional>

class ClientController;

class Client final : public network::IHandler {
 public:
  Client(network::Address address, network::Address server_address, ClientController& controller);

  bool IsConnected() const noexcept;

  void Update();

  void SendPlayerEntityMovedEvent(const PlayerEntityMovedEvent& event);

 private:
  void OnConnect(network::Socket socket) override;

  void OnReceive(network::Packet packet) override;

 private:
  network::Host host_;
  std::optional<network::Socket> server_;
  ClientController* controller_;
};