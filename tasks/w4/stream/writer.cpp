#include <stream/writer.hpp>

namespace stream {

Writer::Writer(network::Packet& packet)
    : cursor_{packet.Data()} {
}

}  // namespace stream