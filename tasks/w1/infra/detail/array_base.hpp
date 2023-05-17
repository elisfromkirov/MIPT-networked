#pragma once

#include <memory>
#include <utility>

namespace infra {

namespace detail {

template <typename TValue>
class ArrayBase {
 public:
  explicit ArrayBase(std::uint64_t size);

  ArrayBase(ArrayBase&& other) noexcept;
  ArrayBase& operator=(ArrayBase&& other) noexcept;

 protected:
  ~ArrayBase() noexcept;

  void Swap(ArrayBase& other) noexcept;

 protected:
  TValue* data_;
  std::uint64_t size_;
};

}  // namespace detail

}  // namespace infra

#define ARRAY_BASE_IMPL
#include <infra/detail/array_base.ipp>
#undef ARRAY_BASE_IMPL