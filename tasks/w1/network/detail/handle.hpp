#pragma once

namespace network::detail {

class Handle {
 public:
  Handle(int handle) noexcept;

  Handle(Handle&& other) noexcept;
  Handle& operator=(Handle&& other) noexcept;

 protected:
  ~Handle() noexcept;

 protected:
  void Swap(Handle& other) noexcept;

 protected:
  int handle_;
};

}  // namespace network::detail