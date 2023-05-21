#include <network/host.hpp>

#include <enet/enet.h>

namespace network {

Host::Host(const Address& address)
    : host_{enet_host_create(address.address_.get(), 32, 2, 0, 0)} {
  assert(host_);
}

Address Host::GetAddress() const {
  return Address{host_->address.host, host_->address.port};
}

void Host::Dispatch(IHandler* handler) {
  assert(host_);

  ENetEvent event{};
  while (enet_host_service(host_.get(), &event, 1) > 0) {
    switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT: {
        handler->OnConnect(Socket{event.peer});
      } break;
      case ENET_EVENT_TYPE_RECEIVE: {
        handler->OnReceive(Packet{event.packet});
      } break;
      default: {
      }
    }
  }
}

Socket Host::Connect(const Address& address) {
  assert(host_);

  return Socket{enet_host_connect(host_.get(), address.address_.get(), 2, 0)};
}

}  // namespace network