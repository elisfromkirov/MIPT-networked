#ifndef ARRAY_IMPL
#error Do not include this file directly
#endif

namespace infra {

template <typename TValue>
Array<TValue>::Array(std::uint64_t size)
    : detail::ArrayBase<TValue>{size} {
  for (std::uint64_t i = 0; i < this->size_; ++i) {
    std::construct_at(this->data_ + i);
  }
}

template <typename TValue>
TValue* Array<TValue>::Data() const noexcept {
  return this->data_;
}

template <typename TValue>
std::uint64_t Array<TValue>::Size() const noexcept {
  return this->size_;
}

template <typename TValue>
TValue& Array<TValue>::operator[](std::uint64_t index) noexcept {
  assert(index < this->size_);

  return this->data_[index];
}

template <typename TValue>
const TValue& Array<TValue>::operator[](std::uint64_t index) const noexcept {
  assert(index < this->size_);

  return this->data_[index];
}

}  // namespace infra