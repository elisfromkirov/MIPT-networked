#include <game/server.hpp>

#include <network/network.hpp>

int main() {
  network::Initialize();
  GameServer server{network::Address{"127.0.0.1", 2022}};
  while (true) {
    server.Update();
  }
  network::Finalize();
  return 0;
}