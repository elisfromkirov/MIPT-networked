#pragma once

#include <network/host.hpp>
#include <network/socket.hpp>

#include <protocol/protocol.hpp>

#include <vector>

class Server {
 public:
  Server(network::Endpoint endpoint);

  void Serve();

 private:
  void OnJoinRequest(network::Packet packet);

  void OnDatagram(network::Packet packet);

  void OnKeepAlive(network::Packet packet);

 private:
  network::Host host_;
  std::vector<network::Socket> sockets_;
};