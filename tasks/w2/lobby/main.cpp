#include <lobby/server.hpp>

#include <network/network.hpp>

int main() {
  

  network::Initialize();
  LobbyServer server{network::Address{"127.0.0.1", 2023}};
  while (true) {
    server.Update();
  }
  network::Finalize();
  return 0;
}