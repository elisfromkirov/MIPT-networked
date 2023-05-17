#include <network/host.hpp>

#include <iostream>

int main() {
  auto host = network::Host::Bind(network::Endpoint{"127.0.0.1", 2022});

  while (true) {
    while (auto packet = host.Receive()) {
      std::cout << std::string_view{reinterpret_cast<char*>(packet.Data()), packet.Size()} << std::endl;
    }
  }

  return 0;
}