#pragma once
#include "mathUtils.h"
#include <limits>

template <typename T>
T pack_float_to_range(T range, float value, float min, float max) noexcept {
  return static_cast<T>(static_cast<float>(range) * ((clamp(value, min, max) - min) / (max - min)));
}

template <typename T>
T unpack_float_from_range(T range, T value, float min, float max) noexcept {
  return static_cast<float>(value) / static_cast<float>(range) * (max - min) + min;
}

template <typename T>
class PackedFloat {
 public:
  static constexpr const T range = std::numeric_limits<T>::max();

  static PackedFloat pack(float value, float min, float max) {
    return PackedFloat{
      pack_float_to_range(range, value, min, max);
    };
  }

  static float unpack(PackedFloat packed_value, float min, float max) {
    return unpack_float_from_range(range, packed_value.value_, min, max);
  }

  T value() const noexcept {
    return value_;
  }

 private:
  PackedFloat(T value) noexcept
    : value_{value} {
  }

 private:
  T value_;
};

struct Vec2 {
  float x;
  float y;
};

struct Vec3 {
  float x;
  float y;
  float z;
};

template <typename T, std::size_t num_x_bits, std::size_t num_y_bits>
class PackedVec2 {
  static_assert(sizeof(T) * 8 == num_x_bits + num_x_bits, "must be");

 public:
  static constexpr const T x_range = (1 << num_x_bits) - 1;
  static constexpr const T y_range = (1 << num_y_bits) - 1;

  static PackedVec2 pack(Vec2 vec, float min, float max) noexcept {
    return PackedVec2{
        (pack_float_to_range(x_range, vec.x, min, max) << num_y_bits) +
        (pack_float_to_range(y_range, vec.y, min, max));
    };
  }

  static Vec2 unpack(PackedVec2 packed_vec, float min, float max) noexcept {
    T x_value = (packed_vec.value_ >> num_y_bits);
    T y_value = (packed_vec.value_ & y_range);
    return Vec2{
        unpack_float_from_range(x_range, x_value, min, max),
        unpack_float_from_range(y_range, y_value, min, max),
    };
  }

  T value() const noexcept {
    return value_;
  }

 private:
  PackedVec2(T value) noexcept
      : value_{value} {
  }

 private:
  T value_;
};

template <typename T, std::size_t num_x_bits, std::size_t num_y_bits, std::size_t num_z_bits>
class PackedVec3 {
  static_assert(sizeof(T) * 8 == num_x_bits + num_x_bits + num_z_bits, "must be");

 public:
  static constexpr const T x_range = (1 << num_x_bits) - 1;
  static constexpr const T y_range = (1 << num_y_bits) - 1;
  static constexpr const T z_range = (1 << num_z_bits) - 1;

  static PackedVec3 pack(Vec3 vec, float min, float max) noexcept {
    return PackedVec3{
        (pack_float_to_range(x_range, vec.x, min, max) << (num_y_bits + num_z_bits)) +
        (pack_float_to_range(y_range, vec.y, min, max) << num_z_bits) +
        (pack_float_to_range(z_range, vec.z, min, max))
    };
  }

  static Vec3 unpack(PackedVec3 packed_vec, float min, float max) noexcept {
    T x_value = (packed_vec.value_ >> (num_y_bits + num_z_bits));
    T y_value = (packed_vec.value_ >> num_z_bits);
    T z_value = (packed_vec.value_ & z_range);

    return Vec3{
        unpack_float_from_range(x_range, x_value, min, max),
        unpack_float_from_range(y_range, y_value, min, max),
        unpack_float_from_range(z_range, z_value, min, max),
    };
  }

  T value() const noexcept {
    return value_;
  }

 private:
  PackedVec3(T value) noexcept
    : value_{value} {
  }

 private:
  T value_;
};

class Reader {
 public:
  Reader(std::uint8_t* data) noexcept
    : current_{data} {
  }

  std::uint32_t read_packed_uint32() noexcept {
    assert(current_ != nullptr);

    if ((current_[0] & 0x80) == 0x80) {
      auto value = ((reinterpret_cast<std::uint8_t>(current_)[0]) & (~0x80));
      current_ += sizeof(std::uint8_t);
      return value;
    }
    if ((current_[0] & 0x40) == 0x40) {
      auto value = ((reinterpret_cast<std::uint16_t>(current_)[0]) & (~0x4000));
      current_ += sizeof(std::uint16_t);
      return value;
    }
    auto value = reinterpret_cast<std::uint32_t>(current_)[0];
    current_ += sizeof(std::uint32_t);
    return value;
  }

 private:
  std::uint8_t* current_;
};

class Writer {
 public:
  Writer(std::uint8_t* data) noexcept
    : current_{data} {
  }

  void write_packed_uint32(std::uint32_t value) {
    assert(current_ != nullptr);
    assert(value < 0x3fffffff);

    if (value < 0x7f) {
      reinterpret_cast<std::uint8_t*>(current_)[0] = (value & 0x80);
      current_ += sizeof(std::uint8_t);
    }
    if (value < 0x3fff) {
      reinterpret_cast<std::uint16_t*>(current_)[0] = 0;
      current_ += sizeof(std::uint16_t);
    }
    reinterpret_cast<std::uint32_t*>(current_)[0] = value;
    current_ += sizeof(std::uint32_t);
  }

 private:
  std::uint8_t* current_;
};