#include <client/client.hpp>

#include <client/controller.hpp>

#include <platform/keyboard.hpp>

ClientController::ClientController(World& world)
    : world_{&world},
      client_{nullptr},
      controlled_entity_{0} {
}

void ClientController::SetupClient(Client* client) {
  client_ = client;
}

void ClientController::SetupControlledEntity(const Entity& controlled_entity) {
  auto& entity = world_->Add(controlled_entity.uuid);
  entity.uuid = controlled_entity.uuid;
  entity.x = controlled_entity.x;
  entity.y = controlled_entity.y;
  entity.r = controlled_entity.r;

  controlled_entity_ = controlled_entity.uuid;
}

void ClientController::Update(std::uint32_t delta_time) {
  auto delta_x = 0.0f;
  auto delta_y = 0.0f;

  if (platform::Keyboard::IsKeyDown(platform::VirtualKey::kLeftArrow)) {
    delta_x -= static_cast<float>(delta_time) * 0.001f;
  }
  if (platform::Keyboard::IsKeyDown(platform::VirtualKey::kRightArrow)) {
    delta_x += static_cast<float>(delta_time) * 0.001f;
  }
  if (platform::Keyboard::IsKeyDown(platform::VirtualKey::kUpArrow)) {
    delta_y -= static_cast<float>(delta_time) * 0.001f;
  }
  if (platform::Keyboard::IsKeyDown(platform::VirtualKey::kDownArrow)) {
    delta_y += static_cast<float>(delta_time) * 0.001f;
  }

  auto& entity = world_->Find(controlled_entity_);

  entity.x += delta_x;
  entity.y += delta_y;

  client_->SendPlayerEntityMovedEvent(PlayerEntityMovedEvent{controlled_entity_, delta_x, delta_y});
}

void ClientController::OnEntityAttachedEvent(EntityAttachedEvent event) {
  auto& entity = world_->Add(event.uuid);
  entity.uuid = event.uuid;
  entity.x = event.x;
  entity.y = event.y;
  entity.r = event.r;
}

void ClientController::OnEntityDetachedEvent(EntityDetachedEvent event) {
  world_->Remove(event.uuid);
}

void ClientController::OnEntityMovedEvent(EntityMovedEvent event) {
  auto& entity = world_->Find(event.uuid);
  entity.x += event.delta_x;
  entity.y += event.delta_y;
}

void ClientController::OnEntityResizedEvent(EntityResizedEvent event) {
  auto& entity = world_->Find(event.uuid);
  entity.r += event.delta_r;
}