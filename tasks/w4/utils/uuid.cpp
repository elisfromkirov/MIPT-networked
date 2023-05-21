#include <utils/uuid.hpp>

namespace utils {

std::uint64_t UniversallyUniqueIdentifier::Next() noexcept {
  return ++next_uuid_;
}

std::uint64_t UniversallyUniqueIdentifier::next_uuid_{0};

}  // namespace utils