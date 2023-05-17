#include <client/client.hpp>

#include <protocol/protocol.hpp>


Client::Client(network::Endpoint client_endpoint, network::Endpoint server_endpoint)
    : host_{network::Host::Bind(client_endpoint)},
      socket_{network::Socket::Connect(server_endpoint)} {
  socket_.Send(protocol::PackJoinRequest(client_endpoint));
}

void Client::Send(const std::string& string) {
  socket_.Send(protocol::PackDatagram(string));
}

void Client::SendKeepAlive() {
  socket_.Send(protocol::PackKeepAlive());
}