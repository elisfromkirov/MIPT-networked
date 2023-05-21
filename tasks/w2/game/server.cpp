#include <game/server.hpp>

#include <iostream>

namespace detail {

// random name generation
std::string_view names[] = {
  "name-1",
  "name-2",
  "name-3"
};

}  // namespace detail

GameServer::GameServer(network::Address address)
    : host_{address},
      clients_{} {
}

void GameServer::Update() {
  host_.Dispatch(this);

  for (auto& client : clients_) {
    client.socket.Send(
      protocol::MakeMessage<protocol::PingRequest>(
        protocol::Tag::kPlayerPingEvent,
        network::Time()
      )
    );

    client.socket.Send(
      protocol::MakeReliableMessage<protocol::GameServerTimeEvent>(
        protocol::Tag::kGameServerTimeEvent,
        network::Time()
      )
    );
  }  
}

void GameServer::OnConnect(network::Socket socket) {
  for (auto& client : clients_) {
    socket.Send(
      protocol::MakeReliableMessage<protocol::PlayerJoinedGameEvent>(
        protocol::Tag::kPlayerJoinedGameEvent,
        client.uuid
      )
    );
  }
}

void GameServer::OnReceive(network::Packet packet) {
  switch (protocol::TagOf(packet)) {
    case protocol::Tag::kJoinGameRequest: {
      OnJoinGameRequest(protocol::Cast<protocol::JoinGameRequest>(packet));
    } break;
    case protocol::Tag::kPingResponse: {
      OnPingResponse(protocol::Cast<protocol::PingResponse>(packet));
    } break;
    default: {
    }
  }  
}

void GameServer::OnJoinGameRequest(protocol::JoinGameRequest* request) {
  auto socket = host_.Connect(network::Address{request->game_client_host, request->game_client_port});
  clients_.emplace_back(clients_.size(), detail::names[clients_.size() % 3], std::move(socket));
}

void GameServer::OnPingResponse(protocol::PingResponse* response) {
  auto ping = network::Time() - response->game_server_time;
  for (auto& client : clients_) {
    client.socket.Send(
      protocol::MakeMessage<protocol::PlayerPingEvent>(
        protocol::Tag::kPlayerPingEvent,
        response->uuid,
        ping
      )
    );
  }
}