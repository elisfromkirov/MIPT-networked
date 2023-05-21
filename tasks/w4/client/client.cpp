#include <client/client.hpp>

#include <client/controller.hpp>

Client::Client(network::Address address, network::Address server_address, ClientController& controller)
    : host_{address},
      server_{},
      controller_{&controller} {
  host_.Connect(server_address);
  controller_->SetupClient(this);
}

bool Client::IsConnected() const noexcept {
  return server_.has_value();
}

void Client::Update() {
  host_.Dispatch(this);
}

void Client::SendPlayerEntityMovedEvent(const PlayerEntityMovedEvent& event) {
  server_->Send(SerializePlayerEntityMovedEvent(event));
}

void Client::OnConnect(network::Socket socket) {
  if (!IsConnected()) {
    auto address = host_.GetAddress();

    socket.Send(SerializeJoinGameRequest({address.Host(), address.Port()}));

    server_.emplace(std::move(socket));
  }
}

void Client::OnReceive(network::Packet packet) {
  switch (TagOf(packet)) {
    case Tag::kJoinGameResponse: {
      auto response = DeserializeJoinGameResponse(std::move(packet));
      controller_->SetupControlledEntity(Entity{response.uuid, response.x, response.y, response.r});
    } break;
    case Tag::kEntityAttachedEvent: {
      controller_->OnEntityAttachedEvent(DeserializeEntityAttachedEvent(std::move(packet)));
    } break;
    case Tag::kEntityDetachedEvent: {
      controller_->OnEntityDetachedEvent(DeserializeEntityDetachedEvent(std::move(packet)));
    } break;
    case Tag::kEntityMovedEvent: {
      controller_->OnEntityMovedEvent(DeserializeEntityMovedEvent(std::move(packet)));
    } break;
    case Tag::kEntityResizedEvent: {
      controller_->OnEntityResizedEvent(DeserializeEntityResizedEvent(std::move(packet)));
    } break;    
    default: {
    }
  }
}