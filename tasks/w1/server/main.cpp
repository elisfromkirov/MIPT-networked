#include <server/server.hpp>

int main() {
  Server server{network::Endpoint{"127.0.0.1", 2022}};
  server.Serve();
  return 0;
}