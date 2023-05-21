#include <server/server.hpp>
#include <server/controller.hpp>

#include <entity/world.hpp>

#include <network/network.hpp>

int main() {
  network::Initialize();

  World world{};

  ServerController controller{world};

  Server server{network::Address{"127.0.0.1", 2024}, controller};

  auto time = network::Time();
  while (true) {
    server.Update();
    controller.Update(network::Time() - time);
    time = network::Time();
  }

  network::Finalize();

  return 0;
}