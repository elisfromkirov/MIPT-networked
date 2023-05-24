#include <server/server.hpp>

#include <iostream>

Server::Server(network::Endpoint endpoint)
    : host_{network::Host::Bind(endpoint)},
      sockets_{} {
}

void Server::Serve() {
  while (auto packet = host_.Receive()) {
    auto message = static_cast<protocol::Message>(packet.Data()[0]);
    switch (message) {
      case protocol::Message::kJoinRequest: OnJoinRequest(std::move(packet)); break;
      case protocol::Message::kDatagram: OnDatagram(std::move(packet)); break;
      case protocol::Message::kKeepAlive: OnKeepAlive(std::move(packet)); break;
    }
  }
}

void Server::OnJoinRequest(network::Packet packet) {
  auto endpoint = protocol::UnpackJoinRequest(packet);

  std::cout << "Client connected from " << endpoint.Address() << " " << endpoint.Port() << std::endl;

  auto socket = network::Socket::Connect(endpoint);
  sockets_.push_back(std::move(socket));
}

void Server::OnDatagram(network::Packet packet) {
  std::string_view string{reinterpret_cast<const char*>(packet.Data() + 1), packet.Size() - 1};

  std::cout << "Client sent " << string << std::endl;

  for (auto& socket : sockets_) {
      socket.Send(packet.Clone());
  }
}

void Server::OnKeepAlive(network::Packet packet) {
  std::cout << "Keep alive" << std::endl;
}