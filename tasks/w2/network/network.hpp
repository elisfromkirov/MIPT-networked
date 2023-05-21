#pragma once

#include <network/address.hpp>
#include <network/host.hpp>
#include <network/handler.hpp>
#include <network/packet.hpp>
#include <network/socket.hpp>

namespace network {

void Initialize();

void Finalize();

std::uint32_t Time();

}  // namespace network