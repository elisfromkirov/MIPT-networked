#include <client/client.hpp>

#include <iostream>

int main() {
  Client client{network::Endpoint{"127.0.0.2", 2023}, network::Endpoint{"127.0.0.1", 2022}};

  while (true) {
    std::cout << "> ";
    std::string input{};
    std::getline(std::cin, input);

    client.Send(input);

    client.SendKeepAlive();
  }

  return 0;
}