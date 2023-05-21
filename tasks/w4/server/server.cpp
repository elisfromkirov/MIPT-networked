#include <server/controller.hpp>

#include <server/server.hpp>

Server::Server(network::Address address, ServerController& controller)
    : host_{address},
      controller_{&controller} {
  controller_->SetupServer(this);
}

bool Server::IsConnected(const network::Socket& socket) const noexcept {
  auto address = socket.GetAddress();
  for (const auto& client : clients_) {
    auto client_address = client.GetAddress();
    if (address.Host() == client_address.Host() && address.Port() == client_address.Port()) {
      return true;
    }
  }
  return false;
}

void Server::Update() {
  host_.Dispatch(this);
}

void Server::Broadcast(const EntityAttachedEvent& event) {
  for (auto& client : clients_) {
    client.Send(SerializeEntityAttachedEvent(event));
  }
}

void Server::Broadcast(const EntityDetachedEvent& event) {
  for (auto& client : clients_) {
    client.Send(SerializeEntityDetachedEvent(event));
  }
}

void Server::Broadcast(const EntityMovedEvent& event) {
  for (auto& client : clients_) {
    client.Send(SerializeEntityMovedEvent(event));
  }
}

void Server::Broadcast(const EntityResizedEvent& event) {
  for (auto& client : clients_) {
    client.Send(SerializeEntityResizedEvent(event));
  }
}

void Server::OnConnect(network::Socket socket) {
  if (!IsConnected(socket)) {
    auto entities = controller_->Entities();
    for (const auto& entity : entities) {
      socket.Send(SerializeEntityAttachedEvent({entity.uuid, entity.x, entity.y, entity.r}));
    }

    auto entity = controller_->SetupEntity();
    socket.Send(SerializeJoinGameResponse({entity.uuid, entity.x, entity.y, entity.r}));

    for (auto& client : clients_) {
      client.Send(SerializeEntityAttachedEvent({entity.uuid, entity.x, entity.y, entity.r}));
    }

    clients_.emplace_back(std::move(socket));
  }
} 

void Server::OnReceive(network::Packet packet) {
  switch (TagOf(packet)) {
    case Tag::kJoinGameRequest: {
      auto request = DeserializeJoinGameRequest(std::move(packet));
      host_.Connect(network::Address{request.host, request.port});
    } break;
    case Tag::kPlayerEntityMovedEvent: {
      controller_->OnPlayerEntityMovedEvent(DeserializePlayerEntityMovedEvent(std::move(packet)));
    } break;
    default: {
    }
  }
}