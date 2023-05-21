#pragma once

#include <network/network.hpp>

#include <protocol/protocol.hpp>

#include <string>
#include <vector>

class GameServer final : private network::IHandler {
 public:
  GameServer(network::Address address);

  void Update();

 private:
  void OnConnect(network::Socket socket) override;

  void OnReceive(network::Packet packet) override;

 private:
  void OnJoinGameRequest(protocol::JoinGameRequest* request);

  void OnPingResponse(protocol::PingResponse* response);

 private:
  struct Client {
    std::uint64_t uuid;
    std::uint8_t name[128];
    network::Socket socket;

    Client(std::uint32_t uuid, std::string_view string_name, network::Socket socket)
        : uuid{uuid},
          name{},
          socket{std::move(socket)} {
      std::memcpy(name, string_name.data(), string_name.size());
    }
  };

 private:
  network::Host host_;
  std::vector<Client> clients_;
};