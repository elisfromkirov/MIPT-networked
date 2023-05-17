#include <network/socket.hpp>

#include <iostream>

int main() {
  auto socket = network::Socket::Connect(network::Endpoint{"127.0.0.1", 2022});

  while (true) {
    std::cout << "> ";
    std::string input{};
    std::getline(std::cin, input);

    socket.Send(network::Packet{input.data(), input.size()});
  }

  return 0;
}