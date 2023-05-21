#pragma once

#include <network/network.hpp>

#include <protocol/protocol.hpp>

#include <optional>

class Client final : public network::IHandler {
 public:
  Client(network::Address address, network::Address lobby_address);

  void Update();

 private:
  void OnConnect(network::Socket socket) override;

  void OnReceive(network::Packet packet) override;

 private:
  void OnGameStartedEvent(protocol::GameStartedEvent* event);

  void OnJoinGameResponse(protocol::JoinGameResponse* response);

  void OnPingRequest(protocol::PingRequest* request);

  void OnPlayerJoinedGameEvent(protocol::PlayerJoinedGameEvent* event);

  void OnPlayerPingEvent(protocol::PlayerPingEvent* event);

  void OnGameServerTimeEvent(protocol::GameServerTimeEvent* event);

 private:
  enum class State {
    kUsual,
    kConnectingToLobby,
    kConnectingToServer
  };

 private:
  network::Host host_;
  std::optional<network::Socket> lobby_;
  std::optional<network::Socket> server_;
  State state_;
  std::uint64_t uuid_;
};