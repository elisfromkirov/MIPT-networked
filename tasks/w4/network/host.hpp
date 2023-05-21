#pragma once

#include <network/address.hpp>
#include <network/packet.hpp>
#include <network/handler.hpp>
#include <network/socket.hpp>

#include <network/detail/forward.hpp>
#include <network/detail/enet_host_deleter.hpp>

#include <cassert>

#include <memory>

namespace network {

class Host final {
 public:
  Host(const Address& address);

  Address GetAddress() const;

  void Dispatch(IHandler* handler);

  Socket Connect(const Address& address);

 private:
  std::unique_ptr<ENetHost, detail::ENetHostDeleter> host_;
};

}  // namespace network