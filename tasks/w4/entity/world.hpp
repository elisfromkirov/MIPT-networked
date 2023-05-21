#pragma once

#include <entity/entity.hpp>

#include <unordered_map>
#include <vector>

class World final {
 public:
  World();

  Entity& Add(std::uint64_t uuid);

  void Remove(std::uint64_t uuid);

  Entity& Find(std::uint64_t uuid);

  std::unordered_map<std::uint64_t, Entity>& Entities();

  void Draw();

 private:
  std::unordered_map<std::uint64_t, Entity> entities_; 
};