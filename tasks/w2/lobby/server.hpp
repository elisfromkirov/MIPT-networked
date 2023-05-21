#pragma once

#include <network/network.hpp>

#include <protocol/protocol.hpp>

#include <optional>
#include <vector>

class LobbyServer final : private network::IHandler { 
 public:
  LobbyServer(network::Address address);

  void Update();

 private:
  void OnConnect(network::Socket socket) override;

  void OnReceive(network::Packet packet) override;

 private:
  void OnJoinLobbyRequest(protocol::JoinLobbyRequest* request);

  void OnStartGameRequest(protocol::StartGameRequest* request);

 private:
  bool GameStarted() const noexcept;

 private:
  network::Host host_;
  std::vector<network::Socket> clients_;
  std::optional<network::Address> game_server_address_;
};