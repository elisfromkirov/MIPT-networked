#include <network/network.hpp>

#include <enet/enet.h>

namespace network {

void Initialize() {
  enet_initialize();
}

void Finalize() {
  enet_deinitialize();
}

std::uint32_t Time() {
  return enet_time_get();
}

}  // namepsace network