#include <entity/world.hpp>

#include <platform/window.hpp>

World::World()
    : entities_{} {
}

Entity& World::Add(std::uint64_t uuid) {
  entities_.insert({uuid, {}});
  return entities_.at(uuid);
}

void World::Remove(std::uint64_t uuid) {
  entities_.erase(uuid);
}

Entity& World::Find(std::uint64_t uuid) {
  return entities_.at(uuid);
}

std::unordered_map<std::uint64_t, Entity>& World::Entities() {
  return entities_;
}

void World::Draw() {
  platform::Window::BeginDraw();
  for (const auto& [uuid, entity] : entities_) {
    platform::Window::DrawRectangle(entity.x, entity.y, entity.r);
  }
  platform::Window::EndDraw();
}