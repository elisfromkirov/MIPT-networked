#include <client/client.hpp>

#include <network/network.hpp>

int main() {
  network::Initialize();
  Client client{network::Address{"127.0.0.1", 2024}, network::Address{"127.0.0.1", 2023}};
  while (true) {
    client.Update();
  }
  network::Finalize();
  return 0;
}