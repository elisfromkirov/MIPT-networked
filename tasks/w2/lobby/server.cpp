#include <lobby/server.hpp>

#include <iostream>

LobbyServer::LobbyServer(network::Address address)
    : host_{address},
      clients_{},
      game_server_address_{} {
}

void LobbyServer::Update() {
  host_.Dispatch(this);
}

void LobbyServer::OnConnect(network::Socket socket) { 
  if (!GameStarted()) {
    clients_.push_back(std::move(socket));
  } else {
    socket.Send(
      protocol::MakeReliableMessage<protocol::GameStartedEvent>(
        protocol::Tag::kGameStartedEvent,
        game_server_address_->Host(),
        game_server_address_->Port()
      )
    );
  }
}

void LobbyServer::OnReceive(network::Packet packet) {
  switch (protocol::TagOf(packet)) {
    case protocol::Tag::kJoinLobbyRequest: {
      OnJoinLobbyRequest(protocol::Cast<protocol::JoinLobbyRequest>(packet));
    } break;
    case protocol::Tag::kStartGameRequest: {
      OnStartGameRequest(protocol::Cast<protocol::StartGameRequest>(packet));
    } break;
    default: {
    }
  }
}

void LobbyServer::OnJoinLobbyRequest(protocol::JoinLobbyRequest* request) {
  host_.Connect(network::Address{request->lobby_client_host, request->lobby_client_port});
}

void LobbyServer::OnStartGameRequest(protocol::StartGameRequest* request) {
  if (!GameStarted()) {
    game_server_address_.emplace("127.0.0.1", 2022);

    for (auto& client : clients_) {
      client.Send(
        protocol::MakeReliableMessage<protocol::GameStartedEvent>(
          protocol::Tag::kGameStartedEvent,
          game_server_address_->Host(),
          game_server_address_->Port()
        )
      );
    }
  }
}

bool LobbyServer::GameStarted() const noexcept {
  return game_server_address_.has_value();
}