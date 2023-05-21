#include <utils/random.hpp>

#include <random>

namespace utils {
// 
float Random(bool signed_random) {
  static std::mt19937 gen{};
  if (signed_random) {
    if (gen() % 2 == 0) {
      return -1.f * static_cast<float>(gen()) / static_cast<float>(std::mt19937::max());
    }
    return static_cast<float>(gen()) / static_cast<float>(std::mt19937::max());
  }
  return std::fabs(static_cast<float>(gen()) / static_cast<float>(std::mt19937::max()));
}

}  // namespace utils