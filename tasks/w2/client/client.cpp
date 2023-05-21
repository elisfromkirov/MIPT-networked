#include <client/client.hpp>

#include <input/input.hpp>

#include <iostream>

Client::Client(network::Address address, network::Address lobby_address)
    : host_{address},
      lobby_{},
      server_{},
      state_{State::kConnectingToLobby},
      uuid_{} {
  host_.Connect(std::move(lobby_address));
}

void Client::Update() {
  host_.Dispatch(this);

  std::uint8_t buffer[1024] = {};
  auto result = input::AsyncInput::Poll(buffer, sizeof(buffer));
  if (result > 0 && state_ != State::kConnectingToLobby) {
    lobby_->Send(
      protocol::MakeReliableMessage<protocol::StartGameRequest>(
        protocol::Tag::kStartGameRequest
      )
    );
  }
}

void Client::OnConnect(network::Socket socket) {
  switch (state_) {
    case State::kConnectingToLobby: {
      auto address = host_.GetAddress();

      lobby_.emplace(std::move(socket));

      lobby_->Send(
        protocol::MakeReliableMessage<protocol::JoinLobbyRequest>(
          protocol::Tag::kJoinLobbyRequest,
          address.Host(),
          address.Port()
        )
      );

      state_ = State::kUsual;
    } break;
    case State::kConnectingToServer: {
      auto address = host_.GetAddress();

      server_.emplace(std::move(socket));

      server_->Send(
        protocol::MakeReliableMessage<protocol::JoinGameRequest>(
          protocol::Tag::kJoinGameRequest,
          address.Host(),
          address.Port()
        )
      );

      state_ = State::kUsual;
    } break;
    default: {
    }
  }
}

void Client::OnReceive(network::Packet packet) {
  switch (protocol::TagOf(packet)) {
    case protocol::Tag::kGameStartedEvent: {
      OnGameStartedEvent(protocol::Cast<protocol::GameStartedEvent>(packet));
    } break;
    case protocol::Tag::kJoinGameResponse: {
      OnJoinGameResponse(protocol::Cast<protocol::JoinGameResponse>(packet));
    } break;
    case protocol::Tag::kPingRequest: {
      OnPingRequest(protocol::Cast<protocol::PingRequest>(packet));
    } break;
    case protocol::Tag::kPlayerJoinedGameEvent: {
      OnPlayerJoinedGameEvent(protocol::Cast<protocol::PlayerJoinedGameEvent>(packet));
    } break;
    case protocol::Tag::kPlayerPingEvent: {
      OnPlayerPingEvent(protocol::Cast<protocol::PlayerPingEvent>(packet));
    } break;
    case protocol::Tag::kGameServerTimeEvent: {
      OnGameServerTimeEvent(protocol::Cast<protocol::GameServerTimeEvent>(packet));
    } break;
    default: {
    }
  }
}

void Client::OnGameStartedEvent(protocol::GameStartedEvent* event) {
  host_.Connect(network::Address{event->game_server_host, event->game_server_port});
  state_ = State::kConnectingToServer;

  std::cout << "game started event received" << std::endl; // DEBUG LOG: REMOVE ME!
}

void Client::OnJoinGameResponse(protocol::JoinGameResponse* response) {
  uuid_ = response->uuid;

  std::cout << "you joined game, assigned uuid " << response->uuid << std::endl;
}

void Client::OnPingRequest(protocol::PingRequest* request) {
  server_->Send(
    protocol::MakeMessage<protocol::PingResponse>(
      protocol::Tag::kPingResponse,
      uuid_,
      request->game_server_time
    )
  );
}

void Client::OnPlayerJoinedGameEvent(protocol::PlayerJoinedGameEvent* event) {
  std::cout << "player #" << event->uuid << " joined the game" << std::endl;
}

void Client::OnPlayerPingEvent(protocol::PlayerPingEvent* event) {
  std::cout << "player #" << event->uuid << " ping is " << event->ping << std::endl; 
}

void Client::OnGameServerTimeEvent(protocol::GameServerTimeEvent* event) {
  // std::cout << "server time is " << event->time << std::endl;
}