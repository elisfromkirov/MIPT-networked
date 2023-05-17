#pragma once

#include <network/host.hpp>
#include <network/socket.hpp>

class Client {
 public:
  Client(network::Endpoint client_endpoint, network::Endpoint server_endpoint);

  void Send(const std::string& string);

  void SendKeepAlive();

 private:
  network::Host host_;
  network::Socket socket_;
};