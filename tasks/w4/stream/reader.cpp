#include <stream/reader.hpp>

namespace stream {

Reader::Reader(network::Packet& packet) noexcept
    : cursor_{packet.Data()} {
}

}  // namespace stream