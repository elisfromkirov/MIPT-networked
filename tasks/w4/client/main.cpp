#include <client/client.hpp>
#include <client/controller.hpp>

#include <entity/world.hpp>

#include <network/network.hpp>

#include <platform/window.hpp>

int main() {
  platform::Window::Initialize(800, 800);

  network::Initialize();

  World world{};

  ClientController controller{world};

  Client client{network::Address{"127.0.0.1", 2022}, network::Address{"127.0.0.1", 2024}, controller};
  while (!client.IsConnected()) {
    client.Update();
  }
  auto time = network::Time();
  while (platform::Window::Continue()) {
    client.Update();
    controller.Update(network::Time() - time);
    world.Draw();
    time = network::Time();
  }

  network::Finalize();

  platform::Window::Finalize();

  return 0;
}