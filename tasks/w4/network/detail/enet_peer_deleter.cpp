#include <network/detail/enet_peer_deleter.hpp>

namespace network::detail {

void ENetPeerDeleter::operator()(ENetPeer* socket) const noexcept {
}

}  // namespace network::detail