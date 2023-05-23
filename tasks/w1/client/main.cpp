#include <client/client.hpp>

#include <input/input.hpp>

int main() {
  Client client{network::Endpoint{"127.0.0.2", 2023}, network::Endpoint{"127.0.0.1", 2022}};

  std::uint8_t buffer[1024] = {};
  while (true) {
    if (auto read_bytes = input::AsyncInput::Poll(buffer, sizeof(buffer))) {
      client.Send(std::string(reinterpret_cast<char*>(buffer)));
    }

    client.SendKeepAlive();
  }

  return 0;
}