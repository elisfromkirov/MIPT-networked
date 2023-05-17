#pragma once

#include <infra/detail/array_base.hpp>

#include <cassert>
#include <memory>
#include <utility>

namespace infra {

template <typename TValue>
class Array final : private detail::ArrayBase<TValue> {
 public:
  explicit Array(std::uint64_t size = 0);

  [[nodiscard]]
  TValue* Data() const noexcept;

  [[nodiscard]]
  std::uint64_t Size() const noexcept;

  TValue& operator[](std::uint64_t index) noexcept;

  const TValue& operator[](std::uint64_t index) const noexcept;
};

}  // namespace infra

#define ARRAY_IMPL
#include <infra/array.ipp>
#undef ARRAY_IMPL