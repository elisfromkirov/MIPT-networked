#ifndef ARRAY_BASE_IMPL
#error Do not include this file directly
#endif

namespace infra {

namespace detail {

template <typename TValue>
ArrayBase<TValue>::ArrayBase(std::uint64_t size)
    : data_{size != 0 ? reinterpret_cast<TValue*>(new char[size * sizeof(TValue)]) : nullptr},
      size_{size} {
}

template <typename TValue>
ArrayBase<TValue>::ArrayBase(ArrayBase&& other) noexcept 
    : data_{other.data_},
      size_{other.size_} {
  other.data_ = 0;
  other.size_ = 0;
}

template <typename TValue>
ArrayBase<TValue>& ArrayBase<TValue>::ArrayBase::operator=(ArrayBase&& other) noexcept {
  if (this != &other) {
    ArrayBase<TValue> temporary{std::move(other)};
    Swap(temporary);
  }
  return *this;
}

template <typename TValue>
ArrayBase<TValue>::~ArrayBase() noexcept {
  for (std::uint64_t i = 0; i < size_; ++i) {
    std::destroy_at(data_ + i);
  }
  delete[] reinterpret_cast<char*>(data_);
}

template <typename TValue>
void ArrayBase<TValue>::Swap(ArrayBase& other) noexcept {
  std::swap(data_, other->data_);
}

}  // namespace detail

}  // namespace infra