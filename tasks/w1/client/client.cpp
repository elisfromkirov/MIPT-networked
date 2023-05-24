#include <client/client.hpp>

#include <protocol/protocol.hpp>

#include <iostream>

Client::Client(network::Endpoint client_endpoint, network::Endpoint server_endpoint)
    : host_{network::Host::Bind(client_endpoint)},
      socket_{network::Socket::Connect(server_endpoint)} {
  socket_.Send(protocol::PackJoinRequest(client_endpoint));
}

void Client::Poll() {
  while (auto packet = host_.Receive()) {
    auto message = static_cast<protocol::Message>(packet.Data()[0]);
    switch (message) {
      case protocol::Message::kDatagram: OnDatagram(std::move(packet)); break;
    }
  }
}

void Client::Send(const std::string& string) {
  socket_.Send(protocol::PackDatagram(string));
}

void Client::SendKeepAlive() {
  socket_.Send(protocol::PackKeepAlive());
}

void Client::OnDatagram(network::Packet packet) {
  std::string_view string{reinterpret_cast<const char*>(packet.Data() + 1), packet.Size() - 1};

  std::cout << "Server return " << string << std::endl;
}