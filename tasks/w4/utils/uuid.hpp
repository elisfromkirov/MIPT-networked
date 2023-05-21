#pragma once

#include <cstdint>

namespace utils {

class UniversallyUniqueIdentifier {
 public:
  static std::uint64_t Next() noexcept;

 private:
  static std::uint64_t next_uuid_;
};

}  // namesapce utils